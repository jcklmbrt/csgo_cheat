
#ifndef CSGO_CHEAT_VTABLE_UTIL_HPP
#define CSGO_CHEAT_VTABLE_UTIL_HPP

#include "memory/offset.hpp"

namespace mem
{
	struct VTableUtil
	{
		template<typename T>
		T Offset(ptrdiff_t offset)
		{
			//return Offset<T>(this, offset);
			return T((uint8_t *)this + offset);
		}

		void Hook(int index, void *hook, void **original = nullptr);
		static void UnHookAll();

		template<typename Fn>
		Fn GetMethod(int index)
		{
			return Fn(m_vmt[index]);
		}

		template<typename T, int I, typename ...Args>
		T Call(Args... args)
		{
			using Fn = T(*)(void *, Args...);
			Fn fn = GetMethod<Fn>(I);
			return fn(this, args...);
		}

		void **m_vmt;
	};
}

#endif //CSGO_CHEAT_VTABLE_UTIL_HPP
