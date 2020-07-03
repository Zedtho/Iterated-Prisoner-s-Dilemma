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
	Agent::Strategy strategy;
	int score;
};


std::vector<Agent*> Agents;

void InitializeAgents();
void InitializeInputs();
void TallyAndOutput();
void Meet();
void KillOff();
int TallyType(Agent::Strategy strat, std::vector<Agent*> agents);
bool YesOrNo(float chance);