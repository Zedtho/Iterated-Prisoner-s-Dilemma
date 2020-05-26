#pragma once
#include "Agent.h"

class Cooperator : public Agent
{
public:
	Cooperator();
	
	bool WillCooperate(Agent* agent)
	{
		return true;
	}
	Cooperator ReturnCopy()
	{
		return Cooperator();
	}
};