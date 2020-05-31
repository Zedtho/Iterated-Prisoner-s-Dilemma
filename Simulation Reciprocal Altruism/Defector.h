#pragma once
#include "Agent.h"


class Defector : public Agent
{
public:
	Defector() { strat = Strategy::DEFECTOR; };
	bool WillCooperate(Agent* agent) override
	{
		return false;
	}
	void Update(Agent* agent, bool agentChoice) override
	{};
	
};
