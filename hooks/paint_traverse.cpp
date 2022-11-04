#include "util/strtools.hpp"
#include "util/fmt.hpp"
#include "memory/interfaces.hpp"

#include "source_sdk/public/vgui/ipanel.hpp"

#include "features/esp.hpp"

void(*PaintTraverse)(IPanel *panel, int vgui_panel, bool force_repaint, bool allow_force);
void hkPaintTraverse(IPanel *panel, int vgui_panel, bool force_repaint, bool allow_force)
{
	const char *name = intf::panel->GetName(vgui_panel);

	switch(FNV(name))
	{
	case FNV("HudZoom"):
		//remove scope
		return;
		break;

	case FNV("FocusOverlayPanel"):
		//intf::panel->SetMouseInputEnabled(vgui_panel, 1);
		break;

	case FNV("MatSystemTopPanel"):
		{
			Draw gr;
			fmt::DrawLog(gr);
			esp::Run(gr);
			break;
		}
	}

	PaintTraverse(panel, vgui_panel, force_repaint, allow_force);
}