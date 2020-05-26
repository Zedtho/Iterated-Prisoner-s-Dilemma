#pragma once
#include <vector>
class Agent
{
public:
	Agent();
	enum Strategy
	{
		Cooperator,
		TFT,
		Deflector,
		Bogus
	};
	static const int StartScore = 4;
	int Score = StartScore;
	Strategy GetStrategy()
	{
		return strategy;
	}
	int GetScore()
	{
		return Score;
	}
	virtual bool WillCooperate(Agent* agent) { return 1; };
	//The following two are only functions used by TFT, but has to be declared here to work. Seems suboptimal.
	void RemoveNaughty(Agent* agent){};
	void AddNaughty(Agent* agent){};
	Agent ReturnCopy() { return *this;};
protected:
	Strategy strategy;

};
