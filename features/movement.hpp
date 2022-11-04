#ifndef CSGO_CHEAT_FEATURES_MOVEMENT_HPP_
#define CSGO_CHEAT_FEATURES_MOVEMENT_HPP_

struct EnginePrediction;
struct C_CSPlayer;
struct CUserCmd;

void BunnyHop_PrePred(C_CSPlayer *local);
void BunnyHop_PostPred(EnginePrediction &pred, C_CSPlayer *local, CUserCmd *cmd);

#endif //CSGO_CHEAT_FEATURES_MOVEMENT_HPP_
