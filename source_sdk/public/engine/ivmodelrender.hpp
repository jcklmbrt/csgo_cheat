
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_IVMODELRENDER_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_IVMODELRENDER_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/public/materialsystem/imaterial.hpp"
#include "source_sdk/mathlib/vector.hpp"

struct IClientRenderable;
struct model_t;
struct matrix3x4_t;

typedef unsigned short ModelInstanceHandle_t;

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	char pad0[4];
	IClientRenderable *renderable;
	model_t *model;
	matrix3x4_t *model_to_world;
	matrix3x4_t *lighting_offset;
	Vector *lighting_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
};

struct IVModelRender : mem::VTableUtil
{
	void ForcedMaterialOverride(IMaterial *pMat)
	{
		return Call<void, 1>(pMat, 0, 0);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_ENGINE_IVMODELRENDER_HPP_
