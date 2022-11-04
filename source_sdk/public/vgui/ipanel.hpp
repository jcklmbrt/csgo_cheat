
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_VGUI_IPANEL_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_VGUI_IPANEL_HPP_

#include "memory/vtable_util.hpp"

struct IPanel : mem::VTableUtil
{
	void SetMouseInputEnabled(int panel, bool state)
	{
		return Call<void, 32>(panel, state);
	}

	char *GetName(int panel)
	{
		return Call<char *, 37>(panel);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_VGUI_IPANEL_HPP_
