#include <algorithm>
#include <cmath>

#include "util/fmt.hpp"

#include "memory/interfaces.hpp"

#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/public/engine/icollideable.hpp"
#include "source_sdk/public/cdll_int.hpp"
#include "source_sdk/game/shared/usercmd.hpp"
#include "source_sdk/public/globalvars_base.hpp"
#include "source_sdk/public/iclientnetworkable.hpp"
#include "source_sdk/public/engine/ivmodelinfo.hpp"
#include "source_sdk/public/iclientrenderable.hpp"
#include "source_sdk/public/icliententitylist.hpp"
#include "source_sdk/public/inetchannelinfo.hpp"
#include "source_sdk/public/icvar.hpp"
#include "source_sdk/tier1/convar.hpp"
#include "source_sdk/game/shared/in_buttons.hpp"
#include "source_sdk/engine/gl_model_private.hpp"
#include "source_sdk/game/shared/cstrike15/cs_weapon_parse.hpp"
#include "source_sdk/game/client/c_basecombatweapon.hpp"

#include "features/player_lagcompensation.hpp"
#include "features/setup_bones.hpp"
#include "features/player_util.hpp"

inline int TIME2TICKS(float time)
{
	float fl_tick = 0.5f + time / intf::globals->interval_per_tick;
	return static_cast<int>(fl_tick);
}

inline float TICKS2TIME(int ticks)
{
	float fl_tick = static_cast<float>(ticks);
	return fl_tick * intf::globals->interval_per_tick;
}

float GetLerpTime()
{
	static ConVar *cl_interp_ratio = intf::cvar->FindVar("cl_interp_ratio");
	static ConVar *sv_client_max_interp_ratio = intf::cvar->FindVar("sv_client_max_interp_ratio");
	static ConVar *sv_client_min_interp_ratio = intf::cvar->FindVar("sv_client_min_interp_ratio");
	static ConVar *cl_interp = intf::cvar->FindVar("cl_interp");
	static ConVar *sv_maxupdaterate = intf::cvar->FindVar("sv_maxupdaterate");

	float ratio = cl_interp_ratio->GetFloat();
	float max_ratio = sv_client_max_interp_ratio->GetFloat();
	float min_ratio = sv_client_min_interp_ratio->GetFloat();

	ratio = std::clamp(ratio, min_ratio, max_ratio);

	return std::max(cl_interp->GetFloat(), ratio / sv_maxupdaterate->GetFloat());
}

int PlayerRecord::Tick()
{
	return TIME2TICKS(m_simulation_time + GetLerpTime());
}

PlayerRecord::PlayerRecord(C_CSPlayer *player)
{
	m_simulation_time = player->SimulationTime();
	m_origin = player->VecOrigin();
	m_angles = player->EyeAngles();

	player->SetAbsOrigin(m_origin);
	player->SetAbsAngles(m_angles);
	player->InvalidateBoneCache();
	player->UpdateClientsideAnimation();

	ICollideable *collideable = player->GetCollideable();
	m_obb_maxs = collideable->OBBMaxs();
	m_obb_mins = collideable->OBBMaxs();

	SetupBones(player, m_bones, BONE_USED_BY_ANYTHING);
}

bool PlayerRecord::Valid()
{
	static ConVar *sv_maxunlag = intf::cvar->FindVar("sv_maxunlag");

	INetChannelInfo *nci = intf::engine->GetNetChannelInfo();

	if(nci == nullptr)
		return false;

	int dead_time = intf::globals->curtime - sv_maxunlag->GetFloat();

	if(m_simulation_time < dead_time)
		return false;

	float correct = 0.0f;
	correct += nci->GetLatency(FLOW_INCOMING);
	correct += nci->GetLatency(FLOW_OUTGOING);
	correct += GetLerpTime();

	// check bounds [0,sv_maxunlag]
	correct = std::clamp(correct, 0.0f, sv_maxunlag->GetFloat());

	// calculate difference between tick sent by player and our latency based tick
	float delta = correct - (intf::globals->curtime - m_simulation_time);

	return std::abs(delta) <= 0.2f;
}

void PlayerRecord::Store()
{
	for(int i = 1; i <= intf::globals->max_clients; i++)
	{
		C_CSPlayer *player = intf::entitylist->GetClientEntity<C_CSPlayer *>(i);

		std::deque<PlayerRecord> &record = g_records[i];

		if(ValidPlayer(player) && player->IsOtherEnemy(C_CSPlayer::GetLocalPlayer()))
		{
			if(record.empty() || record.front().m_simulation_time != player->SimulationTime())
			{
				record.emplace_front(player);
			}

			while(record.size() > 8 && !record.back().Valid())
			{
				record.pop_back();
			}
		}
		else
		{
			record.clear();
		}
	}
}

void PlayerRecord::BackTrack(CUserCmd *cmd)
{
	if(!(cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2))
		return;

	C_CSPlayer *local = C_CSPlayer::GetLocalPlayer();

	if(local == nullptr || !CanShoot(local))
		return;

	float best_fov = 20.0f;
	Vector eye_pos = local->GetEyePosition();
	QAngle aim_punch = local->GetAimPunch();

	for(int i = 1; i <= intf::globals->max_clients; i++)
	{
		C_CSPlayer *player = intf::entitylist->GetClientEntity<C_CSPlayer *>(i);

		if(ValidPlayer(player) && player->IsOtherEnemy(local))
		{
			for(PlayerRecord &record : g_records[i])
			{
				Vector head = GetHitbox(player, 0, record.m_bones);
				QAngle target = VectorAngles(head - eye_pos);
				QAngle delta = target - (cmd->viewangles + aim_punch);

				float fov = std::hypot(delta.x, delta.y);

				if(fov < best_fov)
				{
					best_fov = fov;
					cmd->tick_count = record.Tick();
				}
			}
		}
	}
}