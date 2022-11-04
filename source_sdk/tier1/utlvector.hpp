
#ifndef CSGO_CHEAT_UTLVECTOR_HPP
#define CSGO_CHEAT_UTLVECTOR_HPP

template<typename T>
struct CUtlVector
{
	T *memory;
	int allocation_count;
	int grow_size;
	int size;
	T *elements;

	T &operator[](int i)
	{
		return elements[i];
	}
};

#endif//CSGO_CHEAT_UTLVECTOR_HPP
