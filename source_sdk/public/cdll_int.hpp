
#ifndef CSGO_CHEAT_CDLL_INT_HPP
#define CSGO_CHEAT_CDLL_INT_HPP

#include <memory>
#include "memory/vtable_util.hpp"
#include "source_sdk/mathlib/mathlib.hpp"

struct VMatrix;
struct ClientClass;
struct KeyValues;
struct ISpatialQuery;
struct INetChannelInfo;

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

constexpr size_t MAX_PLAYER_NAME_LENGTH = 128;
constexpr size_t SIGNED_GUID_LEN        = 32;

struct player_info_t
{
	uint64_t version;
	// network xuid
	uint64_t xuid;
	// scoreboard information
	char name[MAX_PLAYER_NAME_LENGTH];
	// local server user ID, unique while server is running
	int user_id;
	// global unique player identifer
	char guid[SIGNED_GUID_LEN + 1];
	// friends identification number
	uint32_t friends_id;
	// friends name
	char friends_name[MAX_PLAYER_NAME_LENGTH];
	// true, if player is a bot controlled by game.dll
	bool fakeplayer;
	// true if player is the HLTV proxy
	bool ishltv;
	uint32_t custom_files[4];
	unsigned char files_downloaded;
};

struct IVEngineClient : mem::VTableUtil
{
	void GetScreenSize(int &w, int &h)
	{
		return Call<void, 5>(std::cref(w), std::cref(h));
	}

	void GetScreenCenter(int &w, int &h)
	{
		GetScreenSize(w, h);
		w /= 2;
		h /= 2;
	}

	bool GetPlayerInfo(int index, player_info_t *info)
	{
		return Call<bool, 8>(index, info);
	}

	QAngle GetViewAngles()
	{
		QAngle res;
		Call<void, 18>(&res);
		return res;
	}

	bool IsInGame()
	{
		return Call<bool, 26>();
	}

	bool IsConnected()
	{
		return Call<bool, 27>();
	}

	VMatrix *WorldToScreenMatrix()
	{
		return Call<VMatrix *, 37>();
	}

	INetChannelInfo *GetNetChannelInfo()
	{
		return Call<INetChannelInfo *, 78>();
	}
};

struct IBaseClientDLL : mem::VTableUtil
{
	ClientClass *GetAllClasses()
	{
		return Call<ClientClass *, 8>();
	}

	bool DispatchUserMessage(int type, int flags, int size, void *data)
	{
		return Call<bool, 38>(type, flags, size, data);
	}
};

#endif//CSGO_CHEAT_CDLL_INT_HPP
