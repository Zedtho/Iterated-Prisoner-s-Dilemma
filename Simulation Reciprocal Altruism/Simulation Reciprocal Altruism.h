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

std::random_device rd;
std::mt19937 rng(rd());
struct Result
{
	float InvaderScore = 0;
	float NativeScore = 0;
};


std::vector<Agent*> Agents;
std::vector<Result> Scorecard;
//Statistics
float InvaderSumPopRep = 0; //sum of all the scores of the invaders over different trials
float NativeSumPopRep = 0; //sum of all the scores of the natives over different trials
float InvaderStandardDeviation;
float NativeStandardDeviation;
float InvaderMean;
float NativeMean;


void InitializeAgents();
int main();
void Input();
void Meet();
void KillOff();
void TallyAndOutput();
int TallyType(Agent::Strategy strat, const std::vector<Agent*> agents);
void Statistics();
bool YesOrNo(float chance);
void Output();
Result TallyScore(const std::vector<Agent*> agents);
