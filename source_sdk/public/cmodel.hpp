
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_CMODEL_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_CMODEL_HPP_

#include <cstdint>
#include "source_sdk/mathlib/mathlib.hpp"

struct Ray_t
{
	VectorAligned m_start;
	VectorAligned m_delta;
	VectorAligned m_start_offset;
	VectorAligned m_extents;
	matrix3x4_t *m_world_axis_transform;
	bool m_is_ray;
	bool m_is_swept;

	Ray_t(Vector src, Vector dst)
	{
		m_delta = dst - src;
		m_is_swept = m_delta.x || m_delta.y || m_delta.z;
		m_extents = {0.0f, 0.0f, 0.0f, 0.0f};
		m_start_offset = {0.0f, 0.0f, 0.0f, 0.0f};
		m_is_ray = true;
		m_start = src;
		m_world_axis_transform = nullptr;
	}

	Ray_t(Vector src, Vector dst, Vector mins, Vector maxs)
	{
		m_delta = dst - src;
		m_extents = (maxs - mins) * 0.5f;
		m_start_offset = (maxs + mins) * 0.5f;
		m_start = src + m_start_offset;
		m_start_offset *= -1.0f;
		m_world_axis_transform = nullptr;

		m_is_swept = m_delta.x || m_delta.y || m_delta.z;
		m_is_ray = (m_extents.LengthSqr() < 1e-6);
	}
};

/*
struct cmodel_t
{
	Vector mins, maxs;
	Vector origin;		// for sounds or lights
	int    headnode;

	vcollide_t	vcollisionData;
};
 */


struct csurface_t
{
	const char *name;
	uint16_t props;
	uint16_t flags;
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_CMODEL_HPP_
