#include <thread>
#include <dlfcn.h>
#include "memory/interfaces.hpp"
#include "memory/vtable_util.hpp"
#include "memory/function_pointers.hpp"
#include "hooks/hooks.hpp"
#include "renderer/renderer.hpp"

void MainThread()
{
	void *serverbrowser = nullptr;
	while(serverbrowser == nullptr)
	{
		serverbrowser = dlopen("./bin/linux64/serverbrowser_client.so", RTLD_NOLOAD | RTLD_NOW);
		usleep(500*1000);
	}

	dlclose(serverbrowser);

	intf::Init();
	fptr::Init();
	hook::Init();
}

__attribute__((constructor))
void EntryPoint()
{
	std::thread(MainThread).detach();
}

__attribute__((destructor))
void ExitPoint()
{
	Draw::Free();
	mem::VTableUtil::UnHookAll();
}
