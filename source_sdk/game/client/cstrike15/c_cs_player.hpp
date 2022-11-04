
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_CSTRIKE15_C_CS_PLAYER_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_CSTRIKE15_C_CS_PLAYER_HPP_

#include "memory/function_pointers.hpp"
#include "source_sdk/game/client/c_baseplayer.hpp"
#include "source_sdk/public/datamap.hpp"

struct C_CSPlayer : C_BasePlayer
{
	static C_CSPlayer *GetLocalPlayer()
	{
		C_BasePlayer *baseplayer = fptr::C_BasePlayer_GetLocalPlayer(-1);
		return (C_CSPlayer *)baseplayer;
	}

	void ClampBonesInBBox(matrix3x4a_t *bone_to_world, int mask)
	{
		fptr::C_CSPlayer_ClampBonesInBBox(this, bone_to_world, mask);
	}

	bool IsOtherEnemy(C_CSPlayer *other)
	{
		return fptr::C_CSPlayer_IsOtherEnemy(this, other);
	}

	OFFSET(int,    Flags,      mem::NetVar("CCSPlayer", "m_fFlags"))
	OFFSET(bool,   IsScoped,   mem::NetVar("CCSPlayer", "m_bIsScoped"))
	OFFSET(QAngle, EyeAngles,  mem::NetVar("CCSPlayer", "m_angEyeAngles"))
	OFFSET(int,    ShotsFired, mem::NetVar("CCSPlayer", "m_iShotsFired"))
	OFFSET(int,    TickBase,   mem::NetVar("CCSPlayer", "m_nTickBase"))

	datamap_t *GetPredDescMap()
	{
		return Call<datamap_t *, 21>();
	}

	OFFSET(int,  GroundEntity,   GetPredDescMap()->Find("m_hGroundEntity"))
	OFFSET(int,  MoveType,       GetPredDescMap()->Find("m_MoveType"))
	OFFSET(int,  Buttons,        GetPredDescMap()->Find("m_nButtons"))
	OFFSET(int,  ButtonLast,     GetPredDescMap()->Find("m_afButtonLast"))
	OFFSET(int,  ButtonPressed,  GetPredDescMap()->Find("m_afButtonPressed"))
	OFFSET(int,  ButtonReleased, GetPredDescMap()->Find("m_afButtonReleased"))
	OFFSET(char, Impulse,        GetPredDescMap()->Find("m_nImpulse"))
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_CSTRIKE15_C_CS_PLAYER_HPP_
