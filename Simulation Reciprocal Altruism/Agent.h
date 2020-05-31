#pragma once
#include <vector>
class Agent
{
protected:
	
public:
	Agent();
	
	int GetScore()
	{
		return score;
	}
	virtual bool WillCooperate(Agent& agent) = 0;
	virtual void Update(Agent& agent, bool Agentchoice) = 0;
protected:

	//Data
	int score = 0;
	struct Memory
	{
		std::vector<Agent*> Memory;
		std::vector<bool> DidCooperate;
	};
	Memory memory;

};
