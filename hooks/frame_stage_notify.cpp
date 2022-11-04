#include "memory/interfaces.hpp"

#include "source_sdk/public/cdll_int.hpp"
#include "source_sdk/public/icliententitylist.hpp"
#include "source_sdk/public/globalvars_base.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"

#include "features/player_lagcompensation.hpp"
#include "features/player_util.hpp"

void(*FrameStageNotify)(IBaseClientDLL *client, ClientFrameStage_t stage);
void hkFrameStageNotify(IBaseClientDLL *client, ClientFrameStage_t stage)
{
	if(!intf::engine->IsConnected() || !intf::engine->IsInGame())
	{
		FrameStageNotify(client, stage);
		return;
	}

	int max_ent = intf::entitylist->GetHighestEntityIndex();

	for(int i = 1; i <= max_ent; i++)
	{
		C_BaseEntity *entity = intf::entitylist->GetClientEntity<C_BaseEntity *>(i);

		if(entity != nullptr)
		{
			if(entity->IsPlayer() || entity->IsWeapon())
			{
				//m_bCanUseFastPath. see C_BaseAnimating::GetClientModelRenderable
				*entity->Offset<bool *>(0x2CEC) = false;
			}
		}
	}

	switch(stage)
	{
	case FRAME_RENDER_START:
		BackupRecord::Store();
		break;

	case FRAME_NET_UPDATE_END:

		//disable interpolation
		for(int i = 1; i < intf::globals->max_clients; i++)
		{
			C_CSPlayer *player = intf::entitylist->GetClientEntity<C_CSPlayer *>(i);

			if(ValidPlayer(player))
			{
				//See Reset_Interp xrefs 8b 46 10 55 48 89 e5 41 56 49 89 f6 41 55 41 54
				VarMapping_t *mapping = player->Offset<VarMapping_t *>(0x48);

				for(int j = 0; j < mapping->entries.size; j++)
				{
					mapping->entries[j].needs_to_interpolate = false;
				}
			}
		}
		break;

	default:
		break;
	}

	FrameStageNotify(client, stage);
}