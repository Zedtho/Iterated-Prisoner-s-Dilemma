// Simulation Reciprocal Altruism.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulation Reciprocal Altruism.h"
#include<time.h>


int main()
{
	//Requests starting parameters of simulation.
	std::cout << "Insert the amount of starting cooperators \n";
	std::cin >> InitAmountCoop;
	std::cout << " \n" << "Insert the amount of starting Tit-for-tatters \n";
	std::cin >> InitAmountTFT;
	std::cout << " \n" << "Insert the amount of starting Deflectors \n";
	std::cin >> InitAmountDefl;
	std::cout << " \n" << "Finally, how many days should this simulation go for? \n";
	std::cin >> AmountRounds;
	DeflContainer.reserve(5 * InitAmountDefl);
	CoopContainer.reserve(5 * InitAmountCoop);
	TFTContainer.reserve(5 * InitAmountTFT);
	Agents.reserve(10 * (InitAmountCoop + InitAmountDefl + InitAmountTFT));

	//Initializes Agents and AliveAgents
	//Seems to work
		for (int i = 0; i < InitAmountCoop; ++i)
		{
			CoopContainer.push_back(Cooperator());
			Agents.push_back(&CoopContainer[i]);
			AliveAgents.push_back(Agents[i]);

		}
		int arraySize = Agents.size();
		for (int i = 0; i < InitAmountDefl; ++i)
		{
			DeflContainer.push_back(Deflector());
			Agents.push_back(&DeflContainer[i]);
			AliveAgents.push_back(Agents[i + arraySize]);
		}
		arraySize = Agents.size();
		for (int i = 0; i < InitAmountTFT; ++i)
		{
			TFTContainer.push_back(TFT());
			Agents.push_back(&TFT());
			AliveAgents.push_back(Agents[i + arraySize]);
		}
	

	//Round-Organizer
	for (int Round = 0; Round < AmountRounds; ++Round)
	{
		//Handles meetings
		for (int i = 0; i < std::floor(AliveAgents.size()*nMeetingsProportion); ++i)
		{
			srand((unsigned int)time(NULL));
			unsigned int FirstCandidateNumber = rand() % AliveAgents.size();
			unsigned int SecondCandidateNumber = rand() % AliveAgents.size();

			while (FirstCandidateNumber == SecondCandidateNumber)
			{
				SecondCandidateNumber = rand() % AliveAgents.size();
			}

			bool WillFirstCoop = (*AliveAgents[FirstCandidateNumber]).WillCooperate(AliveAgents[SecondCandidateNumber]);
			bool WillSecondCoop = (*AliveAgents[SecondCandidateNumber]).WillCooperate(AliveAgents[FirstCandidateNumber]);
			//The actual meeting
			switch (WillFirstCoop)
			{
			case true:
				if (WillSecondCoop == true)
				{
					AliveAgents[FirstCandidateNumber]->Score += CooperateValue;
					AliveAgents[SecondCandidateNumber]->Score += CooperateValue;
				}
				else 
				{
					AliveAgents[FirstCandidateNumber]->Score += LoserValue;
					AliveAgents[SecondCandidateNumber]->Score += WinnerValue;
				}
				break;
			case false:
				if (WillSecondCoop == true)
				{
					AliveAgents[FirstCandidateNumber]->Score += WinnerValue;
					AliveAgents[SecondCandidateNumber]->Score += LoserValue;
				}
				else
				{
					AliveAgents[FirstCandidateNumber]->Score += DeflectorValue;
					AliveAgents[SecondCandidateNumber]->Score += DeflectorValue;
				}
				break;
			}
			//Remembering system for TFTs
			if (AliveAgents[FirstCandidateNumber]->GetStrategy() == Agent::Strategy::TFT)
			{
				switch (WillSecondCoop)
				{
				case true:
					AliveAgents[FirstCandidateNumber]->RemoveNaughty(AliveAgents[SecondCandidateNumber]);
				case false:
					AliveAgents[FirstCandidateNumber]->AddNaughty(AliveAgents[SecondCandidateNumber]);
				}
			}
			if (AliveAgents[SecondCandidateNumber]->GetStrategy() == Agent::Strategy::TFT)
			{
				switch (WillFirstCoop)
				{
				case true:
					AliveAgents[SecondCandidateNumber]->RemoveNaughty(AliveAgents[FirstCandidateNumber]);
				case false:
					AliveAgents[SecondCandidateNumber]->AddNaughty(AliveAgents[FirstCandidateNumber]);
				}
			}
		}
		//Handles deaths
		/*for (unsigned int i = 0; i < AliveAgents.size(); ++i)
		{
			if (AliveAgents[i]->GetScore() <= DeathScore)
			{
				//swaps that pointer with last one
				std::swap(AliveAgents[i], AliveAgents[AliveAgents.size() - 1]);
				AliveAgents.pop_back();

			}
		}*/
		/*//Handles reproductions
		for (unsigned int i = 0; i < AliveAgents.size(); ++i)
		{
			if (AliveAgents[i]->GetScore() > ReproduceScore)
			{
				AliveAgents[i]->Score = Agent::StartScore;
				Agent* agent = &(*AliveAgents[i]).ReturnCopy();
				Agents.push_back(agent);
				AliveAgents.push_back(agent);
			}
		}*/

		//Tally different types and output them
		int AmountCoop = 0;
		int AmountDefl = 0;
		int AmountTFT = 0;
		int AmountBogus = 0;
		for (unsigned int i = 0; i < AliveAgents.size(); ++i)
		{
			switch ((*AliveAgents[i]).GetStrategy())
			{
			case Agent::Strategy::Cooperator:
				AmountCoop++;

			case Agent::Strategy::Deflector:
				AmountDefl++;

			case Agent::Strategy::TFT:
				AmountTFT++;

			case Agent::Strategy::Bogus:
				AmountBogus++;

			}


		}
		std::cout << AmountCoop << "/" << AmountTFT << "/" << AmountDefl << "/" << AmountBogus << "\n";
	}
	std::cout << "Thank you for using our simulation";
	int WaitForInput;
	std::cin >> WaitForInput;
	return 0;
}

