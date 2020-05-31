#pragma once

#include "Agent.h"


class TFT : public Agent
{
	
public:
	void Update(Agent* agent, bool agentChoice);
	TFT();
	bool WillCooperate(Agent* agent) override;


};

