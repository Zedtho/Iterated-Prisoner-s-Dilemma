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
	

	//Initializes Agents and Agents
	//Seems to work
		for (int i = 0; i < InitAmountCoop; ++i)
		{
			Agents.push_back(new Cooperator);

		}
		for (int i = 0; i < InitAmountDefl; ++i)
		{
			Agents.push_back(new Deflector);
		}
		for (int i = 0; i < InitAmountTFT; ++i)
		{
			Agents.push_back(new TFT);
		}
	
		

	//Round-Organizer
	for (int Round = 0; Round < AmountRounds; ++Round)
	{
		//Handles meetings
		for (int i = 0; i < std::floor(Agents.size()*nMeetingsProportion); ++i)
		{
			srand((unsigned int)time(NULL));
			unsigned int FirstCandidateNumber = rand() % Agents.size();
			unsigned int SecondCandidateNumber = rand() % Agents.size();

			while (FirstCandidateNumber == SecondCandidateNumber)
			{
				SecondCandidateNumber = rand() % Agents.size();
			}

			bool WillFirstCoop = Agents[FirstCandidateNumber]->WillCooperate(Agents[SecondCandidateNumber]);
			bool WillSecondCoop = Agents[SecondCandidateNumber]->WillCooperate(Agents[FirstCandidateNumber]);
			//The actual meeting
			switch (WillFirstCoop)
			{
			case true:
				if (WillSecondCoop == true)
				{
					Agents[FirstCandidateNumber]->Score += CooperateValue;
					Agents[SecondCandidateNumber]->Score += CooperateValue;
				}
				else 
				{
					Agents[FirstCandidateNumber]->Score += LoserValue;
					Agents[SecondCandidateNumber]->Score += WinnerValue;
				}
				break;
			case false:
				if (WillSecondCoop == true)
				{
					Agents[FirstCandidateNumber]->Score += WinnerValue;
					Agents[SecondCandidateNumber]->Score += LoserValue;
				}
				else
				{
					Agents[FirstCandidateNumber]->Score += DeflectorValue;
					Agents[SecondCandidateNumber]->Score += DeflectorValue;
				}
				break;
			}
			//Remembering system for TFTs
			if (Agents[FirstCandidateNumber]->GetStrategy() == Agent::Strategy::TFT)
			{
				switch (WillSecondCoop)
				{
				case true:
					Agents[FirstCandidateNumber]->RemoveNaughty(Agents[SecondCandidateNumber]);
				case false:
					Agents[FirstCandidateNumber]->AddNaughty(Agents[SecondCandidateNumber]);
				}
			}
			if (Agents[SecondCandidateNumber]->GetStrategy() == Agent::Strategy::TFT)
			{
				switch (WillFirstCoop)
				{
				case true:
					Agents[SecondCandidateNumber]->RemoveNaughty(Agents[FirstCandidateNumber]);
				case false:
					Agents[SecondCandidateNumber]->AddNaughty(Agents[FirstCandidateNumber]);
				}
			}
		}
		
		//Tally different types and output them
		int AmountCoop = 0;
		int AmountDefl = 0;
		int AmountTFT = 0;
		int AmountBogus = 0;
		for (unsigned int i = 0; i < Agents.size(); ++i)
		{
			switch (Agents[i]->GetStrategy())
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
	//DELETE STUFF FROM Agents, FREE THE HEAP
	return 0;
}

