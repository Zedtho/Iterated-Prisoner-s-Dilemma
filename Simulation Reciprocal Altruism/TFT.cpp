#include "stdafx.h"
#include "TFT.h"

void TFT::Update(Agent* agent, bool agentChoice)
{
	bool isMemorized = false;
	int index;
	for( unsigned int i = 0; i < this->memory.size(); ++i)
	{
		if (memory.memory[i] == agent)
		{
			isMemorized = true;
			index = i;
		}
	}

	if (isMemorized == true)
	{
		this->memory.didCooperate[index] = agentChoice;
	}
	else
	{
		memory.AddEvent(agent, agentChoice);
	}
}

TFT::TFT() : Agent()
{
	
}

bool TFT::WillCooperate(Agent * agent)
{
	bool willCooperate = true;
	for (unsigned int i = 0; i < this->memory.size(); ++i)
	{
		if (this->memory.memory[i] == agent)
		{
			willCooperate = this->memory.didCooperate[i];
		}
	}
	return willCooperate;
}
