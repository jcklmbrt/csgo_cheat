
#ifndef CSGO_CHEAT_MEMORY_FUNCTION_POINTERS_HPP_
#define CSGO_CHEAT_MEMORY_FUNCTION_POINTERS_HPP_

#include "source_sdk/shaderapivk/d3d9_types.hpp"
#include "source_sdk/mathlib/mathlib.hpp"

struct C_BasePlayer;
struct C_BaseEntity;
struct C_BaseAnimating;
struct C_CSPlayer;
struct CClientState;
struct IPrediction;
struct IClientMode;
struct Vector;
struct CUserCmd;
struct CStudioHdr;
struct CIKContext;
struct CBoneSetup;
struct CBoneMergeCache;
struct C_BaseWeaponWorldModel;
struct bf_write;
struct mstudioseqdesc_t;

enum thinkmethods_t : int;

namespace fptr
{
	void Init();

	inline dxvk::D3D9Device**(*CShaderDeviceDx8_Dx9Device)();
	inline C_BasePlayer*(*C_BasePlayer_GetLocalPlayer)(int);
	inline IClientMode*(*GetClientModeNormal)();
	inline CClientState*(*GetBaseLocalClient)();
	inline void(*C_BaseEntity_SetAbsOrigin)(C_BaseEntity *, Vector &);
	inline void(*C_BaseEntity_SetAbsAngles)(C_BaseEntity *, QAngle &);
	inline void(*C_BaseAnimating_InvalidateBoneCache)(C_BaseAnimating *);
	inline void(*C_BasePlayer_PostThinkVPhysics)(C_BasePlayer *);
	inline void(*C_BasePlayer_SimulatePlayerSimulatedEntities)(C_BasePlayer *);
	inline bool(*C_BaseEntity_PhysicsRunThink)(C_BaseEntity *, thinkmethods_t);
	inline void(*C_BaseEntity_SetNextThink)(C_BaseEntity *, int, float);
	inline void(*CPrediction_StartCommand)(IPrediction *, C_BaseEntity *, CUserCmd *);
	inline void(*CPrediction_FinishCommand)(IPrediction *, C_BaseEntity *);
	inline void(*WriteUsercmd)(bf_write *buf, CUserCmd *to, CUserCmd *from);
	inline void(*CIKContext_CIKContext)(CIKContext *);
	inline void(*CIKContext_Init)(CIKContext *, CStudioHdr *hdr, Vector &angles, Vector &pos, float time, int frame_counter, int bone_mask);
	inline void(*CIKContext_UpdateTargets)(CIKContext *, Vector *pos, Quaternion *q, matrix3x4a_t *bone_to_world, void *bone_computed);
	inline void(*CIKContext_SolveDependencies)(CIKContext *, Vector *pos, Quaternion *q, matrix3x4a_t *bone_to_world, void *bone_computed);
	inline void(*CIKContext_AddDependencies)(CIKContext *, mstudioseqdesc_t *seqdesc, int sequence, float cycle, float *pose_parameters, float weight);
	inline void(*CIKContext_CopyTo)(CIKContext *, CIKContext *to, unsigned short *remapping);
	inline void(*CBoneSetup_AccumulatePose)(CBoneSetup *, Vector *pos, Quaternion *q, int sequence, float cycle, float weight, float time, CIKContext *ik);
	inline void(*CBoneSetup_CalcAutoplaySequences)(CBoneSetup *, Vector *pos, Quaternion *q, float realtime, CIKContext *ik);
	inline void(*InitPose)(CStudioHdr *, Vector *pos, Quaternion *q, int mask);
	inline void(*CalcBoneAdj)(CStudioHdr *hdr, Vector *pos, Quaternion *q, float *controllers, int mask);
	inline void(*CBoneMergeCache_CBoneMergeCache)(CBoneMergeCache *);
	inline void(*CBoneMergeCache_Init)(CBoneMergeCache *, C_BaseAnimating *owner);
	inline void(*CBoneMergeCache_MergeMatchingPoseParams)(CBoneMergeCache *);
	inline void(*CBoneMergeCache_CopyFromFollow)(CBoneMergeCache *, Vector *follow_pos, Quaternion *follow_q, int mask, Vector *my_pos, Quaternion *my_q);
	inline void(*CBoneMergeCache_CopyToFollow)(CBoneMergeCache *, Vector *my_pos, Quaternion *my_q, int mask, Vector *follow_pos, Quaternion *follow_q);
	inline int(*CStudioHdr_GetNumSeq)(CStudioHdr *);
	inline mstudioseqdesc_t *(*CStudioHdr_GetSeqDesc)(CStudioHdr *, int sequence);
	inline void(*C_CSPlayer_ClampBonesInBBox)(C_CSPlayer *, matrix3x4a_t *bone_to_world, int mask);
	inline bool(*C_CSPlayer_IsOtherEnemy)(C_CSPlayer *, C_CSPlayer *other);
	inline bool(*C_BaseWeaponWorldModel_HoldsPlayerAnimations)(C_BaseWeaponWorldModel *);
};

#endif //CSGO_CHEAT_MEMORY_FUNCTION_POINTERS_HPP_
