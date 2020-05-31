#include "stdafx.h"
#include "Agent.h"

Agent::Agent()
{
}

void Agent::Memory::AddEvent(Agent * agent, bool agentChoice)
{
		this->memory.push_back(agent);
		this->didCooperate.push_back(agentChoice);
}
