
#include "hooks/hooks.hpp"

#include "source_sdk/shaderapivk/d3d9_types.hpp"
#include "source_sdk/shaderapivk/d3d9_device.hpp"
#include "source_sdk/public/vgui/ipanel.hpp"
#include "source_sdk/public/engine/ivmodelrender.hpp"
#include "source_sdk/game/client/iclientmode.hpp"
#include "source_sdk/public/cdll_int.hpp"

#include "memory/interfaces.hpp"
#include "memory/function_pointers.hpp"

#include "renderer/renderer.hpp"

float(*GetViewModelFOV)(IClientMode *clientmode);
float hkGetViewModelFOV(IClientMode *clientmode)
{
	return 120.0f;
}

bool hkShouldDrawFog(IClientMode *clientmode)
{
	return false;
}

extern dxvk::HResult(*EndScene)(dxvk::D3D9Device *device);
extern dxvk::HResult hkEndScene(dxvk::D3D9Device *device);

extern bool(*IsHLTV)(IVEngineClient *engine);
extern bool hkIsHLTV(IVEngineClient *engine);

extern bool(*IsPaused)(IVEngineClient *engine);
extern bool hkIsPaused(IVEngineClient *engine);

extern void(*DrawModelExecute)(IVModelRender *modelrender, void *ctx, void *state, ModelRenderInfo_t *info, matrix3x4_t *bone_to_world);
extern void hkDrawModelExecute(IVModelRender *modelrender, void *ctx, void *state, ModelRenderInfo_t *info, matrix3x4_t *bone_to_world);

extern void (*FrameStageNotify)(IBaseClientDLL *client, ClientFrameStage_t stage);
extern void hkFrameStageNotify(IBaseClientDLL *client, ClientFrameStage_t stage);

extern bool(*CreateMove)(IClientMode *clientmode, float input_sample_time, CUserCmd *cmd);
extern bool hkCreateMove(IClientMode *clientmode, float input_sample_time, CUserCmd *cmd);

extern void(*PaintTraverse)(IPanel *panel, int vgui_panel, bool force_repaint, bool allow_force);
extern void hkPaintTraverse(IPanel *panel, int vgui_panel, bool force_repaint, bool allow_force);

extern bool(*WriteUsercmdDeltaToBuffer)(IBaseClientDLL *client, int slot, bf_write *buf, int from, int to, bool isnewcommand);
extern bool hkWriteUsercmdDeltaToBuffer(IBaseClientDLL *client, int slot, bf_write *buf, int from, int to, bool isnewcommand);

void hook::Init()
{
	dxvk::D3D9Device *device = *fptr::CShaderDeviceDx8_Dx9Device();
	IClientMode *clientmode = fptr::GetClientModeNormal();

	Draw::Init(device);

	device->Hook(42, (void *)&hkEndScene, (void **)&EndScene);

	intf::panel->Hook(42, (void *)&hkPaintTraverse, (void **)&PaintTraverse);
	intf::client->Hook(37, (void *)&hkFrameStageNotify, (void **)&FrameStageNotify);
	intf::client->Hook(24, (void *)&hkWriteUsercmdDeltaToBuffer, (void **)&WriteUsercmdDeltaToBuffer);
	intf::engine->Hook(93, (void *)&hkIsHLTV, (void **)&IsHLTV);
	intf::engine->Hook(82, (void *)&hkIsPaused, (void **)&IsPaused);
	intf::modelrender->Hook(21, (void *)&hkDrawModelExecute, (void **)&DrawModelExecute);

	clientmode->Hook(18, (void *)&hkShouldDrawFog);
	clientmode->Hook(25, (void *)&hkCreateMove, (void **)&CreateMove);
	clientmode->Hook(36, (void *)&hkGetViewModelFOV, (void **)&GetViewModelFOV);
}