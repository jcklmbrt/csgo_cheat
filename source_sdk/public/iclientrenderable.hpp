
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTRENDERABLE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTRENDERABLE_HPP_

#include "memory/vtable_util.hpp"

struct IClientUnknown;
struct matrix3x4_t;
struct model_t;

struct IClientRenderable : mem::VTableUtil
{
	IClientUnknown *GetIClientUnknown()
	{
		return Call<IClientUnknown *, 0>();
	}

	model_t *GetModel()
	{
		return Call<model_t *, 8>();
	}

	bool SetupBones(matrix3x4_t *matrix, int bone_count, int mask, float time)
	{
		return Call<bool, 13>(matrix, bone_count, mask, time);
	}

	matrix3x4_t &RenderableToWorldTransform()
	{
		return Call<matrix3x4_t &, 32>();
	}

};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTRENDERABLE_HPP_
