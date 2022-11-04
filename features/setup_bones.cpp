#include "features/setup_bones.hpp"

#include "memory/interfaces.hpp"

#include "source_sdk/mathlib/mathlib.hpp"
#include "source_sdk/game/client/cstrike15/c_cs_player.hpp"
#include "source_sdk/public/studio.hpp"
#include "source_sdk/public/bone_setup.hpp"
#include "source_sdk/public/globalvars_base.hpp"
#include "source_sdk/public/icliententitylist.hpp"
#include "source_sdk/public/datacache/imdlcache.hpp"
#include "source_sdk/game/shared/bone_merge_cache.hpp"
#include "source_sdk/game/client/c_basecombatweapon.hpp"

void GetSkeleton(C_CSPlayer *entity, CStudioHdr *hdr, Vector *pos, Quaternion *q, int mask)
{
	CBoneSetup bone_setup = CBoneSetup(hdr, mask, entity->PoseParameter().data());

	bone_setup.InitPose(pos, q);
	bone_setup.AccumulatePose(pos, q, entity->Sequence(), entity->Cycle(), 1.0f, entity->SimulationTime(), entity->IK());

	Vector origin = entity->VecOrigin();
	QAngle angles = entity->GetAbsAngles();

	int layers[MAX_OVERLAYS] = {};

	for(int i = 0; i < entity->AnimOverlay().size; i++)
	{
		layers[i] = MAX_OVERLAYS;
	}

	for(int i = 0; i < entity->AnimOverlay().size; i++)
	{
		CAnimationLayer &layer = entity->AnimOverlay()[i];

		if((layer.weight > 0) && layer.order >= 0 && layer.order < entity->AnimOverlay().size)
		{
			layers[layer.order] = i;
		}
	}

	bool do_weapon_setup = false;

	C_BaseWeaponWorldModel *weapon_world_model = nullptr;

	if(entity->IsPlayer())
	{
		C_BaseCombatWeapon *weapon = entity->GetActiveWeapon();

		if(weapon != nullptr)
		{
			weapon_world_model = intf::entitylist->GetClientEntityFromHandle<C_BaseWeaponWorldModel *>(weapon->WeaponWorldModel());

			if(weapon_world_model != nullptr && weapon_world_model->ModelPtr() != nullptr)
			{
				if(weapon_world_model->HoldsPlayerAnimations())
				{
					if(weapon_world_model->BoneMergeCache() == nullptr)
					{
						weapon_world_model->BoneMergeCache() = new CBoneMergeCache();
						weapon_world_model->BoneMergeCache()->Init(weapon_world_model);
					}

					if(weapon_world_model->BoneMergeCache())
					{
						do_weapon_setup = true;
					}
				}
			}
		}
	}

	if(do_weapon_setup)
	{
		CStudioHdr *wpn_hdr = weapon_world_model->ModelPtr();

		weapon_world_model->BoneMergeCache()->MergeMatchingPoseParams();

		CIKContext wpn_ik;
		wpn_ik.Init(wpn_hdr, angles, origin, entity->SimulationTime(), 0, BONE_USED_BY_BONE_MERGE);

		CBoneSetup wpn_setup = CBoneSetup(wpn_hdr, BONE_USED_BY_BONE_MERGE, weapon_world_model->PoseParameter().data());

		Vector wpn_pos[MAX_STUDIO_BONES];
		Quaternion wpn_q[MAX_STUDIO_BONES];

		wpn_setup.InitPose(wpn_pos, wpn_q);

		for(int i = 0; i < entity->AnimOverlay().size; i++)
		{
			CAnimationLayer &layer = entity->AnimOverlay()[i];

			if(layer.sequence <= 1 || layer.weight <= 0.0f)
				continue;

			entity->UpdateDispatchLayer(&layer, wpn_hdr, layer.sequence);

			if(layer.dispatched_dst > 0 && layer.dispatched_dst < wpn_hdr->GetNumSeq())
			{
				weapon_world_model->BoneMergeCache()->CopyFromFollow(pos, q, BONE_USED_BY_BONE_MERGE, wpn_pos, wpn_q);

				mstudioseqdesc_t *seqdesc = hdr->GetSeqDesc(layer.sequence);

				entity->IK()->AddDependencies(seqdesc, layer.sequence, layer.cycle, entity->PoseParameter().data(), layer.weight);

				wpn_setup.AccumulatePose(wpn_pos, wpn_q, layer.dispatched_dst, layer.cycle, layer.weight, entity->SimulationTime(), &wpn_ik);

				weapon_world_model->BoneMergeCache()->CopyToFollow(wpn_pos, wpn_q, BONE_USED_BY_BONE_MERGE, pos, q);

				wpn_ik.CopyTo(entity->IK(), weapon_world_model->BoneMergeCache()->raw_index_mapping);
			}
			else
			{
				bone_setup.AccumulatePose(pos, q, layer.sequence, layer.cycle, layer.weight, entity->SimulationTime(), entity->IK());
			}
		}
	}
	else
	{
		for(int i = 0; i < entity->AnimOverlay().size; i++)
		{
			if(layers[i] >= 0 && layers[i] < entity->AnimOverlay().size)
			{
				CAnimationLayer &layer = entity->AnimOverlay()[layers[i]];
				bone_setup.AccumulatePose(pos, q, layer.sequence, layer.cycle, layer.weight, entity->SimulationTime(), entity->IK());
			}
		}
	}

	CIKContext auto_ik;
	auto_ik.Init(hdr, angles, origin, entity->SimulationTime(), 0, mask);

	bone_setup.CalcAutoplaySequences(pos, q, entity->SimulationTime(), &auto_ik);

	if(hdr->hdr->numbonecontrollers > 0)
	{
		bone_setup.CalcBoneAdj(pos, q, entity->EncodedController().data());
	}
}

void Studio_BuildMatrices(CStudioHdr *hdr, QAngle angles, Vector origin, Vector *pos, Quaternion *q, matrix3x4a_t *bone_to_world, int mask, CBoneBitList &bone_computed)
{
	int chain[MAX_STUDIO_BONES];
	int chain_length = hdr->hdr->numbones;

	for(int i = 0; i < hdr->hdr->numbones; i++)
	{
		chain[chain_length - i - 1] = i;
	}

	matrix3x4a_t bone_matrix;
	matrix3x4a_t rotation_matrix;

	AngleMatrix(angles, origin, rotation_matrix);

	for(int j = chain_length - 1; j >= 0; j--)
	{
		int i = chain[j];

		//skip bones that the IK has already setup
		if(bone_computed.IsBoneMarked(i))
		{
			continue;
		}

		mstudiobone_t *bone = hdr->hdr->GetBone(i);

		if(bone->flags & mask)
		{
			QuaternionMatrix(q[i], pos[i], bone_matrix);

			int parent = bone->parent;

			if(parent == -1)
			{
				ConcatTransforms(rotation_matrix, bone_matrix, bone_to_world[i]);
			}

			else
			{
				ConcatTransforms(bone_to_world[parent], bone_matrix, bone_to_world[i]);
			}
		}
	}
}

void SetupBones(C_CSPlayer *entity, matrix3x4a_t *bone_to_world, int mask)
{
	intf::mdlcache->BeginLock();

	Vector pos[MAX_STUDIO_BONES];
	Quaternion q[MAX_STUDIO_BONES];

	CBoneBitList bone_computed;

	CStudioHdr *hdr = entity->ModelPtr();

	if(hdr != nullptr)
	{
		Vector origin = entity->VecOrigin();
		QAngle angles = entity->GetAbsAngles();

		if(entity->IK() == nullptr)
		{
			//~CBaseAnimating() will free m_pIK without leaking memory
			entity->IK() = new CIKContext();
		}

		entity->IK()->Init(hdr, angles, origin, entity->SimulationTime(), intf::globals->tickcount, mask);

		GetSkeleton(entity, hdr, pos, q, mask);

		entity->IK()->UpdateTargets(pos, q, bone_to_world, &bone_computed);
		entity->CalculateIKLocks(entity->SimulationTime());
		entity->IK()->SolveDependencies(pos, q, bone_to_world, &bone_computed);

		Studio_BuildMatrices(hdr, angles, origin, pos, q, bone_to_world, mask, bone_computed);

		entity->ClampBonesInBBox(bone_to_world, mask);

		//memcpy(entity->CachedBoneData().memory, bone_to_world, sizeof(matrix3x4a_t) * MAX_STUDIO_BONES);
	}

	intf::mdlcache->EndLock();

}