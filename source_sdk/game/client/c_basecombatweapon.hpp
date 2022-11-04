
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASECOMBATWEAPON_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASECOMBATWEAPON_HPP_

#include "memory/netvars.hpp"
#include "source_sdk/game/client/c_baseanimating.hpp"

struct CCSWeaponInfo;

struct C_BaseWeaponWorldModel : C_BaseAnimating
{
	bool HoldsPlayerAnimations()
	{
		return fptr::C_BaseWeaponWorldModel_HoldsPlayerAnimations(this);
	}
};

struct C_BaseCombatWeapon : C_BaseAnimating
{
	const char *GetName()
	{
		return Call<const char *, 219>();
	}

	CCSWeaponInfo *GetCSWpnData()
	{
		return Call<CCSWeaponInfo *, 529>();
	}

	float GetInaccuracy()
	{
		return Call<float, 483>();
	}

	float GetSpread()
	{
		return Call<float, 453>();
	}

	OFFSET(int, Clip1, mem::NetVar("CBaseCombatWeapon", "m_iClip1"))
	OFFSET(int, WeaponWorldModel, mem::NetVar("CBaseCombatWeapon", "m_hWeaponWorldModel"))
	OFFSET(float, NextPrimaryAttack, mem::NetVar("CBaseCombatWeapon", "m_flNextPrimaryAttack"))
	//CWeaponCSBase
	OFFSET(float, PostponeFireReadyTime, mem::NetVar("CWeaponCSBase", "m_flPostponeFireReadyTime"))

	//CBaseAttributableItem
	OFFSET(int, ItemDefinitionIndex, mem::NetVar("CBaseAttributableItem", "m_iItemDefinitionIndex"))
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASECOMBATWEAPON_HPP_
