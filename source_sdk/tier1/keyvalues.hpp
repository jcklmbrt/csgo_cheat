
#ifndef CSGO_CHEAT_SOURCE_SDK_TIER1_KEYVALUES_HPP_
#define CSGO_CHEAT_SOURCE_SDK_TIER1_KEYVALUES_HPP_

struct KeyValues
{
	static KeyValues *FromString(const char *name, const char *value);
	KeyValues *FindKey(const char *name, bool create);
	void SetString(const char *name, const char *value);
};

#endif //CSGO_CHEAT_SOURCE_SDK_TIER1_KEYVALUES_HPP_
