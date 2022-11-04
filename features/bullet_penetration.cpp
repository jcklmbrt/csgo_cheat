#include <cmath>
#include "features/bullet_penetration.hpp"

#include "source_sdk/mathlib/vector.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/public/iclientnetworkable.hpp"
#include "source_sdk/public/gametrace.hpp"
#include "source_sdk/engine/ienginetrace.hpp"
#include "memory/interfaces.hpp"
#include "source_sdk/game/shared/cstrike15/cs_weapon_parse.hpp"
#include "source_sdk/tier1/convar.hpp"
#include "util/strtools.hpp"
#include "source_sdk/public/client_class.hpp"

bool IsBreakableEntity(C_BaseEntity *entity)
{
	static constexpr int DAMAGE_NO          = 0;
	static constexpr int DAMAGE_EVENTS_ONLY = 1; // Call damage functions, but don't modify health
	static constexpr int DAMAGE_YES         = 2;
	static constexpr int DAMAGE_AIM         = 3;

	IClientNetworkable *networkable = entity->GetClientNetworkable();

	if(entity == nullptr || networkable->entindex() == 0)
		return false;

	//original IsBreakable fn
	//static auto IsBreakable = mem::PatternScan<bool(__thiscall *)(C_BaseEntity *)>(
	//	"client", "\x55\x8B\xEC\x51\x56\x8B\xF1\x85\xF6\x74\x68\x83\xBE")
	//);

	//reverse IsBreakable for this offset
	bool *take_damage   = entity->Offset<bool *>(0x280);
	bool old_take_damage = *take_damage;

	ClientClass *client_class = networkable->GetClientClass();

	switch(FNV(client_class->network_name)) {
	case FNV("CBreakableSurface"):
	case FNV("CFuncBrush"):
	case FNV("CBaseDoor"):
		*take_damage = DAMAGE_YES;
		break;
	}

//	bool result = IsBreakable(entity);

	*take_damage = old_take_damage;

//	return result;

}

float UTIL_DistanceToRay(Vector pos, Vector rayStart, Vector rayEnd)
{
	Vector to  = pos    - rayStart;
	Vector dir = rayEnd - rayStart;

	float length = dir.Length();
	dir /= length;

	float range_along = dir.Dot(to);
	float range;

	//off start point
	if(range_along < 0.0f)
		range = -(pos - rayStart).Length();

		//off end point
	else if(range_along > length)
		range = -(pos - rayEnd).Length();

		// within ray bounds
	else
	{
		Vector onRay = (dir * range_along) + rayStart;
		range = (pos - onRay).Length();
	}

	return range;
}

void UTIL_TraceLine(Vector start, Vector end, int mask, C_BaseEntity *entity, trace_t &exit)
{
	TraceFilter::SkipOneEntity filter = {entity};
	Ray_t ray = Ray_t(start, end);

	intf::trace->TraceRay(&ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &exit);
}

void UTIL_ClipTraceToPlayers(Vector start, Vector end, int mask, ITraceFilter *filter, trace_t &tr)
{
	trace_t player_trace;
	Ray_t ray = Ray_t(start, end);

	float smallest_fraction = tr.fraction;
	float max_range = 60.0f;

	for(int i = 0; i < intf::globals->max_clients; i++)
	{
		C_CSPlayer *player = intf::entitylist->GetClientEntity<C_CSPlayer *>(i);

		if(!player || !player->IsAlive())
			continue;

		if(player->GetClientNetworkable()->IsDormant())
			continue;

		if(filter && filter->ShouldHitEntity(player, mask) == false)
			continue;

		float range = UTIL_DistanceToRay(player->VecOrigin(), start, end);

		if(range < 0.0f || range > max_range)
			continue;

		intf::trace->ClipRayToEntity(&ray, mask | CONTENTS_HITBOX, player, &player_trace);

		if(player_trace.fraction < smallest_fraction)
		{
			// we shortened the ray - save off the trace
			tr = player_trace;
			smallest_fraction = player_trace.fraction;
		}
	}
};

bool TraceToExit(Vector start, Vector direction, CGameTrace &tr_enter, CGameTrace &tr_exit)
{
	static constexpr float MAX_DISTANCE = 90.0f;
	static constexpr float STEP_SIZE    = 4.0f;

	float flDistance = 0.0f;
	Vector end = {};

	int startContents = 0;

	while(flDistance < MAX_DISTANCE)
	{
		flDistance += STEP_SIZE;

		end = start + (direction * flDistance);

		Vector trEnd = end - (direction * STEP_SIZE);
		int contents = intf::trace->PointContents(end, MASK_SHOT_HULL | CONTENTS_HITBOX);

		//assumes PointContents is a pure function
		if(startContents == 0)
			startContents = contents;

		if((contents & MASK_SHOT_HULL) == 0 || ((contents & CONTENTS_HITBOX) && startContents != contents))
		{
			// this gets a bit more complicated and expensive when we have to deal with displacements
			UTIL_TraceLine(end, trEnd, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr, tr_exit);

			bool hit_world = tr_enter.entity == intf::entitylist->GetClientEntity<C_BaseEntity *>(0);

			// we exited the wall into a player's hitbox
			if(tr_exit.startsolid == true && (tr_exit.surface.flags & SURF_HITBOX))
			{
				// do another trace, but skip the player to get the actual exit surface
				UTIL_TraceLine(end, start, MASK_SHOT_HULL, tr_exit.m_pEnt, tr_exit);

				if(tr_exit.DidHit() && tr_exit.startsolid == false)
				{
					end = tr_exit.end;
					return true;
				}

			}
			else if(tr_exit.DidHit() && tr_exit.startsolid == false)
			{
				bool enter_no_draw = tr_enter.surface.flags & SURF_NODRAW;
				bool exit_no_draw  = tr_exit.surface.flags  & SURF_NODRAW;

				// we have a case where we have a breakable object, but the mapper put a nodraw on the backside
				if(exit_no_draw && IsBreakableEntity(tr_exit.entity) && IsBreakableEntity(tr_enter.entity)) {
					end = tr_exit.end;
					return true;
				}

				// exit nodraw is only valid if our entrace is also nodraw
				else if(exit_no_draw == false || (enter_no_draw && exit_no_draw))
				{
					if(direction.Dot(tr_exit.plane.normal) <= 1.0f)
					{
						end = end - (direction * (STEP_SIZE * tr_exit.fraction));
						return true;
					}
				}
			}
			else if((!hit_world && tr_enter.entity != nullptr) && IsBreakableEntity(tr_enter.entity))
			{
				tr_exit = tr_enter;
				tr_exit.end = start + direction;
				return true;
			}
		}
	}
	return false;
}

float ScaleDamage(CGameTrace &enter, CCSWeaponInfo *wpn_info, float base_damage)
{
	C_CSPlayer *player = reinterpret_cast<C_CSPlayer *>(enter.entity);

	bool is_armored   = false;
	bool heavy_armor = player->HasHeavyArmor();
	int  armor_value = player->ArmorValue();
	int  hitgroup   = enter.hitgroup;

	switch(hitgroup)
	{
	case HITGROUP_HEAD:
		is_armored = player->HasHelmet();
		//base_damage *= heavy_armor ? 2.0f : 4.0;
		base_damage *= wpn_info->headshot_multiplier;
		break;
	case HITGROUP_STOMACH:
		base_damage *= 1.25f;
		[[fallthrough]];
	case HITGROUP_GENERIC:
	case HITGROUP_CHEST:
	case HITGROUP_LEFTARM:
	case HITGROUP_RIGHTARM:
		is_armored = true;
		break;

	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		base_damage *= 0.75f;
		break;

	default:
		break;
	}

	if(armor_value > 0 && is_armored)
	{
		float bonus_value = 1.f, armor_bonus_ratio = 0.5f, armor_ratio = wpn_info->armor_ratio / 2.f;

		//damage gets modified for heavy armor users
		if(heavy_armor)
		{
			armor_bonus_ratio = 0.33f;
			armor_ratio *= 0.5f;
			bonus_value = 0.33f;
		}

		float new_damage = base_damage * armor_ratio;

		if(heavy_armor)
			new_damage *= 0.85f;

		if(((base_damage - (base_damage * armor_ratio)) * (bonus_value * armor_bonus_ratio)) > armor_value)
			new_damage = base_damage - (armor_value / armor_bonus_ratio);

		base_damage = new_damage;
	}
	return base_damage;
}

bool HandleBulletPenetration(trace_t &tr_enter, trace_t &tr_exit, Vector dir, float penetration_power, float &damage)
{
	//cvars
	static ConVar *ff_damage_bullet_penetration = intf::cvar->FindVar("ff_damage_bullet_penetration");
	static ConVar *ff_damage_reduction_bullets  = intf::cvar->FindVar("ff_damage_reduction_bullets");
	//assume we're using the new penetration method (sv_penetration_type 1)
	//static auto sv_penetration_type          = g_pCvar->Find("sv_penetration_type");

	// find exact penetration exit
	if(!TraceToExit(tr_enter.end, dir, tr_enter, tr_exit))
	{
		// ended in solid
		if((intf::trace->PointContents(tr_enter.end, MASK_SHOT_HULL) & MASK_SHOT_HULL) == 0)
		{
			return false;
		}
	}

	//assuming trace_to_exit doesn't mutate our enter trace
	CSurfaceData *enter_surface = intf::physprops->GetSurfaceData(tr_enter.surface.props);
	CSurfaceData *exit_surface  = intf::physprops->GetSurfaceData(tr_exit.surface.props);

	bool no_draw  = tr_enter.surface.flags & SURF_NODRAW;
	bool is_grate = tr_enter.contents      & CONTENTS_GRATE;

	// percent of total damage lost automatically on impacting a surface
	float penetration_modifier, damage_modifier = 0.16f;

	// since some railings in de_inferno are CONTENTS_GRATE but CHAR_TEX_CONCRETE, we'll trust the
	// CONTENTS_GRATE and use a high damage modifier.
	if(is_grate || no_draw || enter_surface->material == CHAR_TEX_GLASS || enter_surface->material == CHAR_TEX_GRATE)
	{
		if(enter_surface->material == CHAR_TEX_GLASS || enter_surface->material == CHAR_TEX_GRATE)
		{
			penetration_modifier = 3.0f;
			damage_modifier = 0.05f;
		}
		else
		{
			penetration_modifier = 1.0f;
		}
	}

	//we can do a team check here.
	else if(enter_surface->material == CHAR_TEX_FLESH && ff_damage_reduction_bullets->GetFloat() == 0.0f)
	{
		if(ff_damage_bullet_penetration->GetFloat() == 0.0f)
		{
			return false;
		}

		penetration_modifier = ff_damage_bullet_penetration->GetFloat();
	}
	else
	{
		penetration_modifier = (enter_surface->penetration_modifier + exit_surface->penetration_modifier) / 2.0f;
	}

	if(enter_surface->material == exit_surface->material)
	{
		switch(exit_surface->material)
		{
		case CHAR_TEX_CARDBOARD:
		case CHAR_TEX_WOOD:
			penetration_modifier = 3.0f;
			break;
		case CHAR_TEX_PLASTIC:
			penetration_modifier = 2.0f;
			break;
		}
	}

	float thickness_sqr = (tr_exit.end - tr_enter.end).LengthSqr();

	penetration_modifier = fmaxf(1.0f / penetration_modifier, 0.0f);

	//pasta'd this monstrosity from IDA
	float damage_lost = (fmaxf(((3.0f / penetration_power) * 1.25f), 0.0f) * (penetration_modifier * 3.0f) + (damage * damage_modifier)) + ((thickness_sqr * penetration_modifier) * 0.041666668);

	damage -= fmaxf(damage_lost, 0.0f);

	if(damage < 1.0f)
		return false;

	return true;
}

bool AutoWall(Vector start, Vector end, CCSWeaponInfo *wpn_info, C_CSPlayer *target)
{
	constexpr float RAY_EXTENSION = 40.0f;

	float damage = static_cast<float>(wpn_info->damage);
	TraceFilter::SkipOneEntity filter = { C_CSPlayer::GetLocalPlayer() };

	CGameTrace enter, exit;

	//direction unit vector
	Vector direction = (end - start).Normalized();

	//the distance we have travelled, wpn_info->range is the max.
	float distance = 0.0f;

	for(int count = 0; count < 4; count++)
	{
		//extend end position out to the max bullet range
		end = start + (direction * (wpn_info->range - distance));

		Ray_t ray = Ray_t(start, end);

		intf::trace->TraceRay(&ray, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &enter);

		UTIL_ClipTraceToPlayers(start, end + direction * RAY_EXTENSION, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &enter);

		// didn't hit anything.
		if(!enter.DidHit())
			return false;

		//calculate the damage based on the distance the bullet travelled.
		distance += enter.fraction * (wpn_info->range - distance);
		damage   *= std::pow(wpn_info->range_modifier, distance / 500.0f);

		//we hit our target
		if(enter.entity == target)
		{
			damage = ScaleDamage(enter, wpn_info, damage);

			return damage >= 100.0f;
			//return damage >= g_cfg.min_damage;
		}

		//calculate damage dropoff from penetration
		if(!HandleBulletPenetration(enter, exit, direction, wpn_info->penetration, damage))
			return false;

		start = exit.end;
	}
	return false;
}