
#include <cstdio>
#include <cstdarg>
#include <climits>
#include <mutex>
#include "renderer/renderer.hpp"

#include "source_sdk/shaderapivk/d3d9_resource.hpp"
#include "source_sdk/shaderapivk/d3d9_texture.hpp"
#include "source_sdk/shaderapivk/d3d9_device.hpp"
#include "source_sdk/mathlib/mathlib.hpp"

struct Vertex
{
	float x, y, z;
	dxvk::Color color;
	float u, v;
};

constexpr size_t MAX_INDEX  = USHRT_MAX;
constexpr size_t MAX_VERTEX = USHRT_MAX;

constexpr uint32_t FVF = (dxvk::D3DFVF_XYZ | dxvk::D3DFVF_DIFFUSE | dxvk::D3DFVF_TEX1);

dxvk::D3D9VertexBuffer *vertex_buffer = nullptr;
dxvk::D3D9IndexBuffer *index_buffer = nullptr;
dxvk::D3D9Texture *texture = nullptr;

uint16_t vtx;
uint16_t idx;

uint16_t *indices;
Vertex *vertices;

std::mutex mutex;

Draw::Draw()
	: m_lock(mutex)
{
	index_buffer->Lock(0, 0, (void **)&indices, 0);
	vertex_buffer->Lock(0, 0, (void **)&vertices, 0);

	vtx = 0;
	idx = 0;
}

Draw::~Draw()
{
	index_buffer->Unlock();
	vertex_buffer->Unlock();
}

void Draw::FillQuad(
	float x0, float y0,
	float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	dxvk::Color color
)
{
	if(vtx + 4 >= MAX_VERTEX || idx + 6 >= MAX_INDEX)
		return;

	//tri1
	indices[idx++] = vtx + 1;
	indices[idx++] = vtx + 0;
	indices[idx++] = vtx + 3;

	//tri2
	indices[idx++] = vtx + 1;
	indices[idx++] = vtx + 3;
	indices[idx++] = vtx + 2;

	//hacky texture color fill
	float dx1 = ((float)1 / 512);
	float dx2 = ((float)2 / 512);

	//quad
	vertices[vtx++] = {x0, y0, 1.0f, color, dx1, 0.4};
	vertices[vtx++] = {x1, y1, 1.0f, color, dx1, 0.5};
	vertices[vtx++] = {x2, y2, 1.0f, color, dx2, 0.5};
	vertices[vtx++] = {x3, y3, 1.0f, color, dx2, 0.4};
}

void Draw::FillRect(float x, float y, float w, float h, dxvk::Color color)
{
	FillQuad(x, y, x, y + h, x + w, y + h, x + w, y, color);
}

void Draw::Init(dxvk::D3D9Device *device)
{
	device->CreateIndexBuffer(
		MAX_INDEX * sizeof(uint16_t),
		dxvk::D3DUSAGE_DYNAMIC,
		dxvk::D3DFMT_INDEX16,
		dxvk::D3DPOOL_DEFAULT,
		&index_buffer
	);

	device->CreateVertexBuffer(
		MAX_VERTEX * sizeof(Vertex),
		dxvk::D3DUSAGE_DYNAMIC,
		FVF,
		dxvk::D3DPOOL_DEFAULT,
		&vertex_buffer
	);

	device->CreateTexture(
		FONT_WIDTH * CHAR_MAX,
		FONT_HEIGHT,
		1,
		dxvk::D3DUSAGE_DYNAMIC,
		dxvk::D3DFMT_A8R8G8B8,
		dxvk::D3DPOOL_DEFAULT,
		&texture
	);

	uint32_t *dst;
	uint64_t font8x8[CHAR_MAX] = {
		0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
		0x000000FF00000000, 0x000000FF00FF0000,//..
		0x1818181818181818, 0x6C6C6C6C6C6C6C6C,//..
		0x181818F800000000, 0x6C6C6CEC0CFC0000,//..
		0x1818181F00000000, 0x6C6C6C6F607F0000,//..
		0x000000F818181818, 0x000000FC0CEC6C6C,//..
		0x0000001F18181818, 0x0000007F606F6C6C,//..
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0008000000000000,//
		0x0000000000000000, 0x00180018183C3C18,// !
		0x0000000000363636, 0x006C6CFE6CFE6C6C,//"#
		0x00187ED07C16FC30, 0x0060660C18306606,//$%
		0x00DC66B61C36361C, 0x0000000000181818,//&'
		0x0030180C0C0C1830, 0x000C18303030180C,//()
		0x0000187E3C7E1800, 0x000018187E181800,//*+
		0x0C18180000000000, 0x000000007E000000,//,-
		0x0018180000000000, 0x0000060C18306000,//./
		0x003C666E7E76663C, 0x007E181818181C18,//01
		0x007E0C183060663C, 0x003C66603860663C,//23
		0x0030307E363C3830, 0x003C6660603E067E,//45
		0x003C66663E060C38, 0x000C0C0C1830607E,//67
		0x003C66663C66663C, 0x001C30607C66663C,//89
		0x0018180018180000, 0x0C18180018180000,//:;
		0x0030180C060C1830, 0x0000007E007E0000,//<=
		0x000C18306030180C, 0x001800181830663C,//>?
		0x003C06765676663C, 0x006666667E66663C,//@A
		0x003E66663E66663E, 0x003C66060606663C,//BC
		0x001E36666666361E, 0x007E06063E06067E,//DE
		0x000606063E06067E, 0x003C66667606663C,//FG
		0x006666667E666666, 0x007E18181818187E,//HI
		0x001C36303030307C, 0x0066361E0E1E3666,//JK
		0x007E060606060606, 0x00C6C6D6D6FEEEC6,//LM
		0x006666767E6E6666, 0x003C66666666663C,//NO
		0x000606063E66663E, 0x006C36566666663C,//PQ
		0x006666363E66663E, 0x003C66603C06663C,//RS
		0x001818181818187E, 0x003C666666666666,//TU
		0x00183C6666666666, 0x00C6EEFED6D6C6C6,//VW
		0x0066663C183C6666, 0x001818183C666666,//XY
		0x007E060C1830607E, 0x003E06060606063E,//Z[
		0x00006030180C0600, 0x007C60606060607C,//\]
		0x000000000000663C, 0xFFFF000000000000,//^_
		0x000000000030180C, 0x007C667C603C0000,//`a
		0x003E6666663E0606, 0x003C6606663C0000,//bc
		0x007C6666667C6060, 0x003C067E663C0000,//de
		0x000C0C0C3E0C0C38, 0x3C607C66667C0000,//fg
		0x00666666663E0606, 0x003C1818181C0018,//hi
		0x0E181818181C0018, 0x0066361E36660606,//jk
		0x003C18181818181C, 0x00C6D6D6FE6C0000,//lm
		0x00666666663E0000, 0x003C6666663C0000,//no
		0x06063E66663E0000, 0xE0607C66667C0000,//pq
		0x000606066E360000, 0x003E603C067C0000,//rs
		0x00380C0C0C3E0C0C, 0x007C666666660000,//tu
		0x00183C6666660000, 0x006CFED6D6C60000,//vw
		0x00663C183C660000, 0x3C607C6666660000,//xy
		0x007E0C18307E0000, 0x003018180E181830,//z{
		0x0018181818181818, 0x000C18187018180C,//|}
		0x000000000062D68C,                    //~
	};

	dxvk::LockedRect rect = {0};
	texture->LockRect(0, &rect);

	for(int ch = 0; ch < CHAR_MAX; ch++)
		for(int y = 0; y < FONT_HEIGHT; y++)
			for(int x = 0; x < FONT_WIDTH; x++)
			{
				dst = (uint32_t *)((uint8_t *)rect.bits + y * rect.pitch) + x + ch * FONT_WIDTH;

				if((font8x8[ch] >> (x + (y * FONT_WIDTH))) & 1)
					*dst = dxvk::ColorARGB(255, 255, 255, 255);
				else
					*dst = dxvk::ColorARGB(0, 0, 0, 0);
			}

	texture->UnlockRect(0);
}

void Draw::Free()
{
	index_buffer->Release();
	vertex_buffer->Release();
	texture->Release();
}

void Draw::PutCh(
	float x, float y,
	dxvk::Color color,
	char ch
)
{
	if(vtx + 4 >= MAX_VERTEX || idx + 6 >= MAX_INDEX)
		return;

	if(!isprint(ch))
		ch = '?';

	float tx1 = ((float)(ch + 0) / CHAR_MAX); // start pos
	float tx2 = ((float)(ch + 1) / CHAR_MAX); // end pos

	//tri1
	indices[idx++] = vtx + 1;
	indices[idx++] = vtx + 0;
	indices[idx++] = vtx + 3;

	//tri2
	indices[idx++] = vtx + 1;
	indices[idx++] = vtx + 3;
	indices[idx++] = vtx + 2;

	//quad
	vertices[vtx++] = {x, y, 1.0f, color, tx1, 0};
	vertices[vtx++] = {x, y + Draw::FONT_HEIGHT, 1.0f, color, tx1, 1};
	vertices[vtx++] = {x + Draw::FONT_WIDTH, y + Draw::FONT_HEIGHT, 1.0f, color, tx2, 1};
	vertices[vtx++] = {x + Draw::FONT_WIDTH, y, 1.0f, color, tx2, 0};
}

void Draw::PutS(float x, float y, dxvk::Color color, const char *str)
{
	float dx = 0;
	float dy = 0;

	while(*str)
	{
		char ch = *str;

		if(ch == '\n')
		{
			dx = 0;
			dy += Draw::FONT_HEIGHT + 1;
		}
		else
		{
			int a = (color >> 24) & 0xFF; // scale shadow alpha by foreground alpha.
			PutCh(x + dx + 1, y + dy + 1, dxvk::ColorARGB(a / 3, 0, 0, 0), ch);
			PutCh(x + dx, y + dy, color, ch);
			dx += Draw::FONT_WIDTH;
		}
		str++;
	}
}

void Draw::PrintF(float x, float y, dxvk::Color color, const char *fmt, ...)
{
	char buf[2048];

	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 2048, fmt, args);
	va_end(args);

	PutS(x, y, color, buf);
}

void Draw::Line(
	float x0, float y0,
	float x1, float y1,
	float thickness,
	dxvk::Color color
) {
	float dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;

	float inv_len = InvSqrt(dy * dy + dx * dx);

	dx *= inv_len * thickness * 0.5f;
	dy *= inv_len * thickness * 0.5f;

	FillQuad(
		x0 + dy, y0 - dx,
		x0 - dy, y0 + dx,
		x1 - dy, y1 + dx,
		x1 + dy, y1 - dx,
		color
	);
}

void Draw::Run(dxvk::D3D9Device *device)
{
	auto lock = std::unique_lock(mutex);

	dxvk::D3D9StateBlock *stateblock = nullptr;
	device->CreateStateBlock(dxvk::D3DSBT_ALL, &stateblock);

	if(stateblock->Capture() < 0)
	{
		stateblock->Release();
		return;
	}

	device->SetRenderState(dxvk::D3DRS_FILLMODE, dxvk::D3DFILL_SOLID);
	device->SetRenderState(dxvk::D3DRS_SHADEMODE, dxvk::D3DSHADE_GOURAUD);
	device->SetRenderState(dxvk::D3DRS_ZWRITEENABLE, false);
	device->SetRenderState(dxvk::D3DRS_ALPHATESTENABLE, false);
	device->SetRenderState(dxvk::D3DRS_CULLMODE, dxvk::D3DCULL_NONE);
	device->SetRenderState(dxvk::D3DRS_ZENABLE, false);
	device->SetRenderState(dxvk::D3DRS_ALPHABLENDENABLE, true);
	device->SetRenderState(dxvk::D3DRS_BLENDOP, dxvk::D3DBLENDOP_ADD);
	device->SetRenderState(dxvk::D3DRS_SRCBLEND, dxvk::D3DBLEND_SRCALPHA);
	device->SetRenderState(dxvk::D3DRS_DESTBLEND, dxvk::D3DBLEND_INVSRCALPHA);
	device->SetRenderState(dxvk::D3DRS_SEPARATEALPHABLENDENABLE, true);
	device->SetRenderState(dxvk::D3DRS_SRCBLENDALPHA, dxvk::D3DBLEND_ONE);
	device->SetRenderState(dxvk::D3DRS_DESTBLENDALPHA, dxvk::D3DBLEND_INVSRCALPHA);
	device->SetRenderState(dxvk::D3DRS_SCISSORTESTENABLE, true);
	device->SetRenderState(dxvk::D3DRS_FOGENABLE, false);
	device->SetRenderState(dxvk::D3DRS_RANGEFOGENABLE, false);
	device->SetRenderState(dxvk::D3DRS_SPECULARENABLE, false);
	device->SetRenderState(dxvk::D3DRS_STENCILENABLE, false);
	device->SetRenderState(dxvk::D3DRS_CLIPPING, true);
	device->SetRenderState(dxvk::D3DRS_LIGHTING, false);

	device->SetTextureStageState(0, dxvk::D3DTSS_COLOROP, dxvk::D3DTOP_MODULATE);
	device->SetTextureStageState(0, dxvk::D3DTSS_COLORARG1, dxvk::D3DTA_TEXTURE);
	device->SetTextureStageState(0, dxvk::D3DTSS_COLORARG2, dxvk::D3DTA_DIFFUSE);
	device->SetTextureStageState(0, dxvk::D3DTSS_ALPHAOP, dxvk::D3DTOP_MODULATE);
	device->SetTextureStageState(0, dxvk::D3DTSS_ALPHAARG1, dxvk::D3DTA_TEXTURE);
	device->SetTextureStageState(0, dxvk::D3DTSS_ALPHAARG2, dxvk::D3DTA_DIFFUSE);
	device->SetTextureStageState(1, dxvk::D3DTSS_COLOROP, dxvk::D3DTOP_DISABLE);
	device->SetTextureStageState(1, dxvk::D3DTSS_ALPHAOP, dxvk::D3DTOP_DISABLE);

	dxvk::ViewPort viewport = {0};
	device->GetViewPort(&viewport);

	float l = 0.5f;
	float r = (float)viewport.w + 0.5f;
	float t = 0.5f;
	float b = (float)viewport.h + 0.5f;
	dxvk::Matrix projection = {
		.m = {
			{2.0f / (r - l), 0.0f, 0.0f, 0.0f},
			{0.0f, 2.0f / (t - b), 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{(r + l) / (l - r), (t + b) / (b - t), 0.0f, 1.0f}},
	};

	device->SetTransform(dxvk::D3DTS_PROJECTION, &projection);

	device->SetTexture(0, texture);

	device->SetFVF(FVF);
	device->SetStreamSource(0, vertex_buffer, 0, sizeof(Vertex));

	device->SetIndices(index_buffer);

	device->DrawIndexedPrimitive(dxvk::D3DPT_TRIANGLELIST, 0, 0, vtx, 0, vtx / 2);

	stateblock->Apply();
}