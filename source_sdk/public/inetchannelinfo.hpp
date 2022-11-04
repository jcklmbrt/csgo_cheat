
#ifndef CSGO_CHEAT_INETCHANNELINFO_HPP
#define CSGO_CHEAT_INETCHANNELINFO_HPP

#include "memory/vtable_util.hpp"

constexpr int FLOW_OUTGOING = 0;
constexpr int FLOW_INCOMING = 1;
constexpr int MAX_FLOWS = 2;

struct INetChannelInfo : mem::VTableUtil
{
	float GetLatency(int flow)
	{
		return Call<float, 9>(flow);
	}
};

#endif//CSGO_CHEAT_INETCHANNELINFO_HPP
