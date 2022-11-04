
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_GAMETRACE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_GAMETRACE_HPP_

#include <cstdint>
#include "source_sdk/public/cmodel.hpp"

struct C_BaseEntity;
typedef struct CGameTrace trace_t;

struct CGameTrace
{
	Vector start;
	Vector end;
	cplane_t plane;
	float fraction;
	int contents;
	uint16_t flags;
	bool allsolid;
	bool startsolid;
	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	C_BaseEntity *entity;
	int hitbox;

	bool DidHit()
	{
		return fraction < 1.0f || allsolid || startsolid;
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_GAMETRACE_HPP_
