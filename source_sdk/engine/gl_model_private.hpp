#ifndef CSGO_CHEAT_SOURCE_SDK_ENGINE_GL_MODEL_PRIVATE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_ENGINE_GL_MODEL_PRIVATE_HPP_

#include "source_sdk/mathlib/vector.hpp"

struct model_t
{
	void  *handle;
	char   name[260];
	int    load;
	int    server_count;
	int    type;
	int    flags;
	Vector mins;
	Vector maxs;
};

#endif //CSGO_CHEAT_SOURCE_SDK_ENGINE_GL_MODEL_PRIVATE_HPP_
