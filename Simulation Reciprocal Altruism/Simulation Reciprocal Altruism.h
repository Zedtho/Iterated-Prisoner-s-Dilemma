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
const float nMeetingsProportion = 0.5f;
const float LoserValue = 0.0f;
const float WinnerValue = 5.0f;
const float CooperateValue = 3.0f;
const float DeflectorValue = 1.0f;
const float DeathScore = 0.0f;
const float ReproduceScore = 100.0f;
int nMeetingsCoop = 0;
int nMeetingsTFT = 0;
int nMeetingsDefect = 0;




std::vector<Agent> Agents;
std::vector<Agent*> AliveAgents;
