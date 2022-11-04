
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_VPHYSICS_INTERFACE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_VPHYSICS_INTERFACE_HPP_

#include "memory/vtable_util.hpp"

struct surfacedata_t
{
	char pad0[80];
	float max_speed_factor;
	float jump_factor;
	float penetration_modifier;
	float damage_modifier;
	short material;
	bool climbable;
};

struct IPhysicsSurfaceProps : mem::VTableUtil
{
	surfacedata_t *GetSurfaceData(int index)
	{
		return Call<surfacedata_t *, 5>(index);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_VPHYSICS_INTERFACE_HPP_
