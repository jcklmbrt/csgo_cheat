cmake_minimum_required(VERSION 3.23)
project(csgo_cheat)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

# https://github.com/izenecloud/cmake/blob/master/SetCompilerWarningAll.cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

    # Disable C++ exceptions.
    string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

    # Disable RTTI.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")

else(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -fvisibility=hidden")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -ltcmalloc_minimal -lm -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-unique")

endif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

add_library(csgo_cheat SHARED
            library.cpp
            memory/vtable_util.cpp
            memory/vtable_util.hpp
            memory/interfaces.cpp
            memory/interfaces.hpp
            source_sdk/public/icvar.hpp
            util/strtools.cpp
            util/strtools.hpp
            source_sdk/public/cdll_int.hpp
            source_sdk/engine/client.hpp
            source_sdk/engine/net_chan.hpp
            source_sdk/public/inetchannelinfo.hpp
            source_sdk/public/client_class.hpp
            source_sdk/public/dt_recv.hpp
            source_sdk/tier1/convar.hpp
            source_sdk/tier1/utlvector.hpp
            source_sdk/mathlib/vector.hpp
            source_sdk/mathlib/mathlib.hpp
            source_sdk/mathlib/vmatrix.hpp
            hooks/hooks.cpp
            hooks/hooks.hpp
            source_sdk/public/bspdata.h
            source_sdk/tier1/keyvalues.hpp
            source_sdk/public/datacache/imdlcache.hpp
            source_sdk/public/icliententitylist.hpp
            source_sdk/public/engine/ivmodelinfo.hpp
            source_sdk/engine/gl_model_private.hpp
            source_sdk/public/studio.hpp
            source_sdk/public/vgui/ipanel.hpp
            source_sdk/public/materialsystem/imaterialsystem.hpp
            source_sdk/public/materialsystem/imaterial.hpp
            source_sdk/public/engine/ivmodelrender.hpp
            source_sdk/engine/gameeventmanager.hpp
            source_sdk/engine/ienginetrace.hpp
            source_sdk/public/cmodel.hpp
            source_sdk/public/gametrace.hpp
            source_sdk/game/client/c_baseentity.hpp
            source_sdk/game/client/c_baseanimating.hpp
            source_sdk/game/client/c_baseplayer.hpp
            source_sdk/game/client/cstrike15/c_cs_player.hpp
            source_sdk/public/iclientrenderable.hpp
            source_sdk/public/iclientnetworkable.hpp
            source_sdk/public/iclientunknown.hpp
            source_sdk/public/ihandleentity.hpp
            source_sdk/public/basehandle.hpp
            source_sdk/shared/ehandle.hpp
            source_sdk/public/engine/icollideable.hpp
            source_sdk/public/vphysics_interface.hpp
            source_sdk/public/iprediction.hpp
            source_sdk/public/igamemovement.hpp
            memory/netvars.cpp
            memory/netvars.hpp
            memory/offset.hpp
            memory/pattern_scan.cpp
            memory/pattern_scan.hpp
            source_sdk/public/color.hpp util/fmt.cpp util/fmt.hpp
            memory/function_pointers.cpp
            memory/function_pointers.hpp renderer/renderer.cpp renderer/renderer.hpp
            source_sdk/shaderapivk/d3d9_device.hpp
            source_sdk/shaderapivk/d3d9_types.hpp
            source_sdk/shaderapivk/d3d9_texture.hpp
            source_sdk/shaderapivk/iunknown.hpp
            source_sdk/shaderapivk/d3d9_resource.hpp
            source_sdk/shaderapivk/d3d9_stateblock.hpp
            source_sdk/game/client/input.hpp
            source_sdk/game/shared/usercmd.hpp
            source_sdk/game/client/iclientmode.hpp
            features/esp.cpp
            features/esp.hpp
            source_sdk/game/client/c_baseflex.hpp
            source_sdk/game/client/c_basecombatweapon.hpp
            source_sdk/game/shared/cstrike15/cs_weapon_parse.hpp
            source_sdk/mathlib/mathlib_base.cpp
            features/player_lagcompensation.cpp
            features/player_lagcompensation.hpp
            source_sdk/public/globalvars_base.hpp
            source_sdk/game/shared/in_buttons.hpp
            source_sdk/public/const.hpp
            source_sdk/public/datamap.hpp
            features/engine_prediction.cpp
            features/engine_prediction.hpp
            hooks/draw_model_execute.cpp
            hooks/is_hltv.cpp
            hooks/frame_stage_notify.cpp
            hooks/create_move.cpp
            hooks/paint_traverse.cpp
            hooks/end_scene.cpp
            hooks/is_paused.cpp
            source_sdk/game/client/c_basecombatcharacter.hpp
            source_sdk/game/shared/imovehelper.hpp
            features/setup_bones.cpp
            features/setup_bones.hpp
            source_sdk/public/bone_setup.hpp
            features/tickbase_manipulation.cpp
            features/tickbase_manipulation.hpp
            hooks/write_usercmd_to_delta_buffer.cpp
            menu/base_item.cpp
            menu/base_item.hpp
            source_sdk/game/shared/bone_merge_cache.hpp
            #features/bullet_penetration.cpp
            #features/bullet_penetration.hpp
            source_sdk/public/tier0/memalloc.hpp
            features/player_util.cpp features/player_util.hpp features/movement.cpp features/movement.hpp menu/menu_main.cpp menu/menu_main.hpp)
