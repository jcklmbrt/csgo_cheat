
#ifndef CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_DEVICE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_DEVICE_HPP_

#include "memory/vtable_util.hpp"
#include "source_sdk/shaderapivk/d3d9_types.hpp"
#include "source_sdk/shaderapivk/d3d9_resource.hpp"
#include "source_sdk/shaderapivk/d3d9_texture.hpp"
#include "source_sdk/shaderapivk/d3d9_stateblock.hpp"

namespace dxvk
{
	struct D3D9Device : mem::VTableUtil
	{
		HResult CreateTexture(
			unsigned w,
			unsigned h,
			unsigned levels,
			uint32_t usage,
			uint32_t format,
			uint32_t pool,
			D3D9Texture **texture
		)
		{
			return Call<HResult, 23>(
				w,
				h,
				levels,
				usage,
				format,
				pool,
				texture,
				nullptr
			);
		}

		HResult CreateVertexBuffer(
			unsigned length,
			uint32_t usage,
			uint32_t fvf,
			D3D9Pool pool,
			D3D9VertexBuffer **vertexbuffer
		)
		{
			return Call<HResult, 26>(
				length,
				usage,
				fvf,
				pool,
				vertexbuffer,
				nullptr
			);
		};

		HResult CreateIndexBuffer(
			unsigned length,
			uint32_t usage,
			D3D9Format format,
			D3D9Pool pool,
			D3D9IndexBuffer **indexbuffer
		)
		{
			return Call<HResult, 27>(
				length,
				usage,
				format,
				pool,
				indexbuffer,
				nullptr
			);
		};

		HResult SetTransform(D3D9TransformStateType state, Matrix *matrix)
		{
			return Call<HResult, 44>(state, matrix);
		}

		HResult GetViewPort(ViewPort *viewport)
		{
			return Call<HResult, 48>(viewport);
		}

		HResult SetRenderState(D3D9RenderStateType state, uint32_t value)
		{
			return Call<HResult, 57>(state, value);
		}

		HResult CreateStateBlock(D3D9StateBlockType type, D3D9StateBlock **stateblock)
		{
			return Call<HResult, 59>(type, stateblock);
		}

		HResult SetTexture(uint32_t stage, D3D9Texture *texture)
		{
			return Call<HResult, 65>(stage, texture);
		}

		HResult SetTextureStageState(uint32_t stage,D3D9TextureStageState type,uint32_t value)
		{
			return Call<HResult, 67>(stage, type, value);
		}

		HResult DrawIndexedPrimitive(
			D3D9PrimitiveType type,
			int base_vertex_index,
			unsigned min_vertex_index,
			unsigned num_vertices,
			unsigned start_index,
			unsigned prim_count
		)
		{
			return Call<HResult, 82>(
				type,
				base_vertex_index,
				min_vertex_index,
				num_vertices,
				start_index,
				prim_count
			);
		}

		HResult SetFVF(uint32_t fvf)
		{
			return Call<HResult, 89>(fvf);
		}

		HResult SetStreamSource(
			unsigned stream_number,
			D3D9VertexBuffer *stream_data,
			unsigned offset,
			unsigned stride
		)
		{
			return Call<HResult, 100>(stream_number, stream_data, offset, stride);
		}

		HResult SetIndices(D3D9IndexBuffer *indices)
		{
			return Call<HResult, 104>(indices);
		}

	};
}

#endif //CSGO_CHEAT_SOURCE_SDK_SHADERAPIVK_D3D9_DEVICE_HPP_
