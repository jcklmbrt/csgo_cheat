#include "features/movement.hpp"
#include "features/engine_prediction.hpp"

#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/game/shared/in_buttons.hpp"
#include "source_sdk/game/shared/usercmd.hpp"
#include "source_sdk/public/const.hpp"

static bool g_on_ground = true;

void BunnyHop_PrePred(C_CSPlayer *local)
{
	g_on_ground = local->Flags() & FL_ONGROUND;
}

void BunnyHop_PostPred(EnginePrediction &pred, C_CSPlayer *local, CUserCmd *cmd)
{
	if(!g_on_ground && (local->Flags() & FL_ONGROUND))
	{
		cmd->buttons &= ~IN_JUMP;
	}
}