#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_BONE_SETUP_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_BONE_SETUP_HPP_

#include "source_sdk/public/tier0/memalloc.hpp"

struct CBoneBitList
{
	static constexpr uint32_t BitVec_Bit(int num)
	{
		constexpr uint32_t BITS_PER_INT = 32;

		return 1 << (num & (BITS_PER_INT-1));
	}

	static constexpr uint32_t BitVec_Int(int num)
	{
		constexpr uint32_t LOG2_BITS_PER_INT = 5;

		return num >> LOG2_BITS_PER_INT;
	}

	bool IsBoneMarked(int bone)
	{
		uint32_t *base = (uint32_t *)data;
		uint32_t *mask = base + BitVec_Int(bone);

		return *mask & BitVec_Bit(bone);
	}

	char data[0x20] = { 0 };
};

struct CBoneSetup
{
	CBoneSetup(CStudioHdr *hdr, int mask, float *pose_parameters)
	{
		//fptr::CBoneSetup_CBoneSetup(this, hdr, mask, pose_parameters);
		m_hdr = hdr;
		m_mask = mask;
		m_pose_parameter = pose_parameters;
		m_pose_debugger = nullptr;
	}

	void AccumulatePose(Vector *pos, Quaternion *q, int sequence, float cycle, float weight, float time, CIKContext *ik)
	{
		fptr::CBoneSetup_AccumulatePose(this, pos, q, sequence, cycle, weight, time, ik);
	}

	void CalcAutoplaySequences(Vector *pos, Quaternion *q, float realtime, CIKContext *ik)
	{
		fptr::CBoneSetup_CalcAutoplaySequences(this, pos, q, realtime, ik);
	}

	// "static" methods
	void InitPose(Vector *pos, Quaternion *q)
	{
		fptr::InitPose(m_hdr, pos, q, m_mask);
	}

	void CalcBoneAdj(Vector *pos, Quaternion *q, float *contollers)
	{
		fptr::CalcBoneAdj(m_hdr, pos, q, contollers, m_mask);
	}

	CStudioHdr *m_hdr;
	int m_mask;
	float *m_pose_parameter;
	void *m_pose_debugger;
};

ASSERT_SIZE(CBoneSetup, 0x20);

struct CIKContext
{
	void *operator new(size_t size)
	{
		return intf::memalloc->Alloc(size);
	}

	//todo: CIKContext has an inlined destructor. we are leaking memory.
	void operator delete(void *mem)
	{
		return intf::memalloc->Free(mem);
	}

	CIKContext()
	{
		fptr::CIKContext_CIKContext(this);
	}

	void Init(CStudioHdr *hdr, QAngle &angles, Vector &pos, float time, int frame_counter, int bone_mask)
	{
		fptr::CIKContext_Init(this, hdr, angles, pos, time, frame_counter, bone_mask);
	}

	void UpdateTargets(Vector *pos, Quaternion *q, matrix3x4a_t *bone_to_world, void *bone_computed)
	{
		fptr::CIKContext_UpdateTargets(this, pos, q, bone_to_world, bone_computed);
	}

	void SolveDependencies(Vector *pos, Quaternion *q, matrix3x4a_t *bone_to_world, void *bone_computed)
	{
		fptr::CIKContext_SolveDependencies(this, pos, q, bone_to_world, bone_computed);
	}

	void AddDependencies(mstudioseqdesc_t *seqdesc, int sequence, float cycle, float *pose_parameters, float weight)
	{
		fptr::CIKContext_AddDependencies(this, seqdesc, sequence, cycle, pose_parameters, weight);
	}

	void CopyTo(CIKContext *to, unsigned short *remapping)
	{
		fptr::CIKContext_CopyTo(this, to, remapping);
	}

	private:
	char size[0x1120];
};

ASSERT_SIZE(CIKContext, 0x1120);

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_BONE_SETUP_HPP_
