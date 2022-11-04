
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_INPUT_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_INPUT_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/mathlib/vector.hpp"

struct CUserCmd;

struct CInput : mem::VTableUtil {
	char   pad0[165];
	bool   camera_in_third_person;
	char   pad1[2];
	Vector camera_offset;

	CUserCmd *GetUserCmd(int slot, int seq_num)
	{
		return Call<CUserCmd *, 8>(slot, seq_num);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_INPUT_HPP_
