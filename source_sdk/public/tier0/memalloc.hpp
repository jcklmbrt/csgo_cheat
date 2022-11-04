#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_TIER0_MEMALLOC_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_TIER0_MEMALLOC_HPP_

#include "memory/vtable_util.hpp"

struct IMemAlloc : mem::VTableUtil
{
	void *Alloc(size_t size)
	{
		return Call<void *, 0>(size);
	}

	void Free(void *mem)
	{
		return Call<void, 2>(mem);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_TIER0_MEMALLOC_HPP_
