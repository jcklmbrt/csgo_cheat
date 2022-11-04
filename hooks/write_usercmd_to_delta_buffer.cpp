#include <algorithm>
#include "hooks/hooks.hpp"
#include "memory/interfaces.hpp"
#include "source_sdk/game/client/input.hpp"
#include "source_sdk/game/shared/usercmd.hpp"
#include "source_sdk/engine/client.hpp"
#include "memory/function_pointers.hpp"
#include "util/fmt.hpp"

#include "features/tickbase_manipulation.hpp"

bool (*WriteUsercmdDeltaToBuffer)(IBaseClientDLL *client, int slot, bf_write *buf, int from, int to, bool isnewcommand);
bool hkWriteUsercmdDeltaToBuffer(IBaseClientDLL *client, int slot, bf_write *buf, int from, int to, bool isnewcommand)
{
	int *num_backup_commands = mem::Offset<int *>(buf, 0x38);
	int *num_new_commands = mem::Offset<int *>(buf, 0x3C);

	if(g_ticks_to_shift <= 0)
	{
		return WriteUsercmdDeltaToBuffer(client, slot, buf, from, to, isnewcommand);
	}

	if(from != -1)
	{
		return true;
	}

	CClientState *cl = fptr::GetBaseLocalClient();

	g_ticks_to_shift = std::clamp(g_ticks_to_shift, 0, 16);

	int new_commands = *num_new_commands;
	int next_cmd_nr = cl->chokedcommands + cl->lastoutgoingcommand + 1;
	int total_new_commands = g_ticks_to_shift;

	g_ticks_to_shift -= total_new_commands;

	from = -1;
	*num_new_commands = total_new_commands;
	*num_backup_commands = 0;

	//write real commands
	for(to = next_cmd_nr - new_commands + 1; to <= next_cmd_nr; to++)
	{
		if(!WriteUsercmdDeltaToBuffer(client, slot, buf, from, to, true))
		{
			return false;
		}
		from = to;
	}

	//write fake commands
	CUserCmd *last_real_cmd = intf::input->GetUserCmd(slot, from);

	CUserCmd from_cmd, to_cmd;

	if(last_real_cmd != nullptr)
	{
		from_cmd = *last_real_cmd;
	}

	to_cmd = from_cmd;

	to_cmd.command_number++;
	to_cmd.tick_count += 200;

	for(int i = new_commands; i <= total_new_commands; i++)
	{
		fptr::WriteUsercmd(buf, &to_cmd, &from_cmd);
		from_cmd = to_cmd;
		to_cmd.command_number++;
		to_cmd.tick_count++;
	}

	return true;
}