
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_IPREDICTION_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_IPREDICTION_HPP_

#include "memory/vtable_util.hpp"
#include "memory/function_pointers.hpp"
#include "source_sdk/mathlib/vector.hpp"

struct IMoveHelper;
struct C_CSPlayer;
struct C_BaseEntity;
struct CUserCmd;
struct CMoveData;

struct IPrediction : mem::VTableUtil
{
	void CheckMovingGround(C_CSPlayer *player, double frame_time)
	{
		Call<void, 19>(player, frame_time);
	}

	void SetupMove(C_BaseEntity *entity, CUserCmd *cmd, IMoveHelper *helper, CMoveData *data)
	{
		return Call<void, 21>(entity, cmd, helper, data);
	}

	void FinishMove(C_BaseEntity *entity, CUserCmd *cmd, CMoveData *data)
	{
		return Call<void, 22>(entity, cmd, data);
	}

	void StartCommand(C_BaseEntity *entity, CUserCmd *cmd)
	{
		fptr::CPrediction_StartCommand(this, entity, cmd);
	}

	void FinishCommand(C_BaseEntity *entity)
	{
		fptr::CPrediction_FinishCommand(this, entity);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_IPREDICTION_HPP_
