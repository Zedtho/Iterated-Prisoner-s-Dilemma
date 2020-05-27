#pragma once
#include "Agent.h"

class Cooperator : public Agent
{
public:
	Cooperator();
	
	bool WillCooperate(Agent* agent) override
	{
		return true;
	}
	Cooperator ReturnCopy()
	{
		return *this;
	}
};