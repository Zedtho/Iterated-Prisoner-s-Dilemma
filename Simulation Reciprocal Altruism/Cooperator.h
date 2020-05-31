#pragma once
#include "Agent.h"

class Cooperator : public Agent
{
public:
	Cooperator() { strat = Strategy::COOPERATOR; };
	bool WillCooperate(Agent* agent) override
	{
		return true;
	}
	//Cooperators don't remember nuffin
	void Update(Agent* agent, bool agentChoice) override {};

};