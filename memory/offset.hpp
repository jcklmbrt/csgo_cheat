
#ifndef CSGO_CHEAT_MEMORY_OFFSET_HPP_
#define CSGO_CHEAT_MEMORY_OFFSET_HPP_

#include <cstddef>
#include <cstdint>

namespace mem
{
	template<typename T>
	T Offset(void *base, ptrdiff_t diff)
	{
		return T((uint8_t *)base + diff);
	}

	#define OFFSET(type, name, _diff) \
	type &name() {                    \
	static auto diff = _diff;         \
        return *Offset<type *>(diff);     \
	}
};

#define ASSERT_OFFSET(type, member, offset) static_assert(offsetof(type, member) == (offset));
#define ASSERT_SIZE(type, size) static_assert(sizeof(type) == (size));

#endif //CSGO_CHEAT_MEMORY_OFFSET_HPP_
