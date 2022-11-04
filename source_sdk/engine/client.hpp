
#ifndef CSGO_CHEAT_CLIENT_HPP
#define CSGO_CHEAT_CLIENT_HPP

#include "memory/offset.hpp"
#include "source_sdk/engine/net_chan.hpp"

struct CClientState
{
	//char pad[156];
	//CNetChan *net_chan;

	char pad[0x8E3C];
	int lastoutgoingcommand;
	int chokedcommands;
};

ASSERT_OFFSET(CClientState, lastoutgoingcommand, 0x8E3C);
ASSERT_OFFSET(CClientState, chokedcommands, 0x8E40);

#endif //CSGO_CHEAT_CLIENT_HPP
