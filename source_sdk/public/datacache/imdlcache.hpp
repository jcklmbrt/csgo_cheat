
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_DATACACHE_IMDLCACHE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_DATACACHE_IMDLCACHE_HPP_

#include "memory/vtable_util.hpp"

struct IMDLCache : mem::VTableUtil
{
	void BeginLock()
	{
		return Call<void, 33>();
	}
	void EndLock()
	{
		return Call<void, 34>();
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_DATACACHE_IMDLCACHE_HPP_
