
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEPLAYER_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEPLAYER_HPP_

#include "source_sdk/game/client/c_basecombatcharacter.hpp"

struct C_BasePlayer : C_BaseCombatCharacter
{
	int GetHealth()
	{
		return Call<int, 167>(); // return m_iHealth;
	}

	void Think()
	{
		return Call<void, 191>();
	}

	bool IsAlive()
	{
		return Call<bool, 208>();
	}

	void StudioFrameAdvance()
	{
		return Call<void, 282>();
	}

	Vector GetEyePosition()
	{
		return Call<Vector, 348>();
	}

	void PreThink()
	{
		return Call<void, 381>();
	}

	void SelectItem(const char *str)
	{
		return Call<void, 393>(str);
	}

	void UpdateCollisionBounds()
	{
		return Call<void, 403>();
	}

	Vector GetAimPunch()
	{
		return Call<Vector, 409>();
	}

	void SetLocalViewAngles(QAngle angles)
	{
		return Call<void, 436>(&angles);
	}

	void PostThinkVPhysics()
	{
		fptr::C_BasePlayer_PostThinkVPhysics(this);
	}

	void SimulatePlayerSimulatedEntities()
	{
		fptr::C_BasePlayer_SimulatePlayerSimulatedEntities(this);
	}

	OFFSET(Vector, VecOrigin,      mem::NetVar("CBasePlayer", "m_vecOrigin"))
	OFFSET(Vector, AimPunchAngle,  mem::NetVar("CBasePlayer", "m_aimPunchAngle"))
	OFFSET(float,  SimulationTime, mem::NetVar("CBasePlayer", "m_flSimulationTime"))
	OFFSET(int,    NextThinkTick,  mem::NetVar("CBasePlayer", "m_nNextThinkTick"))
	OFFSET(float,  FallVelocity,   mem::NetVar("CBasePlayer", "m_flFallVelocity"))

};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEPLAYER_HPP_
