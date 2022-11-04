#include "source_sdk/game/client/iclientmode.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/game/shared/usercmd.hpp"

#include "features/player_lagcompensation.hpp"
#include "features/engine_prediction.hpp"
#include "features/movement.hpp"

bool(*CreateMove)(IClientMode *clientmode, float input_sample_time, CUserCmd *cmd);
bool hkCreateMove(IClientMode *clientmode, float input_sample_time, CUserCmd *cmd)
{
	bool res = CreateMove(clientmode, input_sample_time, cmd);

	if(!cmd || !cmd->command_number)
	{
		return res;
	}

	C_CSPlayer *local = C_CSPlayer::GetLocalPlayer();

	if(local == nullptr || !local->IsAlive())
	{
		return res;
	}

	bool *send_packet = (bool *)__builtin_frame_address(2) - 0x18;

	BunnyHop_PrePred(local);

	{
		auto pred = EnginePrediction(cmd);

		PlayerRecord::BackTrack(cmd);

		BunnyHop_PostPred(pred, local, cmd);
	}

	return res;
}