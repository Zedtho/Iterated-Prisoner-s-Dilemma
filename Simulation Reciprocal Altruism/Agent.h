#pragma once
#include <vector>
class Agent
{
public:
	enum Strategy
	{
		Cooperator,
		TFT,
		Deflector,
		Bogus
	};

protected:
	std::vector<Agent*> Naughtylist;
	Strategy strategy;

public:


	static const int StartScore = 4;
	int Score = StartScore;

	//functions
	Strategy GetStrategy()
	{
		return strategy;
	}
	int GetScore()
	{
		return Score;
	}
	bool WillCooperate(Agent* agent);
	Agent ReturnCopy() { return *this;};
	Agent(Strategy strat);
	void AddNaughty(Agent* agent)
	{
		Naughtylist.push_back(agent);
	}
	void RemoveNaughty(Agent* agent)
	{
		for (unsigned int i = 0; i < Naughtylist.size(); ++i)
		{
			if (Naughtylist[i] == agent)
			{
				std::swap(Naughtylist[i], Naughtylist[Naughtylist.size() - 1]);
				Naughtylist.pop_back();
			}
		}


}

};
