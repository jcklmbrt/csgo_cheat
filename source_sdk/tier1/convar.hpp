#ifndef CSGO_CHEAT_CONVAR_HPP
#define CSGO_CHEAT_CONVAR_HPP

#include "memory/vtable_util.hpp"
#include "source_sdk/tier1/utlvector.hpp"

struct CVValue_t
{
	char *string;
	int  string_length;
	float float_value;
	int int_value;
};

struct ConCommandBase : mem::VTableUtil
{
	ConCommandBase *next; //0x8
	bool registered;      //0x10
	char *name;           //0x18
	char *description;    //0x20
	int flags;            //0x28
};

struct ConVar : ConCommandBase
{
	void (*callback)();  //0x30
	ConVar *parent;      //0x38
	char *default_value; //0x40

	//CVValue_t
	char *string;       //0x48
	int  string_length; //0x50
	float float_value;  //0x54
	int  int_value;     //0x58

	bool has_min;  //0x60
	float min_val; //0x64
	bool has_max;  //0x68
	float max_val; //0x6C

	CUtlVector<void (*)()> callbacks;

	float GetFloat()
	{
		return Call<float, 15>();
	}

	int GetInt()
	{
		return Call<int, 16>();
	}

	void SetValue(const char *val)
	{
		return Call<void, 17>(val);
	}
};

#endif//CSGO_CHEAT_CONVAR_HPP
