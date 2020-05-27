#include "stdafx.h"
#include "Agent.h"

Agent::Agent(Strategy strat)
{
	strategy = strat;
	Score = StartScore;
}

Agent::Agent(Agent* agent)
{
	strategy = (*agent).strategy;
	Score = StartScore;
}

bool Agent::WillCooperate(Agent* agent)
{
	bool WillCooperate;
	switch (strategy)
	{
	case Strategy::Cooperator:
		WillCooperate = true;
		break;

	case Strategy::Deflector:
		WillCooperate = false;
		break;

	case Strategy::TFT:
		WillCooperate = true;
		for (unsigned int i = 0; i < Naughtylist.size(); ++i)
		{
			if (Naughtylist[i] == agent)
			{
				WillCooperate = false;
			}
		}
		break;
	default: 
		//Throw an exception
		break;
	
		}
	return WillCooperate;
}
