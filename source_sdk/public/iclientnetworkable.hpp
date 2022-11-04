
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTNETWORKABLE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTNETWORKABLE_HPP_

#include "memory/vtable_util.hpp"

struct ClientClass;

struct IClientNetworkable : mem::VTableUtil
{
	ClientClass *GetClientClass()
	{
		return Call<ClientClass *, 2>();
	}

	bool IsDormant()
	{
		return Call<bool, 9>();
	}

	int entindex()
	{
		return Call<int, 10>();
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTNETWORKABLE_HPP_
