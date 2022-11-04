
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTUNKNOWN_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTUNKNOWN_HPP_

#include "memory/vtable_util.hpp"

struct ICollideable;
struct IClientNetworkable;
struct IClientRenderable;
struct C_BaseEntity;

struct IClientUnknown : mem::VTableUtil
{
	/*
	virtual ICollideable *GetCollideable() = 0;
	virtual IClientNetworkable *GetClientNetworkable() = 0;
	virtual IClientRenderable *GetClientRenderable() = 0;
	virtual IClientEntity *GetIClientEntity() = 0;
	virtual C_BaseEntity *GetBaseEntity() = 0;
	virtual IClientThinkable *GetClientThinkable() = 0;
	virtual IClientAlphaProperty *GetClientAlphaProperty() = 0;
*/
	IClientNetworkable *GetClientNetworkable()
	{
		return Call<IClientNetworkable *, 5>();
	}

	C_BaseEntity *GetBaseEntity()
	{
		return Call<C_BaseEntity *, 8>();
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ICLIENTUNKNOWN_HPP_
