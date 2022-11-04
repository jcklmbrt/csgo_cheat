#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_BONE_MERGE_CACHE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_BONE_MERGE_CACHE_HPP_

#include "memory/function_pointers.hpp"

struct CBoneMergeCache
{
	void *operator new(size_t size)
	{
		return intf::memalloc->Alloc(size);
	}

	void operator delete(void *mem)
	{
		return intf::memalloc->Free(mem);
	}

	CBoneMergeCache()
	{
		fptr::CBoneMergeCache_CBoneMergeCache(this);
	}

	void Init(C_BaseAnimating *owner)
	{
		fptr::CBoneMergeCache_Init(this, owner);
	}

	void CopyFromFollow(Vector *follow_pos, Quaternion *follow_q, int mask, Vector *my_pos, Quaternion *my_q)
	{
		fptr::CBoneMergeCache_CopyFromFollow(this, follow_pos, follow_q, mask, my_pos, my_q);
	}

	void CopyToFollow(Vector *my_pos, Quaternion *my_q, int mask, Vector *follow_pos, Quaternion *follow_q)
	{
		fptr::CBoneMergeCache_CopyToFollow(this, my_pos, my_q, mask, follow_pos, follow_q);
	}

	void MergeMatchingPoseParams()
	{
		fptr::CBoneMergeCache_MergeMatchingPoseParams(this);
	}

	char pad0[0xC8];
	unsigned short raw_index_mapping[MAX_STUDIO_BONES];
	bool force_cache_clear;
	char pad1[6];
};

ASSERT_SIZE(CBoneMergeCache, 0x2D0)

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_BONE_MERGE_CACHE_HPP_
