
#ifndef CSGO_CHEAT_INTERFACES_HPP
#define CSGO_CHEAT_INTERFACES_HPP

struct ICvar;
struct IBaseClientDLL;
struct IVEngineClient;
struct IMDLCache;
struct IClientEntityList;
struct IVModelInfoClient;
struct IPanel;
struct IMaterialSystem;
struct IVModelRender;
struct IGameEventManager2;
struct IEngineTrace;
struct IPhysicsSurfaceProps;
struct IPrediction;
struct IGameMovement;
struct CGlobalVarsBase;
struct CInput;
struct IMoveHelper;
struct IMemAlloc;

namespace intf
{
	void Init();

	inline ICvar *cvar = nullptr;
	inline IBaseClientDLL *client = nullptr;
	inline IVEngineClient *engine = nullptr;
	inline IMDLCache *mdlcache = nullptr;
	inline IClientEntityList *entitylist = nullptr;
	inline IVModelInfoClient *modelinfo = nullptr;
	inline IPanel *panel = nullptr;
	inline IMaterialSystem *materialsystem = nullptr;
	inline IVModelRender *modelrender = nullptr;
	inline IGameEventManager2 *eventmanager = nullptr;
	inline IEngineTrace *trace = nullptr;
	inline IPhysicsSurfaceProps *physprops = nullptr;
	inline IPrediction *prediction = nullptr;
	inline IGameMovement *gamemovement = nullptr;
	inline CGlobalVarsBase *globals = nullptr;
	inline CInput *input = nullptr;
	inline IMoveHelper *movehelper = nullptr;
	inline IMemAlloc *memalloc = nullptr;
}

#endif //CSGO_CHEAT_INTERFACES_HPP
