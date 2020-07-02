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
int InitAmountCoop;
int InitAmountTFT;
int InitAmountDef;
int InitAmountCrossEye;
int InitAmountTF2T;
const float CovarianceBetweenTFT = 0.5;
std::random_device rd;
std::mt19937 rng(rd());
struct Result
{
	Agent::Strategy strategy;
	int score;
};
int AmountRounds;
int AmountGenerations;
const float nMeetingsProportion = 0.5;
const int suckersPayoff = 0;
const int temptation = 5;
const int reward = 3;
const int punishment = 1;
const int DeathScore = 0;
const int ReproduceScore = 20;
std::vector<Agent*> Agents;

void InitializeAgents();
void InitializeInputs();
void TallyAndOutput();
void Meet();
void KillOff();
int TallyType(Agent::Strategy strat, std::vector<Agent*> agents)

