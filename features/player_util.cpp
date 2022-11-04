#include "features/player_util.hpp"

#include "memory/interfaces.hpp"

#include "source_sdk/public/studio.hpp"
#include "source_sdk/public/iclientnetworkable.hpp"
#include "source_sdk/public/iclientrenderable.hpp"
#include "source_sdk/public/engine/ivmodelinfo.hpp"
#include "source_sdk/public/globalvars_base.hpp"
#include "source_sdk/game/client/c_basecombatweapon.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/engine/gl_model_private.hpp"
#include "source_sdk/game/shared/cstrike15/cs_weapon_parse.hpp"

Vector GetHitbox(C_CSPlayer *player, int hitbox, matrix3x4_t *bones)
{
	model_t *model = player->GetClientRenderable()->GetModel();
	studiohdr_t *hdr = intf::modelinfo->GetStudiomodel(model);
	mstudiobbox_t *box = hdr->GetHitbox(hitbox);

	Vector mins = VectorTransform(box->bbmin, bones[box->bone]);
	Vector maxs = VectorTransform(box->bbmax, bones[box->bone]);

	return (mins + maxs) * 0.5f;
}

bool ValidPlayer(C_CSPlayer *player)
{
	if(player == nullptr)
		return false;

	if(!player->IsPlayer())
		return false;

	if(!player->IsAlive())
		return false;

	if(player->GetClientNetworkable()->IsDormant())
		return false;

	if(player == C_CSPlayer::GetLocalPlayer())
		return false;

	return true;
}

bool CanShoot(C_CSPlayer *player)
{
	C_BaseCombatWeapon *weapon = player->GetActiveWeapon();

	if(weapon == nullptr)
		return false;

	CCSWeaponInfo *wpn_info = weapon->GetCSWpnData();

	if(wpn_info == nullptr)
		return false;

	if(player->NextAttack() > intf::globals->curtime)
		return false;

	if(weapon->NextPrimaryAttack() > intf::globals->curtime)
		return false;

	if(!weapon->Clip1())
		return false;

	switch(wpn_info->weapon_type)
	{
	case CSWeaponType::C4:
	case CSWeaponType::KNIFE:
	case CSWeaponType::FISTS:
	case CSWeaponType::BREACH_CHARGE:
	case CSWeaponType::BUMP_MINE:
	case CSWeaponType::TABLET:
	case CSWeaponType::MELEE:
	case CSWeaponType::GRENADE:
		return false;
	}

	if(weapon->ItemDefinitionIndex() == CSWeaponID::REVOLVER)
	{
		float ready_time = weapon->PostponeFireReadyTime();

		if(ready_time <= 0 || ready_time >= intf::globals->curtime)
			return false;
	}

	if(!wpn_info->full_auto && player->ShotsFired())
		return false;

	return true;
}