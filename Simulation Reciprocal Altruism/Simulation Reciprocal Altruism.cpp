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


	//Round-Organizer
	for (int Generation = 0; Generation < AmountGenerations; ++Generation)
	{
		InitializeAgents();

		for (int Round = 0; Round < AmountRounds; ++Round)
		{
			Meet();
			TallyAndOutput();
		}

		//Calculate who was most successful, and distribute new guys accordingly.
		int FinalAmountCoop = 0;
		int FinalAmountDef = 0;
		int FinalAmountTFT = 0;
		int FinalAmountCrossEye = 0;
		int FinalAmountTF2T = 0;
		for (unsigned int i = 0; i < Agents.size(); ++i)
		{
			switch (Agents[i]->GetStrategy())
			{
			case Agent::Strategy::COOPERATOR:
				FinalAmountCoop += Agents[i]->GetScore();
				break;
			case Agent::Strategy::DEFECTOR:
				FinalAmountDef += Agents[i]->GetScore();
				break;
			case Agent::Strategy::TFT:
				FinalAmountTFT += Agents[i]->GetScore();
				break;
			case Agent::Strategy::CROSSEYE:
				FinalAmountCrossEye += Agents[i]->GetScore();
				break;
			case Agent::Strategy::TF2T:
				FinalAmountTF2T += Agents[i]->GetScore();

			}
		}
		
		/*const int CumulativeScore = FinalAmountCoop + FinalAmountDef + FinalAmountTFT + FinalAmountCrossEye + FinalAmountTF2T;
		InitAmountCoop = std::floor(FinalAmountCoop / CumulativeScore);
		InitAmountDef = std::floor(FinalAmountDef / CumulativeScore);
		InitAmountTFT = std::floor(FinalAmountTFT / CumulativeScore);
		InitAmountCrossEye = std::floor(FinalAmountCrossEye / CumulativeScore);
		InitAmountTF2T = std::floor(FinalAmountTF2T / CumulativeScore); 
		while (Agents.size() != InitAmountCoop + InitAmountDef + InitAmountTFT + InitAmountCrossEye + InitAmountTF2T)
		{
			InitAmountCoop++; //Find a better way to do that
		}
		KillOff();*/
	}
	std::cout << "\n Final amount of agents of each type is: \n" << InitAmountCoop << "/" << InitAmountTFT << "/" <<
		InitAmountDef << "/" << InitAmountCrossEye << "/" << InitAmountTF2T;
	std::cout << "\n Thank you for using our simulation";
	int WaitForInput;
	std::cin >> WaitForInput;
	
	KillOff();
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
	std::cout << " \n" << "Insert the amount of starting Tit-for-two-tatters \n";
	std::cin >> InitAmountTF2T;


	std::cout << " \n" << "How many rounds should every generation have? \n";
	std::cin >> AmountRounds;
	std::cout << "\n" << "How many total generations until the simulation terminates? \n";
	std::cin >> AmountGenerations;
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
	for (int i = 0; i < InitAmountTF2T; ++i)
	{
		Agents.push_back(new TF2T);
	}
}
void TallyAndOutput()
{
	int AmountCoop = 0;
	int AmountDef = 0;
	int AmountTFT = 0;
	int AmountCrossEye = 0;
	int AmountTF2T = 0;
	for (unsigned int i = 0; i < Agents.size(); ++i)
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
		case Agent::Strategy::TF2T:
			AmountTF2T += Agents[i]->GetScore();

		}
	}
	std::cout << "\n" << AmountCoop << "/" << AmountTFT << "/" << AmountDef << "/" << AmountCrossEye << "/" << AmountTF2T;
}
void Meet()
{
	std::uniform_int_distribution<int> distAlive(0, Agents.size() - 1);
	for (int i = 0; i < std::floor(Agents.size()*nMeetingsProportion); ++i)
	{
		srand((unsigned int)time(NULL));
		unsigned int FirstCandidateNumber = distAlive(rng);
		unsigned int SecondCandidateNumber = distAlive(rng);

		while (FirstCandidateNumber == SecondCandidateNumber)
		{
			SecondCandidateNumber = rand() % Agents.size();
		}  //playing against itself is normally a possibility within game theory as well, but personally I find it makes no sense. It gives rather unintuitive results.

		bool WillFirstCoop = Agents[FirstCandidateNumber]->WillCooperate(Agents[SecondCandidateNumber]);
		bool WillSecondCoop = Agents[SecondCandidateNumber]->WillCooperate(Agents[FirstCandidateNumber]);

		//The actual meeting
		switch (WillFirstCoop)
		{
		case true:
			if (WillSecondCoop)
			{
				Agents[FirstCandidateNumber]->score += reward;
				Agents[SecondCandidateNumber]->score += reward;
			}
			else
			{
				Agents[FirstCandidateNumber]->score += suckersPayoff;
				Agents[SecondCandidateNumber]->score += temptation;
			}
			break;
		case false:
			if (WillSecondCoop)
			{
				Agents[FirstCandidateNumber]->score += temptation;
				Agents[SecondCandidateNumber]->score += suckersPayoff;
			}
			else
			{
				Agents[FirstCandidateNumber]->score += punishment;
				Agents[SecondCandidateNumber]->score += punishment;
			}
			break;
		}
		//Update strategies
		Agents[FirstCandidateNumber]->Update(Agents[SecondCandidateNumber], WillSecondCoop);
		Agents[SecondCandidateNumber]->Update(Agents[FirstCandidateNumber], WillFirstCoop);
	}
}
void KillOff()
{
	for (size_t i = 0; i < Agents.size(); i++)
	{
		delete Agents[i];
	}
}
