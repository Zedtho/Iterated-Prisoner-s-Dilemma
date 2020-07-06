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

	srand((unsigned int)time(NULL));
	for(unsigned int Repetition = 0; Repetition < AmountTrials; ++Repetition)
	{
		InitializeAgents();
		for (int Round = 0; Round < AmountRounds; ++Round)
		{
			Meet();
			TallyAndOutput();
		}
		
		float AmountDef = 0;
		float AmountTFT = 0;
		for (unsigned int i = 0; i < Agents.size(); ++i)
		{
			switch (Agents[i]->GetStrategy())
			{
			case Agent::Strategy::DEFECTOR:
				AmountDef += Agents[i]->GetScore();
				break;
			case Agent::Strategy::TFT:
				AmountTFT += Agents[i]->GetScore();
				break;
			}
		}
		Result temp;
		temp.NativeScore = AmountDef;
		temp.InvaderScore = AmountTFT;
		
		Scorecard.push_back(temp);

		KillOff();
		std::cout << "\n Time to try again \n";
	}
	
	Statistics();
	std::cout << "\n Results:";
	std::cout << "\n   Raw Data (Average of the points gotten by Invaders/Natives)";
	for (unsigned int i = 0; i < Scorecard.size(); ++i)
	{
		std::cout << "\n " << Scorecard[i].InvaderScore / InitAmountTFT << " \ " << Scorecard[i].NativeScore / InitAmountDef;
	}
	std::cout << "\n Mean Invader Score per trial: " << InvaderMean << " Standard Deviation: " << InvaderStandardDeviation;
	std::cout << "\n Mean Invader Score per meeting: " << InvaderMean/(2 *AmountRounds*nMeetingsProportion) << " Standard Deviation: " << InvaderStandardDeviation / sqrt((2 *AmountRounds*nMeetingsProportion));
	std::cout << "\n Mean Native Score per trial: " << NativeMean << " Standard Deviation: " << NativeStandardDeviation;
	std::cout << "\n Mean Native Score per meeting: " << NativeMean / (2 *AmountRounds*nMeetingsProportion) << " Standard Deviation: " << NativeStandardDeviation / sqrt((2 *AmountRounds*nMeetingsProportion));

	std::cout << "\n The simulation is now done. Please insert any key and press enter to quit the program";


	int WaitForInput;
	std::cin >> WaitForInput;
	
	return 0;
}
void InitializeInputs()
{
	std::cout << " \n" << "Insert the amount of organisms with the Tit-for-tat strategy \n";
	std::cin >> InitAmountTFT;
	std::cout << " \n" << "Insert the amount of organisms with the Defector strategy \n";
	std::cin >> InitAmountDef;
	std::cout << " \n" << "How many rounds should the program do? \n";
	std::cin >> AmountRounds;
	std::cout << "\n" << "How many trials should the program do? \n";
	std::cin >> AmountTrials;
	std::cout << " \n" << "Insert the clustering coefficient (must be between 0 and 1) \n";
	std::cin >> ClusteringCoefficient;
	

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
	std::cout << "\n"  "/" << AmountTFT / TallyType(Agent::Strategy::TFT, Agents) << "/" << AmountDef / TallyType(Agent::Strategy::DEFECTOR, Agents);
}
void Meet()
{
	std::uniform_int_distribution<int> distAlive(0, Agents.size() - 1);
	
	for (int i = 0; i < std::floor(Agents.size()*nMeetingsProportion); ++i)
	{
		
		unsigned int FirstCandidateNumber = distAlive(rng);
		unsigned int SecondCandidateNumber = distAlive(rng);

		//playing against itself is normally a possibility within game theory as well, but personally I find it makes no sense. It gives rather unintuitive results.
		//Choose which type it is for this round (only necessary if it is not one of the invaded
		bool Cluster = YesOrNo(ClusteringCoefficient);
		switch (Agents[FirstCandidateNumber]->GetStrategy())
		{
		case Agent::Strategy::TFT:
			if (Cluster)
			{
				while(Agents[SecondCandidateNumber]->GetStrategy() != Agent::Strategy::TFT)
				{
					SecondCandidateNumber = rand() % Agents.size();
				}
			}
			else
			{
				while (Agents[SecondCandidateNumber]->GetStrategy() == Agent::Strategy::TFT)
				{
					SecondCandidateNumber = rand() % Agents.size();
				}
			}
			break;
		default:
			if (Agents[SecondCandidateNumber]->GetStrategy() == Agent::Strategy::TFT && Cluster)
			{
				while (Agents[FirstCandidateNumber]->GetStrategy() != Agent::Strategy::TFT)
				{
					FirstCandidateNumber = rand() % Agents.size();
				}
			}
			break;
		}
		
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
	for (size_t i = 0; i < Agents.size(); ++i)
	{
		delete Agents[i];
	}
	Agents.clear();
}
int TallyType(Agent::Strategy strat, std::vector<Agent*> agents)
{
	int tally = 0;
	for (unsigned int i = 0; i < agents.size(); ++i)
	{
		if (agents[i]->GetStrategy() == strat)
		{
			tally++;
		}
	}
	return tally;
}
void Statistics()
{
	//Why does it go through this loop 5 times?
	for (unsigned int i = 0; i < Scorecard.size(); ++i)
	{
		InvaderSumPopRep += Scorecard[i].InvaderScore;
		NativeSumPopRep += Scorecard[i].NativeScore;
	}
	//Calculate mean - error here
	float InvaderSumPopMean = InvaderSumPopRep / Scorecard.size();
	float NativeSumPopMean = NativeSumPopRep / Scorecard.size();
	InvaderMean = InvaderSumPopMean / ((float)InitAmountTFT);
	NativeMean = NativeSumPopMean / ((float)InitAmountDef);
	//Calculate standard deviation
	float InvaderSumSquares = 0;
	float NativeSumSquares = 0;
	for (unsigned int i = 0; i < Scorecard.size(); ++i)
	{
		InvaderSumSquares += (Scorecard[i].InvaderScore/InitAmountTFT  - InvaderMean)*(Scorecard[i].InvaderScore / InitAmountTFT - InvaderMean);
		NativeSumSquares += (Scorecard[i].NativeScore/InitAmountDef - NativeMean)*(Scorecard[i].NativeScore/InitAmountDef - NativeMean);
	}

	InvaderStandardDeviation = sqrt(InvaderSumSquares / Scorecard.size());
	NativeStandardDeviation = sqrt(NativeSumSquares / Scorecard.size());

}
bool YesOrNo(float chance)
{
	//check if chance is valid
	if (chance > 1.0f || chance < 0.0f)
	{
		std::cout << "fuck";

	}
	return rand() % 100 < (chance * 100);

	
}

