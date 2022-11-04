
#ifndef CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_IUNKNOWN_HPP_
#define CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_IUNKNOWN_HPP_

#include "memory/vtable_util.hpp"

namespace dxvk
{
	struct IUnknown : mem::VTableUtil
	{
		void Release()
		{
			return Call<void, 2>();
		}
	};
}

#endif //CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_IUNKNOWN_HPP_
