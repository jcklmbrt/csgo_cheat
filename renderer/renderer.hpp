
#ifndef CSGO_CHEAT_RENDERER_RENDERER_HPP_
#define CSGO_CHEAT_RENDERER_RENDERER_HPP_

#include <mutex>
#include "source_sdk/shaderapivk/d3d9_types.hpp"

struct Draw
{
	Draw();
	~Draw();

	static void Init(dxvk::D3D9Device *device);
	static void Run(dxvk::D3D9Device *device);
	static void Free();

	static constexpr size_t FONT_WIDTH = 8;
	static constexpr size_t FONT_HEIGHT = 8;

	//primitives
	void FillQuad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, dxvk::Color color);
	void FillRect(float x, float y, float w, float h, dxvk::Color color);
	void Line(float x0, float y0, float x1, float y1, float thickness, dxvk::Color color);

	//text
	void PutCh(float x, float y, dxvk::Color color, char ch);
	void PutS(float x, float y, dxvk::Color color, const char *str);
	void PrintF(float x, float y, dxvk::Color color, const char *fmt, ...);

	std::unique_lock<std::mutex> m_lock;
};

#endif //CSGO_CHEAT_RENDERER_RENDERER_HPP_
