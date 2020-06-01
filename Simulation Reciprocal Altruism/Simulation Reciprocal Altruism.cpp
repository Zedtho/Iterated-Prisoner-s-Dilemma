// Simulation Reciprocal Altruism.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulation Reciprocal Altruism.h"
#include<time.h>
#include <random>


int main()
{
	//Requests starting parameters of simulation.
	
	InitializeInputs();
	InitializeAgents();
	
		

	//Round-Organizer
	for (int Round = 0; Round < AmountRounds; ++Round)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> distAlive(0, Agents.size() - 1);
		//Handles meetings
		for (int i = 0; i < std::floor(Agents.size()*nMeetingsProportion); ++i)
		{
			srand((unsigned int)time(NULL));
			unsigned int FirstCandidateNumber = distAlive(rng);
			unsigned int SecondCandidateNumber = distAlive(rng);

			while (FirstCandidateNumber == SecondCandidateNumber)
			{
				SecondCandidateNumber = rand() % Agents.size();
			}  //playing against itself is normally a possibility within game theory as well, but it may mess up some of the code

			bool WillFirstCoop = Agents[FirstCandidateNumber]->WillCooperate(Agents[SecondCandidateNumber]);
			bool WillSecondCoop = Agents[SecondCandidateNumber]->WillCooperate(Agents[FirstCandidateNumber]);
			//The actual meeting

			switch (WillFirstCoop)
			{
			case true:
				if (WillSecondCoop)
				{
					Agents[FirstCandidateNumber]->score += CooperateValue;
					Agents[SecondCandidateNumber]->score += CooperateValue;
				}
				else 
				{
					Agents[FirstCandidateNumber]->score += LoserValue;
					Agents[SecondCandidateNumber]->score += WinnerValue;
				}
				break;
			case false:
				if (WillSecondCoop)
				{
					Agents[FirstCandidateNumber]->score += WinnerValue;
					Agents[SecondCandidateNumber]->score += LoserValue;
				}
				else
				{
					Agents[FirstCandidateNumber]->score += DefectorValue;
					Agents[SecondCandidateNumber]->score += DefectorValue;
				}
				break;
			}
			//Update strategies
			Agents[FirstCandidateNumber]->Update(Agents[SecondCandidateNumber], WillSecondCoop);
			Agents[SecondCandidateNumber]->Update(Agents[FirstCandidateNumber], WillFirstCoop);
		}
		
		//Tally different types and output them
		int AmountCoop = 0;
		int AmountDef = 0;
		int AmountTFT = 0;
		int AmountCrossEye = 0;
		/*for (unsigned int i = 0; i < Agents.size(); ++i)
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


		}*/ //use Albinopapa's stuff!
		for(unsigned int i = 0; i < Agents.size(); ++i )
		{
			switch (Agents[i]->GetStrategy())
			{
			case Agent::Strategy::COOPERATOR:
				AmountCoop += Agents[i]->GetScore();
				break;
			case Agent::Strategy::DEFECTOR:
				AmountDef += Agents[i]->GetScore();
				break;
			case Agent::Strategy::TFT:
				AmountTFT += Agents[i]->GetScore();
				break;
			case Agent::Strategy::CROSSEYE:
				AmountCrossEye += Agents[i]->GetScore();
				break;
			}
		}
		std::cout << "\n" << AmountCoop << "/" << AmountTFT << "/" << AmountDef << "/" << AmountCrossEye;
	}
	std::cout << "Thank you for using our simulation";
	int WaitForInput;
	std::cin >> WaitForInput;
	//Deinitializes the data
	for (size_t i = 0; i < Agents.size(); i++)
	{
		delete Agents[i];
	}
	return 0;
}

void InitializeInputs()
{
	std::cout << "Insert the amount of starting cooperators \n";
	std::cin >> InitAmountCoop;
	std::cout << " \n" << "Insert the amount of starting Tit-for-tatters \n";
	std::cin >> InitAmountTFT;
	std::cout << " \n" << "Insert the amount of starting Defectors \n";
	std::cin >> InitAmountDef;
	std::cout << " \n" << "Insert the amount of starting CrossEyes \n";
	std::cin >> InitAmountCrossEye;

	std::cout << " \n" << "Finally, how many days should this simulation go for? \n";
	std::cin >> AmountRounds;
}
void InitializeAgents()
{
	for (int i = 0; i < InitAmountCoop; ++i)
	{
		Agents.push_back(new Cooperator);

	}
	for (int i = 0; i < InitAmountTFT; ++i)
	{
		Agents.push_back(new TFT);
	}
	for (int i = 0; i < InitAmountDef; ++i)
	{
		Agents.push_back(new Defector);
	}
	for (int i = 0; i < InitAmountCrossEye; ++i)
	{
		Agents.push_back(new CrossEye);
	}
}
