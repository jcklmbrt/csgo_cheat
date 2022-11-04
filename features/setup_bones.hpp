#ifndef CSGO_CHEAT_FEATURES_SETUP_BONES_HPP_
#define CSGO_CHEAT_FEATURES_SETUP_BONES_HPP_

#include "source_sdk/mathlib/mathlib.hpp"

struct C_CSPlayer;

void SetupBones(C_CSPlayer *player, matrix3x4a_t *bone_to_world, int mask);

#endif //CSGO_CHEAT_FEATURES_SETUP_BONES_HPP_
