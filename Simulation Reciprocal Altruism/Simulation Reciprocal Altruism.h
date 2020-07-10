#pragma once

#include "targetver.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "Agent.h"
#include "Cooperator.h"
#include "Defector.h"
#include "TFT.h"
#include "TF2T.h"
#include "CrossEye.h"
#include "StartingValues.h"
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>


std::random_device rd;
std::mt19937 rng(rd());
struct Result
{
	float InvaderScore = 0;
	float NativeScore = 0;
};


std::vector<Agent*> Agents;
std::vector<Result> Scorecard;
std::vector<std::vector<int>> CSPRTFT; //CumulativescoreperroundTFT - Basically given the round and trial stores the cumulative amount of points a group of TFT earned in that round and trial
std::vector<std::vector<int>> CSPRD; //CumulativescoreperroundDef - same as above but for Defectors
//Statistics
std::vector<float> MeanEachRoundTFT;
std::vector<float> MeanEachRoundDef;
float InvaderSumPopRep = 0; //sum of all the scores of the invaders over different trials - could be incorporated in CSPRTFT and CSPRD
float NativeSumPopRep = 0; //sum of all the scores of the natives over different trials  - could be incorporated in CSPRTFT and CSPRD
float InvaderStandardDeviation;
float NativeStandardDeviation;
std::vector<float> TFTStandardDeviationPerRound;
std::vector<float> DefStandardDeviationPerRound;
float InvaderMean;
float NativeMean;

void Initialize();
int main();
void Input();
void Meet(int Round, int Trial);
void KillOff();
void TallyAndOutput();
int TallyType(Agent::Strategy strat, const std::vector<Agent*> agents);
void Statistics();
bool YesOrNo(float chance);
void Output();
Result TallyScore(const std::vector<Agent*> agents);
