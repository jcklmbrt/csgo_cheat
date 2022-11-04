#ifndef CSGO_CHEAT_FEATURES_PLAYER_UTIL_HPP_
#define CSGO_CHEAT_FEATURES_PLAYER_UTIL_HPP_

#include "source_sdk/mathlib/mathlib.hpp"

struct C_CSPlayer;

Vector GetHitbox(C_CSPlayer *player, int hitbox, matrix3x4_t *bones);
bool ValidPlayer(C_CSPlayer *player);
bool CanShoot(C_CSPlayer *player);

#endif //CSGO_CHEAT_FEATURES_PLAYER_UTIL_HPP_
