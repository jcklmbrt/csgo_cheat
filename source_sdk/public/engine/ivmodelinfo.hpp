
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_IVMODELINFO_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_IVMODELINFO_HPP_

#include "memory/vtable_util.hpp"

struct model_t;
struct studiohdr_t;

struct IVModelInfoClient :mem::VTableUtil
{
	auto GetStudiomodel(model_t *model)
	{
		return Call<studiohdr_t *, 31>(model);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_IVMODELINFO_HPP_
