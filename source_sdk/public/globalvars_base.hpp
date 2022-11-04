
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_GLOBALVARS_BASE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_GLOBALVARS_BASE_HPP_

struct CGlobalVarsBase
{
	float realtime;
	int framecount;
	float absoluteframetime;
	float absoluteframestarttimestddev;
	float curtime;
	float frametime;
	int max_clients;
	int tickcount;
	float interval_per_tick;
	float interpolation;
	int sim_ticks_this_frame;
	int network_protocol;
	void *save_data;
	bool client;
	bool remote_client;
	int timestamp_networking_nase;
	int timestamp_randomize_window;
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_GLOBALVARS_BASE_HPP_
