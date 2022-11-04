
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_IGAMEMOVEMENT_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_IGAMEMOVEMENT_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/mathlib/vector.hpp"

struct C_BaseEntity;

struct CMoveData
{
	bool first_run_of_functions: 1;
	bool game_code_moved_player: 1;
	int player_handle;
	int impulse_command;
	QAngle view_angles;
	QAngle abs_view_angles;
	int buttons;
	int old_buttons;
	float forward_move;
	float side_move;
	float up_move;
	float max_speed;
	float client_max_speed;
	Vector velocity;
	QAngle angles;
	QAngle old_angles;
	float step_height;
	Vector wish_vel;
	Vector jump_vel;
	Vector constaint_center;
	float constraint_radius;
	float constraint_width;
	float constraint_speed_factor;
	float pad[5];
	Vector abs_origin;
};

struct IGameMovement : mem::VTableUtil
{
	void ProcessMovement(C_BaseEntity *entity, CMoveData *data)
	{
		return Call<void, 2>(entity, data);
	}

	void Reset()
	{
		return Call<void, 3>();
	}

	void StartTrackPredictionErrors(C_BaseEntity *entity)
	{
		return Call<void, 4>(entity);
	}

	void FinishTrackPredictionErrors(C_BaseEntity *entity)
	{
		return Call<void, 5>(entity);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_IGAMEMOVEMENT_HPP_
