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
float InvaderSumPopRep = 0; //sum of all the scores of the invaders over different repetitions
float NativeSumPopRep = 0; //sum of all the scores of the natives over different repetitions
float InvaderMean = 0;
float NativeMean = 0;
float InvaderStandardDeviation;
float NativeStandardDeviation;



void InitializeAgents();
int main();
void InitializeInputs();
void TallyAndOutput();
void Meet();
void KillOff();
int TallyType(Agent::Strategy strat, std::vector<Agent*> agents);
void Statistics();
bool YesOrNo(float chance);