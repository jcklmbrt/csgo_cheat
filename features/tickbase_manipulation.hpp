#ifndef CSGO_CHEAT_FEATURES_TICKBASE_MANIPULATION_HPP_
#define CSGO_CHEAT_FEATURES_TICKBASE_MANIPULATION_HPP_

struct C_CSPlayer;
struct CUserCmd;

extern int g_ticks_to_shift;

void DoubleTap(C_CSPlayer *local, CUserCmd *cmd);

#endif //CSGO_CHEAT_FEATURES_TICKBASE_MANIPULATION_HPP_
