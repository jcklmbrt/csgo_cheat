//
//Created by jack on 08/09/22.
//

#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_USERCMD_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_USERCMD_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/mathlib/vector.hpp"

struct CUserCmd : mem::VTableUtil
{
	//For matching server and client commands for debugging
	int command_number;

	//the tick the client created this command
	int tick_count;

	//Player instantaneous view angles.
	QAngle viewangles;
	Vector aimdirection; //For pointing devices.
	//Intended velocities
	//forward velocity.
	float forwardmove;
	// sideways velocity.
	float sidemove;
	// upward velocity.
	float upmove;
	//Attack button states
	int buttons;
	//Impulse command issued.
	uint8_t impulse;
	//Current weapon id
	int weaponselect;
	int weaponsubtype;

	int random_seed; //For shared random functions

	int server_random_seed; //Only the server populates this seed

	short mousedx; //mouse accum in x from create move
	short mousedy; //mouse accum in y from create move

	//Client only, tracks whether we've predicted this command at least once
	bool hasbeenpredicted;
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_USERCMD_HPP_
