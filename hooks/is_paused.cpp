#include "hooks/hooks.hpp"
#include "memory/pattern_scan.hpp"

bool(*IsPaused)(IVEngineClient *engine);
bool hkIsPaused(IVEngineClient *engine)
{
	/*
	in C_BaseEntity::InterpolateServerEntities()

	if(cl_extrapolate.GetBool() && !engine->IsPaused()) <- 84 c0 0f 85 b8 fd
	{
		context.EnableExtrapolation(true);
	}
	*/

	static void *interpolate_server_entities = mem::PatternScan<void *>(
		"csgo/bin/linux64/client_client.so",
		"\x84\xc0\x0f\x85\xb8\xfd"
	);

	void *ret = __builtin_return_address(0);

	//disable extrapolation
	if(ret == interpolate_server_entities)
		return true;

	return IsPaused(engine);
}