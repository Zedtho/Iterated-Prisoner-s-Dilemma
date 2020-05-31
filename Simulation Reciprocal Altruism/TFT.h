#pragma once

#include "Agent.h"


class TFT : public Agent
{
	
public:
	void Update(Agent* agent, bool agentChoice);
	TFT() { strat = Strategy::TFT; };
	bool WillCooperate(Agent* agent) override;


};

