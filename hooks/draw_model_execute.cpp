
#include <cstring>

#include "memory/interfaces.hpp"

#include "features/player_lagcompensation.hpp"

#include "source_sdk/public/icliententitylist.hpp"
#include "source_sdk/engine/gl_model_private.hpp"
#include "source_sdk/public/engine/ivmodelrender.hpp"
#include "source_sdk/public/materialsystem/imaterialsystem.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"

#include "features/player_util.hpp"

void RemoveScopeBlur()
{
	static IMaterial *x_blur = intf::materialsystem->FindMaterial("dev/blurfilterx_nohdr");
	static IMaterial *y_blur = intf::materialsystem->FindMaterial("dev/blurfiltery_nohdr");
	static IMaterial *scope = intf::materialsystem->FindMaterial("dev/scope_bluroverlay");

	x_blur->SetVarFlag(MATERIAL_VAR_NO_DRAW, true);
	y_blur->SetVarFlag(MATERIAL_VAR_NO_DRAW, true);
	scope->SetVarFlag(MATERIAL_VAR_NO_DRAW, true);

}

void(*DrawModelExecute)(IVModelRender *modelrender, void *ctx, void *state, ModelRenderInfo_t *info, matrix3x4_t *bone_to_world);
void hkDrawModelExecute(IVModelRender *modelrender, void *ctx, void *state, ModelRenderInfo_t *info, matrix3x4_t *bone_to_world)
{
	RemoveScopeBlur();

	auto Original = [modelrender, ctx, state, info](matrix3x4_t *bone_to_world, IMaterial *mat = nullptr)
	{
		if(mat != nullptr)
		{
			intf::modelrender->ForcedMaterialOverride(mat);
			DrawModelExecute(modelrender, ctx, state, info, bone_to_world);
			intf::modelrender->ForcedMaterialOverride(nullptr);
		}
		else
		{
			DrawModelExecute(modelrender, ctx, state, info, bone_to_world);
		}
	};

	C_CSPlayer *player = intf::entitylist->GetClientEntity<C_CSPlayer *>(info->entity_index);
	static IMaterial *mat = intf::materialsystem->FindMaterial("debug/debugambientcube");

	mat->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	const char *name = info->model->name;

	//foot shadows
	if(strstr(name, "shadow"))
		return;

	//sleeves
	else if(strstr(name, "sleeve"))
	{
		if(C_CSPlayer::GetLocalPlayer()->IsScoped())
			return;

		mat->SetColor(0.2f, 0.4f, 0.8f);
		Original(bone_to_world, mat);
	}

	//arms
	else if(strstr(name, "arms"))
	{
		if(C_CSPlayer::GetLocalPlayer()->IsScoped())
			return;

		mat->SetColor(0.0f, 1.0f, 0.6f, 1.0f);
		Original(bone_to_world, mat);
	}

	//viewmodel weapon
	else if(strstr(name, "weapons/v_"))
	{
		if(C_CSPlayer::GetLocalPlayer()->IsScoped())
			return;

		mat->SetColor(0.6f, 0.3f, 1.0f, 1.0f);
		Original(bone_to_world, mat);
	}

	//dropped weapon
	else if(strstr(name, "_dropped.mdl"))
	{
		mat->SetColor(0.6f, 0.3f, 1.0f, 1.0f);
		Original(bone_to_world, mat);
	}

	//other weapons
	else if(strstr(name, "weapons"))
	{
		mat->SetColor(0.6f, 0.3f, 1.0f, 1.0f);
		Original(bone_to_world, mat);
	}

	else if(ValidPlayer(player))
	{
		/*
		for(auto &record : g_records[info->entity_index])
		{
			mat->SetColor(0.1f, 0.3f, 1.0f, 0.2f);
			if(record.Valid())
			{
				Original(record.m_bones, mat);
			}
		}
		*/
		if(!g_records[info->entity_index].empty())
		{
			mat->SetColor(0.1f, 0.3f, 1.0f, 0.2f);
			Original(g_records[info->entity_index].back().m_bones, mat);
		}

		if(C_CSPlayer::GetLocalPlayer()->IsOtherEnemy(player))
		{
			mat->SetColor(0.3f, 1.0f, 0.1f, 1.0f);
			Original(bone_to_world, mat);
		}

		else
		{
			mat->SetColor(1.0f, 0.3f, 0.1f, 1.0f);
			Original(bone_to_world, mat);
		}

	}

	else Original(bone_to_world);
}