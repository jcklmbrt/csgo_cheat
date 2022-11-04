
#ifndef CSGO_CHEAT_STRTOOLS_HPP
#define CSGO_CHEAT_STRTOOLS_HPP

#include <cstdint>
#include <cstring>

constexpr auto FNV(const char *str)
{
	constexpr auto PRIME = 16777619u;
	constexpr auto INIT = 2166136261u;

	uint32_t hash = INIT;

	for(; char ch = *str; str++)
	{
		hash ^= ch;
		hash *= PRIME;
	}

	return hash;
}

//const char[] = "..."; is inconsistent.
//use this instead.
template<size_t N>
struct StkString
{
	consteval StkString(const char (&str)[N])
	{
		//compiletime memcpy
		for(int i = 0; i < N; i++)
			m_data[i] = str[i];
	}

	operator const char *()
	{
		return m_data;
	}

	char m_data[N];
};

template<size_t N>
struct XorString : StkString<N>
{
	constexpr void x_or()
	{
		for(int i = 0; i < N; i++)
			m_data[i] = m_data[i] ^ m_key;
	}

	consteval XorString(const char (&str)[N])
		: StkString<N>(str)
	{
		m_key = FNV(str) & 0xFF;

		//encrypt at compiletime
		x_or();
	}

	//compiler will use Xor at compiletime if it gets inlined
	operator const char *()
	{
		//decrypt at runtime
		x_or();

		//nullify key to disable re-encryption
		m_key = 0;

		//return c string
		return m_data;
	}

	using StkString<N>::m_data;
	char m_key;
};

/*
#ifdef _DEBUG
typedef const char *STK;
typedef const char *XOR;
#else
template<size_t N> using XOR = XorString<N>;
template<size_t N> using STK = StkString<N>;
#endif
*/

#ifdef _DEBUG
	#define STK(s) (s)
	#define XOR(s) (s)
#else
	#define STK(s) (StkString(s))
	#define XOR(s) (XorString(s))
#endif

#endif//CSGO_CHEAT_STRTOOLS_HPP
