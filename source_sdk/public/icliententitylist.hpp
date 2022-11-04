
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTENTITYLIST_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTENTITYLIST_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/public/basehandle.hpp"

//typedef CBaseHandle ClientEntityHandle_t;

struct IClientEntityList : mem::VTableUtil
{
	template<typename T>
	T GetClientEntity(int index)
	{
		return Call<T, 3>(index);
	}

	template<typename T>
	T GetClientEntityFromHandle(int index)
	{
		return Call<T, 4>(&index);
	}

	int GetHighestEntityIndex()
	{
		return Call<int, 6>();
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTENTITYLIST_HPP_
