#pragma once

#include "targetver.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "Agent.h"
#include "Cooperator.h"
#include "Defector.h"
#include "TFT.h"

int InitAmountCoop;
int InitAmountTFT;
int InitAmountDef;
int AmountRounds;
const float nMeetingsProportion = 0.5;
const int LoserValue = 0;
const int WinnerValue = 5;
const int CooperateValue = 3;
const int DefectorValue = 1;
const int DeathScore = 0;
const int ReproduceScore = 20;
void InitializeAgents();
void InitializeInputs();
std::vector<Agent*> Agents;

