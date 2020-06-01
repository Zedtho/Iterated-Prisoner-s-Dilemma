#include "stdafx.h"
#include "TF2T.h"

void TF2T::Update(Agent * agent, bool agentChoice)
{
			memory.AddEvent(agent, agentChoice);	
}

bool TF2T::WillCooperate(Agent * agent)
{
	bool secondLastDecision = true;
	bool lastDecision = true;
	for (unsigned int i = 0; i < this->memory.size(); ++i)
	{
		if (this->memory.memory[i] == agent)
		{
			secondLastDecision = lastDecision;
			lastDecision = this->memory.didCooperate[i];
		}
	}
	return (secondLastDecision || lastDecision) ;
}
