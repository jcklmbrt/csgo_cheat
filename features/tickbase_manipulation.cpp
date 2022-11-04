#include "features/tickbase_manipulation.hpp"
#include "features/player_util.hpp"

#include "source_sdk/game/shared/usercmd.hpp"
#include "source_sdk/game/shared/in_buttons.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/game/client/c_basecombatweapon.hpp"
#include "source_sdk/game/shared/cstrike15/cs_weapon_parse.hpp"

int g_ticks_to_shift = 0;

void DoubleTap(C_CSPlayer *local, CUserCmd *cmd)
{
	C_BaseCombatWeapon *weapon = local->GetActiveWeapon();

	if(weapon != nullptr)
	{
		CCSWeaponInfo *wpn_info = weapon->GetCSWpnData();

		if(wpn_info != nullptr)
		{
			if(CanShoot(local) && cmd->buttons & IN_ATTACK && g_ticks_to_shift == 0)
			{
				g_ticks_to_shift += wpn_info->cycle_time;
			}
		}
	}
}