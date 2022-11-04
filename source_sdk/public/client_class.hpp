
#ifndef CSGO_CHEAT_CLIENT_CLASS_HPP
#define CSGO_CHEAT_CLIENT_CLASS_HPP

#include "source_sdk/public/dt_recv.hpp"

struct ClientClass
{
	void *create_fn;
	void *create_event_fn;
	char *network_name;
	RecvTable *recv_table;
	ClientClass *next;
	int class_id;
};

#endif //CSGO_CHEAT_CLIENT_CLASS_HPP
