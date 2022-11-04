
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_ICOLLIDEABLE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_ICOLLIDEABLE_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/mathlib/mathlib.hpp"

struct ICollideable :mem::VTableUtil
{
	Vector OBBMins()
	{
		return *Call<Vector *, 1>();
	};

	Vector OBBMaxs()
	{
		return *Call<Vector *, 2>();
	};
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_ICOLLIDEABLE_HPP_
