
#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_STUDIO_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_STUDIO_HPP_

#include <cstdint>
#include "memory/function_pointers.hpp"
#include "source_sdk/mathlib/vector.hpp"

constexpr int MAX_STUDIO_BONES = 256;

constexpr int BONE_USED_BY_ANYTHING = 0x0007FF00;
constexpr int BONE_USED_BY_HITBOX = 0x00000100;
constexpr int BONE_USED_BY_BONE_MERGE = 0x00040000;

struct mstudiobone_t
{
	int sznameindex;
	int parent;
	char pad0[152];
	/*
	int	bonecontroller[6];

	Vector  pos;
	Quaternion quat;
	RadianEuler rot;
	// compression scale
	Vector posscale;
	Vector rotscale;

	CMat3x4	   poseToBone;
	Quaternion qAlignment;
	*/
	int flags;
	char pad1[52];
};

struct mstudiobbox_t
{
	int bone;
	int group;
	Vector bbmin;
	Vector bbmax;
	int name_index;
	Vector offset_orientation;
	float capsule_radius;
	int pad[4];
};

struct mstudioseqdesc_t
{
	uint8_t pad0[104];
	float fadeintime;
	float fadeouttime;
	uint8_t pad1[84];
	int num_anim_tags;
};

struct studiohdr_t
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	Vector eyeposition;
	Vector illumposition;
	Vector hullMin;
	Vector hullMax;
	Vector bbMin;
	Vector bbMax;
	int flags;
	int numbones;
	int boneindex;
	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;
	int numlocalanim;			// animations/poses
	int localanimindex;		// animation descriptions
	int numlocalseq;				// sequences
	int localseqindex;


	mstudiobbox_t *GetHitbox(int hitbox)
	{
		struct mstudiohitboxset_t
		{
			int name_index;
			int hitboxs;
			int hitbox_index;
		};

		mstudiohitboxset_t *set = (mstudiohitboxset_t *)((int8_t *)this + this->hitboxsetindex);
		mstudiobbox_t *res = (mstudiobbox_t *)((int8_t *)set + set->hitbox_index);

		return res + hitbox;
	}

	mstudioseqdesc_t *LocalSeqdesc(int i)
	{
		if (i < 0 || i >= numlocalseq)
			i = 0;

		return (mstudioseqdesc_t *)(((int8_t *)this) + localseqindex) + i;
	};

	mstudiobone_t *GetBones()
	{
		return (mstudiobone_t *)((int8_t *)this + this->boneindex);
	}

	mstudiobone_t *GetBone(int index)
	{
		return GetBones() + index;
	}
};

struct virtualmodel_t;

struct CStudioHdr
{
	studiohdr_t *hdr;
	virtualmodel_t *vmodel;

	int GetNumSeq()
	{
		if(vmodel == nullptr)
		{
			return hdr->numlocalseq;
		}

		return fptr::CStudioHdr_GetNumSeq(this);
	}

	mstudioseqdesc_t *GetSeqDesc(int sequence)
	{
		if(vmodel == nullptr)
		{
			return hdr->LocalSeqdesc(sequence);
		}

		return fptr::CStudioHdr_GetSeqDesc(this, sequence);
	}
};

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_STUDIO_HPP_
