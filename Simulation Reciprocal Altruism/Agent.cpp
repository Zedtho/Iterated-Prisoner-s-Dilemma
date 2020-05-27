#include "stdafx.h"
#include "Agent.h"
#include <iostream>

Agent::Agent(Strategy strat)
{
	strategy = strat;
	Score = StartScore;
}

const float Agent::StartScore= 10.0f;

Agent::Agent(Agent* agent)
{
	strategy = (*agent).strategy;
	Score = StartScore;
}

bool Agent::WillCooperate(Agent* agent)
{
	bool WillCooperate =true;
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

				std::cout << "\n Naughty boi ";
			}
		}
		break;
	default: 
		std::cout << "SHIT";
		//Throw an exception
		break;
	
		}
	return WillCooperate;
}
