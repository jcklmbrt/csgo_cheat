
#ifndef CSGO_CHEAT_MEMORY_PATTERN_SCAN_HPP_
#define CSGO_CHEAT_MEMORY_PATTERN_SCAN_HPP_

#include <cstdint>

uintptr_t PatternScan_Internal(const char *module, const char *pattern, int offset);

namespace mem
{
	template<typename T> T PatternScan(const char *module, const char *pattern, int offset = 0)
	{
		return T(PatternScan_Internal(module, pattern, offset));
	}
};

#endif //CSGO_CHEAT_MEMORY_PATTERN_SCAN_HPP_
