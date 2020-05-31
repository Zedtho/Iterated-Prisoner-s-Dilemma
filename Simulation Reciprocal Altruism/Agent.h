#pragma once
#include <vector>
class Agent
{
	
public:
	Agent();
	int score = 0;

	int GetScore()
	{
		return score;
	}
	virtual bool WillCooperate(Agent* agent) = 0;
	virtual void Update(Agent* agent, bool Agentchoice) = 0;

protected:

	//Data
	struct Memory
	{
		std::vector<Agent*> memory;
		std::vector<bool> didCooperate;
		unsigned int size() { return this->memory.size(); }
		void AddEvent(Agent* agent, bool agentChoice);
	};
	Memory memory;

};
