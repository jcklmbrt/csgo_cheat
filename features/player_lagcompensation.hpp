
#ifndef CSGO_CHEAT_FEATURES_PLAYER_LAGCOMPENSATION_HPP_
#define CSGO_CHEAT_FEATURES_PLAYER_LAGCOMPENSATION_HPP_

#include <deque>
#include <array>
#include "source_sdk/mathlib/mathlib.hpp"
#include "source_sdk/public/studio.hpp"

struct C_CSPlayer;
struct CUserCmd;

struct PlayerRecord
{
	PlayerRecord(C_CSPlayer *player);

	bool Valid();
	int Tick();

	static void BackTrack(CUserCmd *cmd);
	static void Store();

	matrix3x4a_t m_bones[MAX_STUDIO_BONES];

	float m_simulation_time;
	QAngle m_angles;
	Vector m_origin;
	Vector m_obb_mins;
	Vector m_obb_maxs;
};

struct BackupRecord : PlayerRecord
{
	BackupRecord(C_CSPlayer *player)
		: m_player(player), PlayerRecord(player)
	{};

	~BackupRecord();

	C_CSPlayer *m_player;
};

inline std::array<std::deque<PlayerRecord>, 65> g_records = {};

#endif //CSGO_CHEAT_FEATURES_PLAYER_LAGCOMPENSATION_HPP_
