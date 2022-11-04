
#ifndef CSGO_CHEAT_SOURCE_SDK_ENGINE_GAMEEVENTMANAGER_HPP_
#define CSGO_CHEAT_SOURCE_SDK_ENGINE_GAMEEVENTMANAGER_HPP_

#include "memory/vtable_util.hpp"

struct CGameEvent : mem::VTableUtil
{
	const char *GetName()
	{
		return Call<const char *, 1>();
	}

	int GetInt(const char *name)
	{
		return Call<int, 6>(name, 0);
	}
};

struct IGameEventManager2 : mem::VTableUtil
{
};

#endif //CSGO_CHEAT_SOURCE_SDK_ENGINE_GAMEEVENTMANAGER_HPP_
