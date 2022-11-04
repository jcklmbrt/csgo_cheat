#include <cstring>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "memory/vtable_util.hpp"
#include "util/fmt.hpp"

//static std::unordered_map<mem::VTableUtil *, void **> s_swaps;
static std::vector<std::pair<mem::VTableUtil *, void **>> s_swaps;

void mem::VTableUtil::Hook(int index, void *hook, void **original)
{
	bool swapped = false;

	for(auto &[obj, old] : s_swaps)
		if(obj == this)
			swapped = true;

	if(!swapped)
	{
		void **old_vmt = m_vmt;
		void **new_vmt = new void *[1024];

		memcpy(new_vmt, old_vmt, sizeof(void *) * 1024);

		//s_swaps[this] = old_vmt;
		s_swaps.push_back({this, old_vmt});

		fmt::PrintLn("Object: %X Old VMT: %X New VMT: %X", this, old_vmt, new_vmt);

		m_vmt = new_vmt;
	}

	if(original != nullptr)
	{
		*original = m_vmt[index];
	}

	fmt::PrintLn("Hooked VMT index %d (%X -> %X)", index, m_vmt[index], hook);

	m_vmt[index] = hook;
}

void mem::VTableUtil::UnHookAll()
{
	for(auto &[intf, old_vmt]: s_swaps)
	{
		delete[] intf->m_vmt;
		intf->m_vmt = old_vmt;
	}

	s_swaps.clear();
}