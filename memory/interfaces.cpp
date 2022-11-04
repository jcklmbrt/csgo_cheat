
#include "memory/pattern_scan.hpp"
#include "memory/interfaces.hpp"
#include "memory/offset.hpp"

#include "util/strtools.hpp"
#include "util/fmt.hpp"

#include "source_sdk/game/client/iclientmode.hpp"
#include "source_sdk/public/cdll_int.hpp"

#include <dlfcn.h>
#include <cstring>

using CreateInterfaceFn = void *(*)(const char *name, int *return_code);
using InstantiateInterfaceFn = void *(*)();

// Used internally to register classes.
struct InterfaceReg
{
	InstantiateInterfaceFn m_create_fn;
	const char *m_name;
	InterfaceReg *m_next; // For the global list.
};

template<typename T>
T FindInterface(const char *file, const char *name)
{
	void *lib = dlopen(file, RTLD_NOLOAD | RTLD_LAZY);

	if(lib != nullptr)
	{
		InterfaceReg *reg = *(InterfaceReg **)dlsym(lib, "s_pInterfaceRegs");

		dlclose(lib);

		for(InterfaceReg *iter = reg; iter != nullptr; iter = iter->m_next)
		{
			if(strstr(iter->m_name, name))
			{
				T res = (T)iter->m_create_fn();
				fmt::PrintLn("[%s!%s]: %X\n", file, name, res);
				return res;
			}
		}
	}

	fmt::PrintLn("Failed to find interface: %s %s\n", file, name);

	return nullptr;
}

template<typename T>
T Rel32(void *ptr)
{
	uint8_t *addr  = (uint8_t *)ptr;
	int32_t rel32 = *(int32_t *)ptr;

	return T(addr + 4 + rel32);
}

void intf::Init()
{
	const char *client_client         = "csgo/bin/linux64/client_client.so";
	const char *engine_client         = "engine_client.so";
	const char *vgui_client           = "vgui2_client.so";
	const char *datacache_client      = "datacache_client.so";
	const char *vphysics_client       = "vphysics_client.so";
	const char *materialsystem_client = "materialsystem_client.so";

	cvar           = FindInterface<ICvar                *>(materialsystem_client, "VEngineCvar007");
	materialsystem = FindInterface<IMaterialSystem      *>(materialsystem_client, "VMaterialSystem080");
	modelinfo      = FindInterface<IVModelInfoClient    *>(engine_client,         "VModelInfoClient004");
	engine         = FindInterface<IVEngineClient       *>(engine_client,         "VEngineClient014");
	modelrender    = FindInterface<IVModelRender        *>(engine_client,         "VEngineModel016");
	eventmanager   = FindInterface<IGameEventManager2   *>(engine_client,         "GAMEEVENTSMANAGER002");
	trace          = FindInterface<IEngineTrace         *>(engine_client,         "EngineTraceClient004");
	entitylist     = FindInterface<IClientEntityList    *>(client_client,         "VClientEntityList003");
	prediction     = FindInterface<IPrediction          *>(client_client,         "VClientPrediction001");
	gamemovement   = FindInterface<IGameMovement        *>(client_client,         "GameMovement001");
	client         = FindInterface<IBaseClientDLL       *>(client_client,         "VClient018");
	physprops      = FindInterface<IPhysicsSurfaceProps *>(vphysics_client,       "VPhysicsSurfaceProps001");
	panel          = FindInterface<IPanel               *>(vgui_client,           "VGUI_Panel009");
	mdlcache       = FindInterface<IMDLCache            *>(datacache_client,      "MDLCache004");

	globals = *Rel32<CGlobalVarsBase **>(mem::Offset<void *>(intf::client->m_vmt[11], 16));
	input = **Rel32<CInput ***>(mem::Offset<void *>(intf::client->m_vmt[16], 3));

	void *tier0 = dlopen("libtier0_client.so", RTLD_NOLOAD | RTLD_LAZY);
	memalloc = *(IMemAlloc **)dlsym(tier0, "g_pMemAlloc");
	dlclose(tier0);

	movehelper = **Rel32<IMoveHelper ***>(mem::PatternScan<void *>(client_client, "\x48\x8B\x05????\x44\x89\x85????\x48\x8B\x38", 3));
}
