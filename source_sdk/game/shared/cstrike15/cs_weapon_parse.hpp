
#ifndef CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_CSTRIKE15_CS_WEAPON_PARSE_HPP_
#define CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_CSTRIKE15_CS_WEAPON_PARSE_HPP_

enum CSWeaponType
{
	KNIFE = 0,
	PISTOL,
	SMG,
	RIFLE,
	SHOTGUN,
	SNIPER,
	LMG,
	C4,
	PAD,
	GRENADE,
	UNKNOWN,
	STACKABLE,
	FISTS,
	BREACH_CHARGE,
	BUMP_MINE,
	TABLET,
	MELEE
};

enum CSWeaponID
{
	TASER = 31,
	FLASHBANG = 43,
	HE_GRENADE,
	SMOKE_GRENADE,
	MOLOTOV,
	DECOY,
	INC_GRENADE,
	REVOLVER = 64,
};

struct CCSWeaponInfo
{
	char pad0[32];
	int max_clip1;
	char pad1[204];
	char *name;
	char pad2[72];
	int weapon_type;
	char pad3[4];
	int weapon_price;
	char pad4[12];
	float cycle_time;
	char pad5[12];
	bool full_auto;
	char pad6[3];
	int damage;
	float headshot_multiplier;
	float armor_ratio;
	int bullets;
	float penetration;
	char pad7[8];
	float range;
	float range_modifier;
	char pad8[16];
	bool has_silencer;
	char pad9[23];
	float max_speed;
	float max_speed_alt;
	char pad10[100];
	float recoil_magnitude;
	float recoil_magnitude_alt;
	char pad11[16];
	float recovery_time_stand;
};

static_assert(offsetof(CCSWeaponInfo, damage) == 0x16C);
static_assert(offsetof(CCSWeaponInfo, range) == 0x188);
static_assert(offsetof(CCSWeaponInfo, penetration) == 0x17C);
static_assert(offsetof(CCSWeaponInfo, range_modifier) == 0x18C);

#endif //CSGO_CHEAT_SOURCE_SDK_GAME_SHARED_CSTRIKE15_CS_WEAPON_PARSE_HPP_
