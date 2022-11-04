
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEENTITY_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEENTITY_HPP_

#include "memory/vtable_util.hpp"
#include "memory/netvars.hpp"
#include "memory/function_pointers.hpp"
#include "source_sdk/mathlib/mathlib.hpp"
#include "source_sdk/tier1/utlvector.hpp"

struct ICollideable;
struct IClientNetworkable;
struct IClientRenderable;
struct IInterpolatedVar;

struct VarMapEntry_t
{
	unsigned short type;
	unsigned short needs_to_interpolate;	// Set to false when this var doesn't
	// need Interpolate() called on it anymore.
	void *data;
	IInterpolatedVar *watcher;
};


struct VarMapping_t
{
	VarMapping_t()
	{
		interpolated_entries = 0;
	}

	CUtlVector<VarMapEntry_t> entries;
	int interpolated_entries;
	float last_interpolation_time;
};

enum thinkmethods_t : int
{
	THINK_FIRE_ALL_FUNCTIONS,
	THINK_FIRE_BASE_ONLY,
	THINK_FIRE_ALL_BUT_BASE,
};

struct C_BaseEntity : mem::VTableUtil
{
	//CBaseEntity
	void SetAbsAngles(QAngle ang)
	{
		fptr::C_BaseEntity_SetAbsAngles(this, ang);
	}

	void SetAbsOrigin(Vector vec)
	{
		fptr::C_BaseEntity_SetAbsOrigin(this, vec);
	}

	QAngle GetAbsAngles()
	{
		return *Call<QAngle *, 13>();
	}

	IClientRenderable *GetClientRenderable()
	{
		return Offset<IClientRenderable *>(sizeof(void *));
	}

	//IClientRenderable
	IClientNetworkable *GetClientNetworkable()
	{
		return Offset<IClientNetworkable *>(sizeof(void *) * 2);
	}

	//ICollideable
	ICollideable *GetCollideable()
	{
		return Call<ICollideable *, 4>();
	}

	bool IsPlayer()
	{
		return Call<bool, 210>();
	}

	bool IsWeapon()
	{
		return Call<bool, 218>();
	}

	bool PhysicsRunThink(thinkmethods_t think_method = THINK_FIRE_ALL_FUNCTIONS)
	{
		return fptr::C_BaseEntity_PhysicsRunThink(this, think_method);
	}

	void SetNextThink(int context, float think_time)
	{
		return fptr::C_BaseEntity_SetNextThink(this, context, think_time);
	}

	//OFFSET(VarMapping_t, VarMapping, 0x48)
	OFFSET(int, OwnerEntity, mem::NetVar("CBaseEntity", "m_hOwnerEntity"))
	//OFFSET(matrix3x4_t, CoordinateFrame, mem::NetVar("CBaseEntity", "m_CollisionGroup") - 0x30)
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEENTITY_HPP_
