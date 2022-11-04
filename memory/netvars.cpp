#include <cstring>

#include "util/fmt.hpp"

#include "memory/netvars.hpp"
#include "memory/interfaces.hpp"

#include "source_sdk/public/dt_recv.hpp"
#include "source_sdk/public/client_class.hpp"
#include "source_sdk/public/cdll_int.hpp"

ptrdiff_t TraverseTable(RecvTable *table, const char *prop_name)
{
	for(int i = 0; i < table->prop_count; i++)
	{
		RecvProp &prop = table->props[i];

		if(!strcmp(prop_name, prop.var_name))
			return prop.offset;

		if(prop.recv_type == 6 && prop.datatable)
		{
			ptrdiff_t res = TraverseTable(prop.datatable, prop_name);

			if(res != 0)
				return prop.offset + res;
		}
	}
	return 0;
}

ptrdiff_t mem::NetVar(const char *table_name, const char *prop_name)
{
	ClientClass *client_class = intf::client->GetAllClasses();

	while(client_class != nullptr)
	{
		if(!strcmp(table_name, client_class->network_name))
		{
			ptrdiff_t offset = TraverseTable(client_class->recv_table, prop_name);
			fmt::PrintLn("[%s::%s]: %X\n", table_name, prop_name, offset);
			return offset;
		}
		client_class = client_class->next;
	}

	fmt::PrintLn("failed to find netvar: %s::%s\n", table_name, prop_name);

	return 0;
}