
#ifndef CSGO_CHEAT_NET_CHAN_HPP
#define CSGO_CHEAT_NET_CHAN_HPP

constexpr int MAX_CMD_BUFFER = 4000;
constexpr int MAX_NEW_CMDS = 14;

struct CNetChan
{
	char pad[0x18];
	int out_sequence_nr;
	int in_sequence_nr;
	int out_sequence_nr_ack;
	int out_reliable_state;
	int in_reliable_state;
	int choked_packets;
};

#endif //CSGO_CHEAT_NET_CHAN_HPP
