
#ifndef CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_TEXTURE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_TEXTURE_HPP_

#include "source_sdk/shaderapivk/iunknown.hpp"
#include "source_sdk/shaderapivk/d3d9_types.hpp"

namespace dxvk
{
	struct D3D9Texture : IUnknown
	{
		HResult LockRect(unsigned level, LockedRect *locked_rect)
		{
			return Call<HResult, 19>(level, locked_rect, nullptr, 0);
		}

		HResult UnlockRect(unsigned level)
		{
			return Call<HResult, 20>(level);
		}
	};
}

#endif //CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_TEXTURE_HPP_
