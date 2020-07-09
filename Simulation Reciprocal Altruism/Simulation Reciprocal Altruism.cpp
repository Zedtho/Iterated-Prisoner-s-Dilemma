// Simulation Reciprocal Altruism.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Simulation Reciprocal Altruism.h"


int main()
{
	//Requests starting parameters of simulation.
	Input();
	srand(time(NULL));
	for(unsigned int Trial = 0; Trial < AmountTrials; ++Trial)
	{
		
		Initialize();
		for (int Round = 0; Round < AmountRounds; ++Round)
		{
			Meet(Round, Trial);
			if (DoOutputAvgCumulativeScore) { TallyAndOutput(); }
		}
		Scorecard.push_back(TallyScore(Agents));
		KillOff();
		std::cout << "\n ---------------- End of Trial " << Trial + 1 << " ------------------ \n";
	}
	Statistics();
	Output();
	
	return 0;
}
void Input()
{
	/*std::cout << " \n" << "Insert the amount of organisms with the Tit-for-tat strategy \n";
	std::cin >> InitAmountTFT;
	std::cout << " \n" << "Insert the amount of organisms with the Defector strategy \n";
	std::cin >> InitAmountDef;
	std::cout << " \n" << "What is the average amount of rounds each organism plays the Prisoner's dilemma? \n";
	std::cin >> AmountRounds;
	std::cout << "\n" << "How many trials should the program do? \n";
	std::cin >> AmountTrials;*/
	
	std::cout << " \n" << "Insert the clustering coefficient (must be between 0 and 1) \n";
	std::cin >> ClusteringCoefficient;
	while (ClusteringCoefficient > 1 || ClusteringCoefficient < 0)
	{
		std::cout << " \nClustering coefficient not between 0 and 1. Please try again \n";
		std::cin >> ClusteringCoefficient;
	}
	std::cout << " \n \n --------------- Processing ---------------";
}
void Output()
{
	std::cout << "\n Results:";
	std::cout << "\n   --------------------- Data ---------------- \n ---------Average of the points gotten per trial-------- \n"; 
	std::cout << "Tit-for-tat /  Defector";
	for (unsigned int i = 0; i < Scorecard.size(); ++i)
	{
		std::cout << "\n /" << Scorecard[i].InvaderScore / InitAmountTFT << "/" << Scorecard[i].NativeScore / InitAmountDef;
	}
	std::cout << "\n -------Average points gotten in a round-------- \n";
	std::cout << "Tit-for-tat /  Defector";
	for (unsigned int i = 0; i < AmountRounds; ++i)
	{
			std::cout << "\n " << MeanEachRoundTFT[i]/float(InitAmountTFT) << "/" << MeanEachRoundDef[i]/float(InitAmountDef);
	}
	std::cout << "\n Mean TFT Score per trial: " << InvaderMean << " Standard Deviation: " << InvaderStandardDeviation;
	std::cout << "\n Mean TFT Score per meeting: " << InvaderMean / (2 * AmountRounds*nMeetingsProportion) << " Standard Deviation: " << InvaderStandardDeviation / sqrt((2 * AmountRounds*nMeetingsProportion));
	std::cout << "\n Mean Defector Score per trial: " << NativeMean << " Standard Deviation: " << NativeStandardDeviation;
	std::cout << "\n Mean Defector Score per meeting: " << NativeMean / (2 * AmountRounds*nMeetingsProportion) << " Standard Deviation: " << NativeStandardDeviation / sqrt((2 * AmountRounds*nMeetingsProportion));

	std::cout << "\n The simulation is now done. Please insert any key and press enter to quit the program";


	int WaitForInput;
	std::cin >> WaitForInput;
}
void Initialize()
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

	for (int i = 0; i < AmountTrials; ++i)
	{
		std::vector<int> temp;
		CSPRTFT.push_back(temp);
		CSPRD.push_back(temp);
		for (int j = 0; j < AmountRounds; ++j)
		{
			CSPRTFT[i].push_back(0);
			CSPRD[i].push_back(0);
		}
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
void Meet(int Round, int Trial)
{
	std::uniform_int_distribution<int> distAlive(0, Agents.size() - 1);
	
	for (int i = 0; i < std::floor(Agents.size()*nMeetingsProportion); ++i)
	{
		
		unsigned int FirstCandidateNumber = distAlive(rng);
		unsigned int SecondCandidateNumber = distAlive(rng);

		//playing against itself is normally a possibility within game theory as well, but personally I find it makes no sense. It gives rather unintuitive results.
		//Choose which type it is for this round 
		
		if (YesOrNo(float(InitAmountTFT) / float(InitAmountTFT + InitAmountDef)))
		{
			//1st must be TFT
			while (Agents[FirstCandidateNumber]->GetStrategy() != Agent::Strategy::TFT)
			{
				FirstCandidateNumber = distAlive(rng);
			}
			if (YesOrNo(ClusteringCoefficient))
			{
				//2nd must be TFT now too
				while (Agents[SecondCandidateNumber]->GetStrategy() != Agent::Strategy::TFT)
				{
					SecondCandidateNumber = distAlive(rng);
				}
			}
			else
			{
				//2nd must be All-D 
				while (Agents[SecondCandidateNumber]->GetStrategy() != Agent::Strategy::DEFECTOR)
				{
					SecondCandidateNumber = distAlive(rng);
				}
			}
		}
		else
		{
			//1st must be Def w/probability InitAmountDef/(InitAmountTFT + InitAmountDef)
			while (Agents[FirstCandidateNumber]->GetStrategy() != Agent::Strategy::DEFECTOR)
			{
				FirstCandidateNumber = distAlive(rng);
			}
			
			if ( YesOrNo(float(InitAmountTFT)*float(1 - ClusteringCoefficient) / float(InitAmountDef)) )
			{
				//2nd must be TFT w/probability as shown above)
				while (Agents[SecondCandidateNumber]->GetStrategy() != Agent::Strategy::TFT)
				{
					SecondCandidateNumber = distAlive(rng);
				}
			}
			else
			{
				while (Agents[SecondCandidateNumber]->GetStrategy() != Agent::Strategy::DEFECTOR)
				{
					SecondCandidateNumber = distAlive(rng);
				}
			}
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
				switch (Agents[FirstCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += reward;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += reward;
					break;
				}
				switch (Agents[SecondCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += reward;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += reward;
					break;
				}
			}
			else
			{
				Agents[FirstCandidateNumber]->score += suckersPayoff;
				Agents[SecondCandidateNumber]->score += temptation;
				switch (Agents[FirstCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += suckersPayoff;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += suckersPayoff;
					break;
				}
				switch (Agents[SecondCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += temptation;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += temptation;
					break;
				}
			}
			break;
		case false:
			if (WillSecondCoop)
			{
				Agents[FirstCandidateNumber]->score += temptation;
				Agents[SecondCandidateNumber]->score += suckersPayoff;
				switch (Agents[FirstCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += temptation;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += temptation;
					break;
				}
				switch (Agents[SecondCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += suckersPayoff;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += suckersPayoff;
					break;
				}
			}
			else
			{
				Agents[FirstCandidateNumber]->score += punishment;
				Agents[SecondCandidateNumber]->score += punishment;
				switch (Agents[FirstCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += punishment;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += punishment;
					break;
				}
				switch (Agents[SecondCandidateNumber]->GetStrategy())
				{
				case Agent::Strategy::TFT:
					CSPRTFT[Trial][Round] += punishment;
					break;
				case Agent::Strategy::DEFECTOR:
					CSPRD[Trial][Round] += punishment;
					break;
				}
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
int TallyType(Agent::Strategy strat, const std::vector<Agent*> agents)
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

	
	for (unsigned int i = 0; i < AmountRounds; ++i)
	{
		float SumEachRoundTFT = 0;
		float SumEachRoundDef = 0;
		for (unsigned int j = 0; j < AmountTrials; ++j)
		{
			SumEachRoundTFT += float(CSPRTFT[j][i]);
			SumEachRoundDef += float(CSPRD[j][i]);
		}
		MeanEachRoundTFT.push_back(SumEachRoundTFT / float(AmountTrials));
		MeanEachRoundDef.push_back(SumEachRoundDef / float(AmountTrials));
	}
	
}
bool YesOrNo(float chance)
{
	//check if chance is valid
	if (chance > 1.0f || chance < 0.0f)
	{
		std::cout << "A certain probability was out of bounds. Please report this to the github author.";
	}
	std::bernoulli_distribution bernoulli(chance);
	return bernoulli(rng);
}
Result TallyScore(const std::vector<Agent*> agents)
{
	float AmountDef = 0;
	float AmountTFT = 0;
	for (unsigned int i = 0; i < agents.size(); ++i)
	{
		switch (agents[i]->GetStrategy())
		{
		case Agent::Strategy::DEFECTOR:
			AmountDef += agents[i]->GetScore();
			break;
		case Agent::Strategy::TFT:
			AmountTFT += agents[i]->GetScore();
			break;
		}
	}
	Result temp;
	temp.NativeScore = AmountDef;
	temp.InvaderScore = AmountTFT;
	return temp;
}
