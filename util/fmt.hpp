
#ifndef CSGO_CHEAT_UTIL_FMT_HPP_
#define CSGO_CHEAT_UTIL_FMT_HPP_

#include "renderer/renderer.hpp"

namespace fmt
{
	//Print_Pattern(const char *pattern);
	void PrintLn(const char *fmt, ...);
	void DrawLog(Draw &gr);
};

#endif //CSGO_CHEAT_UTIL_FMT_HPP_
