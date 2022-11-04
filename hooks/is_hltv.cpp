#include "hooks/hooks.hpp"
#include "memory/pattern_scan.hpp"

bool (*IsHLTV)(IVEngineClient *engine);
bool hkIsHLTV(IVEngineClient *engine)
{
	/*

	in CCSGOPlayerAnimState::SetUpVelocity

	#ifndef CLIENT_DLL
	Vector vecAbsVelocity = m_pPlayer->GetAbsVelocity();
	#else

	Vector vecAbsVelocity = m_vecVelocity;

	if (engine->IsHLTV() || engine->IsPlayingDemo()) <- 84 c0 0f 84 77 07 ? ? 4c 8b
	{
		vecAbsVelocity = m_pPlayer->GetAbsVelocity();
	}
	else
	{
		m_pPlayer->EstimateAbsVelocity(vecAbsVelocity);
	}

	*/

	static void *setup_velocity = mem::PatternScan<void *>(
		"csgo/bin/linux64/client_client.so",
		"\x84\xc0\x0f\x84\x77\x07??\x4c\x8b"
	);

	/*
	in C_CSPlayer::AccumulateLayers

	if (!engine->IsHLTV() && ...) <- f3 0f 10 45 cc 84 c0 75 09 f6
		return;

	*/

	static void *accumulate_layers = mem::PatternScan<void *>(
		"csgo/bin/linux64/client_client.so",
		"\xf3\x0f\x10\x45\xcc\x84\xc0\x75\x09\xf6"
	);


	void *ret = __builtin_return_address(0);

	if(ret == setup_velocity || ret == accumulate_layers)
		return true;

	return IsHLTV(engine);
}