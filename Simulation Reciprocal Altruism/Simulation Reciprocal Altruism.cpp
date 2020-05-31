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
	std::cout << " \n" << "Insert the amount of starting Defectors \n";
	std::cin >> InitAmountDef;
	std::cout << " \n" << "Finally, how many days should this simulation go for? \n";
	std::cin >> AmountRounds;
	

	//Initializes Agents and Agents
	//Seems to work
		for (int i = 0; i < InitAmountCoop; ++i)
		{
			Agents.push_back(new Cooperator);

		}
		for (int i = 0; i < InitAmountDef; ++i)
		{
			Agents.push_back(new Defector);
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

			/*while (FirstCandidateNumber == SecondCandidateNumber)
			{
				SecondCandidateNumber = rand() % Agents.size();
			}*/ //playing against itself is normally a possibility within game theory as well

			bool WillFirstCoop = Agents[FirstCandidateNumber]->WillCooperate(Agents[SecondCandidateNumber]);
			bool WillSecondCoop = Agents[SecondCandidateNumber]->WillCooperate(Agents[FirstCandidateNumber]);
			//The actual meeting

			switch (WillFirstCoop)
			{
			case true:
				if (WillSecondCoop == true)
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
				if (WillSecondCoop == true)
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
		int AmountDefl = 0;
		int AmountTFT = 0;
		int AmountBogus = 0;
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
		std::cout << AmountCoop << "/" << AmountTFT << "/" << AmountDefl << "/" << AmountBogus << "\n";
	}
	std::cout << "Thank you for using our simulation";
	int WaitForInput;
	std::cin >> WaitForInput;
	//DELETE STUFF FROM Agents, FREE THE HEAP
	return 0;
}

