#pragma once
#include "Agent.h"
#include <random>
class CrossEye : public Agent
{
public:
	void Update(Agent* agent, bool agentChoice) {};
	bool WillCooperate(Agent* agent) {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> dist(0, 1);
		return dist(rng);
	}
	CrossEye() { strat = Strategy::CROSSEYE; }
};
