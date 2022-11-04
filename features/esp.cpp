
#include <vector>

#include "renderer/renderer.hpp"

#include "memory/interfaces.hpp"

#include "features/esp.hpp"

#include "source_sdk/game/client/c_basecombatweapon.hpp"
#include "source_sdk/mathlib/vmatrix.hpp"
#include "source_sdk/public/engine/icollideable.hpp"
#include "source_sdk/public/studio.hpp"
#include "source_sdk/public/cdll_int.hpp"
#include "source_sdk/public/iclientrenderable.hpp"
#include "source_sdk/public/iclientnetworkable.hpp"
#include "source_sdk/public/engine/ivmodelinfo.hpp"
#include "source_sdk/public/globalvars_base.hpp"
#include "source_sdk/public/icliententitylist.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"

#include "features/player_lagcompensation.hpp"
#include "features/player_util.hpp"

bool WorldToScreen(Vector world, Vector &screen)
{
	static VMatrix *w2s = intf::engine->WorldToScreenMatrix();

	auto MatMul = [world](size_t index)
	{
		return w2s->m[index][0] * world.x +
			w2s->m[index][1] * world.y +
			w2s->m[index][2] * world.z +
			w2s->m[index][3];
	};

	float w = MatMul(3);

	if(w < 0.01f)
		return false;

	int x, y;
	intf::engine->GetScreenSize(x, y);

	screen.x = (x / 2.0f) * (1.0f + MatMul(0) / w);
	screen.y = (y / 2.0f) * (1.0f - MatMul(1) / w);

	return true;
}

bool GetBBox(C_BaseEntity *entity, float &left, float &top, float &right, float &bottom)
{
	ICollideable *collideable = entity->GetCollideable();
	Vector mins = collideable->OBBMins();
	Vector maxs = collideable->OBBMaxs();

	matrix3x4_t &trans = entity->GetClientRenderable()->RenderableToWorldTransform();

	Vector points[] = {
		{mins.x, mins.y, mins.z},
		{mins.x, maxs.y, mins.z},
		{maxs.x, maxs.y, mins.z},
		{maxs.x, mins.y, mins.z},
		{maxs.x, maxs.y, maxs.z},
		{mins.x, maxs.y, maxs.z},
		{mins.x, mins.y, maxs.z},
		{maxs.x, mins.y, maxs.z}
	};

	for(int i = 0; i < 8; i++)
	{
		points[i] = VectorTransform(points[i], trans);

		if(!WorldToScreen(points[i], points[i]))
			return false;
	}

	left = points[0].x;
	bottom = points[0].y;
	right = points[0].x;
	top = points[0].y;

	for(int i = 0; i < 8; i++)
	{
		if(left > points[i].x)
			left = points[i].x;

		if(bottom < points[i].y)
			bottom = points[i].y;

		if(right < points[i].x)
			right = points[i].x;

		if(top > points[i].y)
			top = points[i].y;
	}

	return true;
}

void LocalESP(Draw &gr, C_CSPlayer *local)
{
	if(local == nullptr)
		return;

	if(local->IsScoped())
	{
		int x, y;
		intf::engine->GetScreenCenter(x, y);

		gr.Line(x, y - 200, x, y + 200, 1, dxvk::ColorARGB(255, 0, 0, 0));
		gr.Line(x - 200, y, x + 200, y, 1, dxvk::ColorARGB(255, 0, 0, 0));
	}
}

void CornerBox(Draw &gr, float left, float top, float right, float bottom, dxvk::Color col)
{
	float width = right - left;
	float height = bottom - top;

	float s_width = width / 6.0f;
	float s_height = height / 6.0f;

	dxvk::Color shadow = dxvk::ColorARGB(100, 0, 0, 0);

	gr.FillRect(left - 1, top - 1, s_width + 2, 3, shadow);
	gr.FillRect(left - 1, top - 1, 3, s_height + 2, shadow);

	gr.FillRect(right - s_width - 1, top - 1, s_width + 2, 3, shadow);
	gr.FillRect(right - 1, top - 1, 3, s_height + 2, shadow);

	gr.FillRect(left - 1, bottom - 1, s_width + 2, 3, shadow);
	gr.FillRect(left - 1, bottom - s_height - 1, 3, s_height + 2, shadow);

	gr.FillRect(right - s_width - 1, bottom - 1, s_width + 2, 3, shadow);
	gr.FillRect(right - 1, bottom - s_height - 1, 3, s_height + 3, shadow);

	//top left
	gr.FillRect(left, top, s_width, 1, col);
	gr.FillRect(left, top, 1, s_height, col);

	//top right
	gr.FillRect(right - s_width, top, s_width, 1, col);
	gr.FillRect(right, top, 1, s_height, col);

	//bottom left
	gr.FillRect(left, bottom, s_width, 1, col);
	gr.FillRect(left, bottom - s_height, 1, s_height, col);

	//bottom right
	gr.FillRect(right - s_width, bottom, s_width, 1, col);
	gr.FillRect(right, bottom - s_height, 1, s_height + 1, col);
}

void PlayerESP(Draw &gr, C_CSPlayer *player)
{
	if(!player->IsAlive())
		return;

	float left, top, right, bottom;
	if(GetBBox(player, left, top, right, bottom))
	{
		float width = right - left;
		float height = bottom - top;

		dxvk::Color col = dxvk::ColorARGB(255, 10, 100, 200);

		if(C_CSPlayer::GetLocalPlayer()->IsOtherEnemy(player))
		{
			col = dxvk::ColorARGB(255, 100, 10, 200);
		}
		else
		{
			return;
		}

		CornerBox(gr, left, top, right, bottom, col);

		float health = static_cast<float>(player->GetHealth());

		height += 1;

		float s_height = height - (height * (health / 100.0f));
		float s_health = health * 2.55f;

		left -= 4;

		gr.FillRect(left - 1, top - 1, 3.0f, height + 2, dxvk::ColorARGB(100, 0, 0, 0));
		gr.FillRect(left, top + s_height, 1.0f, height - s_height, dxvk::ColorARGB(255, 255 - s_health, s_health, 0));

	}
}

void WeaponESP(Draw &gr, C_BaseCombatWeapon *weapon)
{
	if(weapon->OwnerEntity() != -1)
		return;

	float left, top, right, bottom;
	if(GetBBox(weapon, left, top, right, bottom))
	{
		float width = right - left;
		float height = bottom - top;

		float s_width = width / 6.0f;
		float s_height = height / 6.0f;

		dxvk::Color col = dxvk::ColorARGB(255, 200, 100, 200);

		CornerBox(gr, left, top, right, bottom, col);
	}
}

void SkeletonESP(Draw &gr, C_CSPlayer *player, matrix3x4a_t *bones)
{
	IClientRenderable *renderable = player->GetClientRenderable();

	studiohdr_t *hdr = intf::modelinfo->GetStudiomodel(renderable->GetModel());

	std::vector<std::pair<Vector, Vector>> points;

	Vector chest = GetHitbox(player, 6, bones);

	for(int i = 0; i < hdr->numbones; i++)
	{
		mstudiobone_t *bone = hdr->GetBone(i);

		if(bone && bone->flags & BONE_USED_BY_HITBOX && bone->parent != -1)
		{
			Vector child  = bones[i].GetOrigin();
			Vector parent = bones[bone->parent].GetOrigin();

			float child_sqr = (child - chest).LengthSqr();
			float parent_sqr = (parent - chest).LengthSqr();

			//use chest hitbox instead of the bone.
			if(parent_sqr < 5 * 5) parent = chest;
			if(child_sqr < 5 * 5) child = chest;

			if(WorldToScreen(child, child) && WorldToScreen(parent, parent))
			{
				points.push_back({child, parent});
			}
		}
	}

	for(auto &[child, parent] : points)
	{
		gr.Line(child.x, child.y, parent.x, parent.y, 3.0f, dxvk::ColorARGB(100, 0, 0, 0));
	}

	for(auto &[child, parent] : points)
	{
		gr.Line(child.x, child.y, parent.x, parent.y, 1.0f, dxvk::ColorARGB(255, 255, 255, 255));
	}
}

void esp::Run(Draw &gr)
{
	int max_ent = intf::entitylist->GetHighestEntityIndex();

	for(int i = 1; i <= max_ent; i++)
	{
		C_BaseEntity *entity = intf::entitylist->GetClientEntity<C_BaseEntity *>(i);

		if(entity == nullptr)
			continue;

		if(entity->IsPlayer())
		{
			C_CSPlayer *player = (C_CSPlayer *)entity;

			if(ValidPlayer(player))
			{
				PlayerESP(gr, player);

				if(!g_records[i].empty() && !player->GetClientNetworkable()->IsDormant())
				{
					SkeletonESP(gr, player, g_records[i].front().m_bones);
				}
			}
		}

		else if(entity->IsWeapon())
		{
			C_BaseCombatWeapon *weapon = (C_BaseCombatWeapon *)entity;
			WeaponESP(gr, weapon);
		}
	}

	LocalESP(gr, C_CSPlayer::GetLocalPlayer());
}