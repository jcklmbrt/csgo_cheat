
#ifndef CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_STATEBLOCK_HPP_
#define CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_STATEBLOCK_HPP_

#include "source_sdk/shaderapivk/d3d9_types.hpp"
#include "source_sdk/shaderapivk/iunknown.hpp"

namespace dxvk
{
	struct D3D9StateBlock : IUnknown
	{
		HResult Capture()
		{
			return Call<HResult, 4>();
		}

		HResult Apply()
		{
			return Call<HResult, 5>();
		}
	};
}

#endif //CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_STATEBLOCK_HPP_
