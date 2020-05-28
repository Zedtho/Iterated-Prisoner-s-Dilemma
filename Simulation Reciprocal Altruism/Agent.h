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


	static const float StartScore;
	float Score = StartScore;

	//functions
	Strategy GetStrategy()
	{
		return strategy;
	}
	float GetScore()
	{
		return Score;
	}
	bool WillCooperate(Agent* agent);
	Agent ReturnCopy() { return *this;};
	Agent(Strategy strat);
	Agent(Agent* agent);
	void AddNaughty(Agent* agent)
	{
		/*bool AlreadyNaughty = false;
		for (unsigned int i = 0; i < Naughtylist.size(); ++i)
		{
			if (Naughtylist[i] = agent)
			{
				AlreadyNaughty = true;
			}
		}
		if (AlreadyNaughty = false)
		{*/
			Naughtylist.push_back(agent);
		//}
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
