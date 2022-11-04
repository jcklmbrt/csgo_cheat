//
// Created by jack on 13/09/22.
//

#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASECOMBATCHARACTER_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASECOMBATCHARACTER_HPP_

#include "source_sdk/game/client/c_baseflex.hpp"

struct C_BaseCombatWeapon;

struct C_BaseCombatCharacter : C_BaseFlex
{
	OFFSET(float, NextAttack, mem::NetVar("CBaseCombatCharacter", "m_flNextAttack"))

	C_BaseCombatWeapon *GetActiveWeapon()
	{
		return Call<C_BaseCombatWeapon *, 331>();
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASECOMBATCHARACTER_HPP_
