#pragma once
#include "Agent.h"


class Deflector : public Agent
{
public:
	Deflector();
	bool WillCooperate(Agent* agent)
	{
		return false;
	}
	Deflector ReturnCopy()
	{
		return Deflector();
	}
};
