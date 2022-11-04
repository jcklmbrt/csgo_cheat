#ifndef CSGO_CHEAT_SOURCE_SDK_PUBLIC_DATAMAP_HPP_
#define CSGO_CHEAT_SOURCE_SDK_PUBLIC_DATAMAP_HPP_

#include <cstring>
#include <cstddef>

typedef enum _fieldtypes
{
	FIELD_VOID = 0,                        // No type or value
	FIELD_FLOAT,                        // Any floating point value
	FIELD_STRING,                        // A string ID (return from ALLOC_STRING)
	FIELD_VECTOR,                        // Any vector, QAngle, or AngularImpulse
	FIELD_QUATERNION,                // A quaternion
	FIELD_INTEGER,                        // Any integer or enum
	FIELD_BOOLEAN,                        // boolean, implemented as an int, I may use this as a hint for compression
	FIELD_SHORT,                        // 2 byte integer
	FIELD_CHARACTER,                // a byte
	FIELD_COLOR32,                        // 8-bit per channel r,g,b,a (32bit color)
	FIELD_EMBEDDED,                        // an embedded object with a datadesc, recursively traverse and embedded class/structure based on an additional typedescription
	FIELD_CUSTOM,                        // special type that contains function pointers to it's read/write/parse functions

	FIELD_CLASSPTR,                        // CBaseEntity *
	FIELD_EHANDLE,                        // Entity handle
	FIELD_EDICT,                        // edict_t *

	FIELD_POSITION_VECTOR,        // A world coordinate (these are fixed up across level transitions automagically)
	FIELD_TIME,                                // a floating point time (these are fixed up automatically too!)
	FIELD_TICK,                                // an integer tick count( fixed up similarly to time)
	FIELD_MODELNAME,                // Engine string that is a model name (needs precache)
	FIELD_SOUNDNAME,                // Engine string that is a sound name (needs precache)

	FIELD_INPUT,                        // a list of inputed data fields (all derived from CMultiInputVar)
	FIELD_FUNCTION,                        // A class function pointer (Think, Use, etc)

	FIELD_VMATRIX,                        // a vmatrix (output coords are NOT worldspace)

	// NOTE: Use float arrays for local transformations that don't need to be fixed up.
	FIELD_VMATRIX_WORLDSPACE,// A VMatrix that maps some local space to world space (translation is fixed up on level transitions)
	FIELD_MATRIX3X4_WORLDSPACE,        // matrix3x4_t that maps some local space to world space (translation is fixed up on level transitions)

	FIELD_INTERVAL,                        // a start and range floating point interval ( e.g., 3.2->3.6 == 3.2 and 0.4 )
	FIELD_MODELINDEX,                // a model index
	FIELD_MATERIALINDEX,        // a material index (using the material precache string table)

	FIELD_VECTOR2D,                        // 2 floats
	FIELD_INTEGER64,                // 64bit integer

	FIELD_VECTOR4D,                        // 4 floats

	FIELD_TYPECOUNT,                // MUST BE LAST
} fieldtype_t;

enum
{
	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,

	// Must be last
	TD_OFFSET_COUNT,
};

struct datamap_t;
struct ISaveRestoreOps;

struct typedescription_t
{
	fieldtype_t field_type;
	const char *field_name;
	int field_offset; // Local offset value
	unsigned short field_size;
	short flags;
	const char *external_name;
	ISaveRestoreOps *save_restore_ops;
	//https://gitlab.com/KittenPopo/csgo-2018-source/-/blob/main/game/shared/saverestore.cpp#L142
	//??????????????????
	void *input_func[2];
	datamap_t *td;
	int field_size_in_bytes;
	typedescription_t *override_field;
	int override_count;
	float field_tolerance;
	int flat_offset[TD_OFFSET_COUNT];
	unsigned short flat_group;
};

ASSERT_OFFSET(typedescription_t, field_name, 0x8);
//static_assert(offsetof(typedescription_t, field_size_in_bytes) == 0x40);
ASSERT_OFFSET(typedescription_t, field_offset, 0x10);
ASSERT_OFFSET(typedescription_t, flags, 0x16);
ASSERT_OFFSET(typedescription_t, external_name, 0x18);
ASSERT_OFFSET(typedescription_t, input_func, 0x28);
//static_assert(offsetof(typedescription_t, flat_offset) == 0x5c);

//-----------------------------------------------------------------------------
// Purpose: stores the list of objects in the hierarchy
//			used to iterate through an object's data descriptions
//-----------------------------------------------------------------------------
struct datamap_t
{
	typedescription_t *data_desc;
	int data_num_fields;
	char const *data_class_name;
	datamap_t *base_map;
	bool chains_validated;
	bool packed_offsets_computed;
	int packed_size;

	ptrdiff_t Find(const char *name)
	{
		for(datamap_t *iter = this; iter; iter = iter->base_map)
		{
			for(int i = 0; i < iter->data_num_fields; i++)
			{
				if(!iter->data_desc[i].field_name)
					continue;

				if(!strcmp(iter->data_desc[i].field_name, name))
					return iter->data_desc[i].field_offset; //[TD_OFFSET_NORMAL];

				if(iter->data_desc[i].field_type == FIELD_EMBEDDED && iter->data_desc[i].td)
				{
					datamap_t *td = iter->data_desc[i].td;

					if(ptrdiff_t offset = td->Find(name))
						return 0;
				}
			}
		}

		return 0;
	}
};


ASSERT_OFFSET(datamap_t, data_num_fields, 0x8);
ASSERT_OFFSET(datamap_t, data_class_name, 0x10);
ASSERT_OFFSET(datamap_t, base_map, 0x18);

#endif //CSGO_CHEAT_SOURCE_SDK_PUBLIC_DATAMAP_HPP_
