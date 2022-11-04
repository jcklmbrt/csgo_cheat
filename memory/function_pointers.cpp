
#include "memory/function_pointers.hpp"
#include "memory/pattern_scan.hpp"

void fptr::Init()
{
	CShaderDeviceDx8_Dx9Device = mem::PatternScan<decltype(CShaderDeviceDx8_Dx9Device)>(
		"shaderapivk_client.so",
		"\x55\x48\x8d\x05????\x48\x89\xe5\x5d\xc3???\x55\x0f\xb6\x16"
	);

	C_BasePlayer_GetLocalPlayer = mem::PatternScan<decltype(C_BasePlayer_GetLocalPlayer)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x83\xFF\xFF\x48\x8B"
	);

	GetClientModeNormal = mem::PatternScan<decltype(GetClientModeNormal)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x8d\x05????\x48\x89\xe5\x5d\xc3???\x55\x48\x8d\x05????\x48\x89\xe5\x5d\xc3???\x55\x48\x8b\x7f\x28"
	);

	GetBaseLocalClient = mem::PatternScan<decltype(GetBaseLocalClient)>(
		"engine_client.so",
		"\x48\x8b\x05????\x55\x48\x89\xe5\x5d\x48\x83\xc0\x08\xc3"
	);

	C_BaseEntity_SetAbsAngles = mem::PatternScan<decltype(C_BaseEntity_SetAbsAngles)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xf4\x53\x48\x89\xfb\x48\x83\xec?\xe8????\xf3\x41\x0f"
	);

	C_BaseEntity_SetAbsOrigin = mem::PatternScan<decltype(C_BaseEntity_SetAbsOrigin)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x55\x41\x54\x49\x89\xf4\x53\x48\x89\xfb\x48\x83\xec\x08\xe8????\xf3\x41\x0f\x10\x04\x24"
	);

	C_BaseAnimating_InvalidateBoneCache = mem::PatternScan<decltype(C_BaseAnimating_InvalidateBoneCache)>(
		"csgo/bin/linux64/client_client.so",
		"\x80\x3d?????\x55\x48\x89\xe5\x74\x1c"
	);

	C_BasePlayer_PostThinkVPhysics = mem::PatternScan<decltype(C_BasePlayer_PostThinkVPhysics)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x56\x41\x55\x41\x54\x53\x48\x89\xfb\x48\x81\xec\xb0\x00\x00\x00\x48\x83"
	);

	C_BasePlayer_SimulatePlayerSimulatedEntities = mem::PatternScan<decltype(C_BasePlayer_SimulatePlayerSimulatedEntities)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x89\xfb\x48\x83\xec\x18\x44\x8b\xa7????\x41"
	);

	C_BaseEntity_PhysicsRunThink = mem::PatternScan<decltype(C_BaseEntity_PhysicsRunThink)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x55\x41\x54\x49\x89\xfc\x53\x89\xf3\x48\x83\xec\x08\x83"
	);

	C_BaseEntity_SetNextThink = mem::PatternScan<decltype(C_BaseEntity_SetNextThink)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x55\x45\x31\xed\x41\x54\x41\xbc\xff\xff\xff\xff\x53\x48\x89\xfb\x48\x83\xec\x08"
	);

	CPrediction_StartCommand = mem::PatternScan<decltype(CPrediction_StartCommand)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xd4\x53\x48\x89\xf3\x48\x83\xec\x08\x4c"
	);

	CPrediction_FinishCommand = mem::PatternScan<decltype(CPrediction_FinishCommand)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x56\x41\x55\x49\x89\xf5\x41\x54\x53\x48\x8b\x1d????\x44"
	);

	WriteUsercmd = mem::PatternScan<decltype(WriteUsercmd)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x8d\x05????\x48\x89\xe5\x41\x55\x49\x89\xfd\x41\x54\x49\x89\xf4\x53\x48\x89\xd3"
	);

	CIKContext_CIKContext = mem::PatternScan<decltype(CIKContext_CIKContext)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x53\x48\x89\xfb\x48\x83\xec\x08\x40\xf6\xc7\x07"
	);

	CIKContext_Init = mem::PatternScan<decltype(CIKContext_Init)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x49\x89\xf7\x41\x56\x49\x89\xfe\x41\x55\x45\x89\xc5"
	);

	CIKContext_UpdateTargets = mem::PatternScan<decltype(CIKContext_UpdateTargets)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x89\xfb\x48\x81\xec????\x48\x89\xb5????\x44\x8b\xaf"
	);

	CIKContext_SolveDependencies = mem::PatternScan<decltype(CIKContext_SolveDependencies)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x49\x89\xff\x41\x56\x41\x55\x41\x54\x53\x48\x81\xec????\x48\x89\xb5????\x48\x8b\xbf"
	);

	CIKContext_AddDependencies = mem::PatternScan<decltype(CIKContext_AddDependencies)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x49\x89\xfe\x41\x55\x41\x54\x53\x48\x81\xec????\xf3\x0f\x11"
	);

	CIKContext_CopyTo = mem::PatternScan<decltype(CIKContext_CopyTo)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x89\xf3\x48\x83\xec\x38\x48\x85\xf6\x75\x17"
	);

	InitPose = mem::PatternScan<decltype(InitPose)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xd0\x48\x89\xe5\x41\x55\x49\x89\xf5\x41\x54\x53\x48\x83\xec\x08\x4c\x8b\x07"
	);

	CalcBoneAdj = mem::PatternScan<decltype(CalcBoneAdj)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x45\x31\xf6\x41\x55\x49\x89\xfd\x41\x54\x53\x31\xdb"
	);

	CBoneSetup_AccumulatePose = mem::PatternScan<decltype(CBoneSetup_AccumulatePose)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x89\xcf\x41\x56\x49\x89\xd6\x41\x55\x4d\x89\xc5\x41\x54\x53\x48\x89\xfb"
	);

	CBoneSetup_CalcAutoplaySequences = mem::PatternScan<decltype(CBoneSetup_CalcAutoplaySequences)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x49\x89\xcd\x41\x54\x53\x48\x89\xfb\x48\x83\xec\x38"
	);

	CBoneMergeCache_CBoneMergeCache = mem::PatternScan<decltype(CBoneMergeCache_CBoneMergeCache)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x31\xf6\x48\x89\xe5\x41\x55\x41\x54\x53\x48\x89\xfb\x48\x83\xec\x08\x48\xc7\x87"
	);

	CBoneMergeCache_Init = mem::PatternScan<decltype(CBoneMergeCache_Init)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x53\x48\x89\xfb\x48\x8d\xbf????\x48\x83\xec\x08\x48\x89\xb7\x68\xff\xff\xff"
	);

	CBoneMergeCache_MergeMatchingPoseParams = mem::PatternScan<decltype(CBoneMergeCache_MergeMatchingPoseParams)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x55\x41\x54\x49\x89\xfc\x53\x48\x83\xec\x18\xe8????\x49\x83\x7c\x24"
	);

	CBoneMergeCache_CopyFromFollow = mem::PatternScan<decltype(CBoneMergeCache_CopyFromFollow)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x4d\x89\xc7\x41\x56\x41\x89\xce\x41\x55\x49\x89\xd5\x41\x54\x49\x89\xf4\x53\x48\x89\xfb\x48\x83\xec\x18\x4c\x89\x4d\xc8\xe8\xd7\xf7"
	);

	CBoneMergeCache_CopyToFollow = mem::PatternScan<decltype(CBoneMergeCache_CopyToFollow)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x4d\x89\xc7\x41\x56\x41\x89\xce\x41\x55\x49\x89\xd5\x41\x54\x49\x89\xf4\x53\x48\x89\xfb\x48\x83\xec\x18\x4c\x89\x4d\xc8\xe8\xf7\xf6"
	);

	CStudioHdr_GetNumSeq = mem::PatternScan<decltype(CStudioHdr_GetNumSeq)>(
		"csgo/bin/linux64/client_client.so",
		"\x48\x8b\x47\x08\x55\x48\x89\xe5\x5d\x8b\x40\x18\xc3"
	);

	CStudioHdr_GetSeqDesc = mem::PatternScan<decltype(CStudioHdr_GetSeqDesc)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x85\xf6\x48\x89\xe5\x41\x54\x53\x48\x89\xfb\x48\x8b\x47\x08\x78\x0c"
	);

	C_CSPlayer_ClampBonesInBBox = mem::PatternScan<decltype(C_CSPlayer_ClampBonesInBBox)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x41\x57\x49\x89\xf7\x41\x56\x41\x55\x41\x89\xd5\x41\x54\x49\x89\xfc\x53\x48\x81\xec"
	);

	C_CSPlayer_IsOtherEnemy = mem::PatternScan<decltype(C_CSPlayer_IsOtherEnemy)>(
		"csgo/bin/linux64/client_client.so",
		"\x31\xc0\x48\x85\xf6\x74\x34\x55\x48\x89\xe5\x41\x54\x49\x89\xfc\x53"
	);

	C_BaseWeaponWorldModel_HoldsPlayerAnimations = mem::PatternScan<decltype(C_BaseWeaponWorldModel_HoldsPlayerAnimations)>(
		"csgo/bin/linux64/client_client.so",
		"\x55\x48\x89\xe5\x53\x48\x89\xfb\x48\x83\xec\x08\x8b\x87????\x85\xc0\x74\x12\x83\xf8\x01\x0f\x94\xc0"
	);
}