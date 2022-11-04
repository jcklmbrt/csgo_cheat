
#ifndef CSGO_CHEAT_SOURCE_SDK_ENGINE_IENGINETRACE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_ENGINE_IENGINETRACE_HPP_

#include <memory>
#include "memory/vtable_util.hpp"
#include "source_sdk/mathlib/vector.hpp"

struct Ray_t;
struct CGameTrace;
struct IHandleEntity;
struct C_BaseEntity;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,                                // NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,                        // NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,        // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct ITraceFilter
{
	virtual bool ShouldHitEntity(IHandleEntity *entity, int mask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

struct OcclusionTestResults_t
{
	VectorAligned end_min, end_max; // the bounding box enclosing the end of the occlusion test, to be used to extend the bounding box of an object shadow
};

//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
struct CTraceFilter : ITraceFilter
{
	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

struct CTraceFilterEntitiesOnly : ITraceFilter
{
	virtual TraceType_t GetTraceType() const
	{
		return TRACE_ENTITIES_ONLY;
	}
};

//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
struct CTraceFilterWorldOnly : public ITraceFilter
{
	bool ShouldHitEntity(IHandleEntity *server_entity, int mask)
	{
		return false;
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_WORLD_ONLY;
	}
};

struct CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
	bool ShouldHitEntity(IHandleEntity *server_entity, int mask)
	{
		return false;
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
};

struct CTraceFilterHitAll : public CTraceFilter
{
	virtual bool ShouldHitEntity(IHandleEntity *server_entity, int mask)
	{
		return true;
	}
};

struct IEngineTrace : mem::VTableUtil
{
	int PointContents(Vector &pos, int mask)
	{
		return Call<int, 0>(std::cref(pos), mask, nullptr);
	}

	void ClipRayToEntity(Ray_t *ray, int mask, C_BaseEntity *entity, CGameTrace *tr)
	{
		return Call<void, 3>(ray, mask, entity, tr);
	}

	void TraceRay(Ray_t *ray, int mask, ITraceFilter *filter, CGameTrace *trace)
	{
		return Call<void, 5>(ray, mask, filter, trace);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_ENGINE_IENGINETRACE_HPP_
