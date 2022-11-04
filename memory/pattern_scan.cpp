#include <cstring>

#include <fcntl.h>
#include <link.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "memory/pattern_scan.hpp"
#include "memory/interfaces.hpp"
#include "util/fmt.hpp"

struct ModuleInfo
{
	const char *name;
	uintptr_t base;
	size_t size;

	static int On_Iterate(dl_phdr_info *info, size_t, void *data0)
	{
		ModuleInfo *data = (ModuleInfo *)data0;

		if(!strstr(info->dlpi_name, data->name))
			return 0;

		data->base = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
		data->size = info->dlpi_phdr[0].p_memsz;

		return 1;
	}

	ModuleInfo(const char *module_name)
	{
		name = module_name;
		base = 0;
		size = 0;

		dl_iterate_phdr(On_Iterate, this);
	}

};

uintptr_t PatternScan_Internal(const char *module, const char *pattern, int offset)
{
	auto info = ModuleInfo(module);

	if(info.base == 0)
	{
		fmt::PrintLn("PatternScan: Failed to find module: %s\n", module);
		return 0;
	}

	uint8_t *module_base = (uint8_t *)info.base;
	size_t module_size = info.size;
	size_t pattern_size = strlen(pattern);

	auto Match = [pattern, pattern_size](uint8_t *base)
	{
		for(int i = 0; i < pattern_size; i++)
			if(static_cast<uint8_t>(pattern[i]) != base[i] && pattern[i] != '?')
				return false;

		return true;
	};

	for(int i = 0; i < module_size - pattern_size; i++)
	{
		if(Match(&module_base[i]))
		{
			auto ptr = uintptr_t(&module_base[i]);
			fmt::PrintLn("[%s!%s]: %X\n", module, "...", ptr);
			return ptr + offset;
		}
	}

	fmt::PrintLn("PatternScan: Failed to find pattern: ");

	return 0;

}
