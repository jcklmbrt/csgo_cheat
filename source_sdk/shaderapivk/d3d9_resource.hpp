
#ifndef CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_RESOURCE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_RESOURCE_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/shaderapivk/d3d9_types.hpp"
#include "source_sdk/shaderapivk/iunknown.hpp"

namespace dxvk
{
	struct D3D9Resource : IUnknown
	{
		HResult Lock(unsigned offset_to_lock, unsigned size_to_lock, void **data, uint32_t flags)
		{
			return Call<HResult, 11>(offset_to_lock, size_to_lock, data, flags);
		}

		HResult Unlock()
		{
			return Call<HResult, 12>();
		}
	};

	struct D3D9VertexBuffer : D3D9Resource
	{
	};

	struct D3D9IndexBuffer : D3D9Resource
	{
	};
}


#endif //CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_RESOURCE_HPP_
