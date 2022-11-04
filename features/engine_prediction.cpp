#include "features/engine_prediction.hpp"

#include "memory/interfaces.hpp"

#include "source_sdk/game/shared/usercmd.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/game/client/c_basecombatweapon.hpp"
#include "source_sdk/game/shared/cstrike15/cs_weapon_parse.hpp"
#include "source_sdk/game/shared/imovehelper.hpp"
#include "source_sdk/public/const.hpp"
#include "source_sdk/public/iprediction.hpp"
#include "source_sdk/public/globalvars_base.hpp"
#include "source_sdk/public/datacache/imdlcache.hpp"

void UpdateButtonState(C_CSPlayer *entity, int usercmd_button_mask)
{
	entity->ButtonLast() = entity->Buttons();

	entity->Buttons() = usercmd_button_mask;
	int buttons_changed = entity->ButtonLast() ^ entity->Buttons();

	entity->ButtonPressed()  = buttons_changed & entity->Buttons();
	entity->ButtonReleased() = buttons_changed & (~entity->Buttons());
}

void RunThink(C_CSPlayer *entity)
{
	int next_think_tick = entity->NextThinkTick();

	if(next_think_tick > 0 && next_think_tick <= entity->TickBase())
	{
		entity->NextThinkTick() = -1;
		entity->SetNextThink(0, -1.0f);
		entity->Think();
	}
}

void RunPreThink(C_CSPlayer *entity)
{
	if(entity->PhysicsRunThink())
	{
		entity->PreThink();
	}
}

void RunPostThink(C_CSPlayer *entity)
{
	intf::mdlcache->BeginLock();

	if(entity->IsAlive())
	{
		entity->UpdateCollisionBounds();

		if(entity->Flags() & FL_ONGROUND)
		{
			entity->FallVelocity() = 0.0f;
		}

		if(entity->Sequence() == -1)
		{
			entity->Sequence() = 0;
		}

		entity->StudioFrameAdvance();
		entity->PostThinkVPhysics();
	}

	entity->SimulatePlayerSimulatedEntities();

	intf::mdlcache->EndLock();
}

EnginePrediction::EnginePrediction(CUserCmd *cmd)
{
	C_CSPlayer *local = C_CSPlayer::GetLocalPlayer();

	int old_random_seed = cmd->random_seed;

	cmd->random_seed &= 0x7FFFFFFF;
	intf::prediction->StartCommand(local, cmd);
	cmd->random_seed = old_random_seed;

	m_curtime = intf::globals->curtime;
	m_frametime = intf::globals->frametime;

	float tickbase = static_cast<float>(local->TickBase());

	intf::globals->curtime = tickbase * intf::globals->interval_per_tick;
	intf::globals->frametime = intf::globals->interval_per_tick;

	intf::movehelper->SetHost(local);
	intf::gamemovement->StartTrackPredictionErrors(local);

	if(cmd->weaponselect)
	{
		C_BaseCombatWeapon *weapon = local->GetActiveWeapon();

		if(weapon != nullptr)
		{
			CCSWeaponInfo *wpn_info = weapon->GetCSWpnData();

			if(wpn_info != nullptr)
			{
				local->SelectItem(wpn_info->name);
			}
		}
	}

	if(cmd->impulse)
	{
		local->Impulse() = cmd->impulse;
	}

	UpdateButtonState(local, cmd->buttons);

	intf::prediction->CheckMovingGround(local, intf::globals->frametime);

	local->SetLocalViewAngles(cmd->viewangles);

	RunPreThink(local);
	RunThink(local);

	memset(&m_movedata, 0, sizeof(m_movedata));
	intf::prediction->SetupMove(local, cmd, intf::movehelper, &m_movedata);
	intf::gamemovement->ProcessMovement(local, &m_movedata);
	intf::prediction->FinishMove(local, cmd, &m_movedata);
	intf::movehelper->ProcessImpacts();

	RunPostThink(local);
}

EnginePrediction::~EnginePrediction()
{
	C_CSPlayer *local = C_CSPlayer::GetLocalPlayer();

	intf::gamemovement->FinishTrackPredictionErrors(local);
	intf::movehelper->SetHost(nullptr);
	intf::prediction->FinishCommand(local);
	intf::gamemovement->Reset();

	intf::globals->curtime = m_curtime;
	intf::globals->frametime = m_frametime;
}