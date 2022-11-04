
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEANIMATING_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEANIMATING_HPP_

#include "source_sdk/game/client/c_baseentity.hpp"
#include "source_sdk/mathlib/mathlib.hpp"

struct CBoneMergeCache;

struct CAnimationLayer
{
	char pad0[0x14];
	int dispatched_dst;
	int order;
	int sequence;
	char pad1[0x4];
	float weight;
	char pad2[0x8];
	float cycle;
	char size[0x14];
};

ASSERT_OFFSET(CAnimationLayer, sequence, 0x1C);
ASSERT_OFFSET(CAnimationLayer, weight, 0x24);
ASSERT_OFFSET(CAnimationLayer, cycle, 0x30);
ASSERT_SIZE(CAnimationLayer, 0x48);

constexpr int MAX_OVERLAYS = 0xF;

#include <array>

struct C_BaseAnimating : C_BaseEntity
{
	void InvalidateBoneCache()
	{
		fptr::C_BaseAnimating_InvalidateBoneCache(this);
	}

	void CalculateIKLocks(float curtime)
	{
		Call<void, 255>(curtime);
	}

	void UpdateClientsideAnimation()
	{
		Call<void, 286>();
	}

	void UpdateDispatchLayer(CAnimationLayer *layer, CStudioHdr *hdr, int sequence)
	{
		Call<void, 310>(layer, hdr, sequence);
	}

	std::array<float, 24> &PoseParameter() {
		static auto offset = mem::NetVar("CBaseAnimating", "m_flPoseParameter");
		return *Offset<std::array<float, 24> *>(offset);
	}

	std::array<float, 4> &EncodedController() {
		static auto offset = mem::NetVar("CBaseAnimating", "m_flEncodedController");
		return *Offset<std::array<float, 4> *>(offset);
	}

	OFFSET(CStudioHdr *, ModelPtr, 0x2FD8);
	OFFSET(CIKContext *, IK, 0x2C30);
	OFFSET(CBoneMergeCache *, BoneMergeCache, 0x2F70)
	OFFSET(CUtlVector<matrix3x4_t>, CachedBoneData, 0x2F78)
	OFFSET(CUtlVector<CAnimationLayer>, AnimOverlay, 0x3020)
	//OFFSET(float *, PoseParameter, mem::NetVar("CBaseAnimating", "m_flPoseParameter"))
	//OFFSET(float *, EncodedController, mem::NetVar("CBaseAnimating", "m_flEncodedController"))
	OFFSET(int, Sequence, mem::NetVar("CBaseAnimating", "m_nSequence"))
	OFFSET(float, Cycle, mem::NetVar("CBaseAnimating", "m_flCycle"))
};

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_CLIENT_C_BASEANIMATING_HPP_
