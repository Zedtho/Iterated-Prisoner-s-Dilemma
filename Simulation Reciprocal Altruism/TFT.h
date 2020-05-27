#pragma once

#include "Agent.h"


class TFT : public Agent
{
	std::vector<Agent*> Naughtylist;
	
public:
	void AddNaughty(Agent* agent)
	{
		Naughtylist.push_back(agent);
	}
	void RemoveNaughty(Agent* agent);
	TFT();
	bool WillCooperate(Agent* agent) override 
	{
		bool WillCooperate = true;
		for (unsigned int i = 0; i < Naughtylist.size(); ++i)
		{
			if (Naughtylist[i] == agent)
			{
				WillCooperate = false;
			}
		}
		return WillCooperate;
	}
	const TFT ReturnCopy()
	{
		return TFT();
	}

};

