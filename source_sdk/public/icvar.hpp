
#ifndef CSGO_CHEAT_ICVAR_HPP
#define CSGO_CHEAT_ICVAR_HPP

#include <memory>
#include "memory/vtable_util.hpp"
#include "source_sdk/public/color.hpp"

struct ConVar;

struct ICvar : mem::VTableUtil
{
	static constexpr Color RED   = {255, 0, 0};
	static constexpr Color BLUE  = {0, 255, 0};
	static constexpr Color WHITE = {255, 255, 255};
	static constexpr Color GRAY  = {100, 100, 100};

	template<typename... Args>
	void ConsoleColorPrintf(const Color &color, const char *fmt, Args... args)
	{
		return Call<void, 25>(std::cref(color), fmt, args...);
	}

	template<typename ...Args>
	void ConsoleDPrintf(const char *fmt, Args... args)
	{
		return Call<void, 27>(fmt, args...);
	}

	ConVar *FindVar(const char *name)
	{
		return Call<ConVar *, 16>(name);
	}
};

#endif //CSGO_CHEAT_ICVAR_HPP
