#pragma once
#include "Agent.h"
class TF2T: public Agent
{
public:
	void Update(Agent* agent, bool agentChoice) override;
	TF2T() { strat = Strategy::TF2T; };
	bool WillCooperate(Agent* agent) override;
};