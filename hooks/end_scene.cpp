#include "renderer/renderer.hpp"

dxvk::HResult(*EndScene)(dxvk::D3D9Device *device);
dxvk::HResult hkEndScene(dxvk::D3D9Device *device)
{
	Draw::Run(device);
	return EndScene(device);
}