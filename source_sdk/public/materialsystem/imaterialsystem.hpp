
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_MATERIALSYSTEM_IMATERIALSYSTEM_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_MATERIALSYSTEM_IMATERIALSYSTEM_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/tier1/keyvalues.hpp"
#include "source_sdk/public/materialsystem/imaterial.hpp"

struct IMaterialSystem :mem::VTableUtil
{
	IMaterial *CreateMaterial(const char *name, KeyValues *kv)
	{
		return Call<IMaterial *, 83>(name, kv);
	}

	IMaterial *FindMaterial(const char *name) {
		return Call<IMaterial *, 84>(name, nullptr, true, nullptr);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_MATERIALSYSTEM_IMATERIALSYSTEM_HPP_
