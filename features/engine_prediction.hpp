#ifndef CSGO_CHEAT_FEATURES_ENGINE_PREDICTION_HPP_
#define CSGO_CHEAT_FEATURES_ENGINE_PREDICTION_HPP_

#include "source_sdk/public/igamemovement.hpp"

struct CUserCmd;

struct EnginePrediction
{
	EnginePrediction(CUserCmd *);
	~EnginePrediction();

	CMoveData m_movedata;
	float m_frametime;
	float m_curtime;
};

#endif //CSGO_CHEAT_FEATURES_ENGINE_PREDICTION_HPP_
