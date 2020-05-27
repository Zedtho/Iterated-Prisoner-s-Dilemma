#pragma once

#include "targetver.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include "Agent.h"
#include "Cooperator.h"
#include "Deflector.h"
#include "TFT.h"
#include <random>

int InitAmountCoop;
int InitAmountTFT;
int InitAmountDefl;
int AmountRounds;
const float nMeetingsProportion = 1;
const int LoserValue = -3;
const int WinnerValue = 5;
const int CooperateValue = 3;
const int DeflectorValue = -1;
const int DeathScore = 0;
const int ReproduceScore = 20;
std::random_device dev;
std::mt19937 rng(dev());


std::vector<Agent> Agents;
std::vector<Agent*> AliveAgents;
