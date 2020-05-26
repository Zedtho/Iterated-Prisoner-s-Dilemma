#include "stdafx.h"
#include "TFT.h"

void TFT::RemoveNaughty(Agent* agent)
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

TFT::TFT() : Agent()
{
	strategy = Strategy::TFT;
	Score = StartScore;
}
