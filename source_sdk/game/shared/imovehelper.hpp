#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_IMOVEHELPER_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_IMOVEHELPER_HPP_

#include "memory/vtable_util.hpp"

struct C_BaseEntity;

struct IMoveHelper : mem::VTableUtil
{
	void SetHost(C_BaseEntity *host)
	{
		Call<void, 1>(host);
	}

	void ProcessImpacts()
	{
		Call<void, 4>();
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_IMOVEHELPER_HPP_
