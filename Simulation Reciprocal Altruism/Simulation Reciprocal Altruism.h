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
const float nMeetingsProportion = 1.0f;
const float LoserValue = 2.0f;
const float WinnerValue = 9.0f;
const float CooperateValue = 6.0f;
const float DeflectorValue = 3.0f;
const float DeathScore = 0.0f;
const float ReproduceScore = 100.0f;



std::vector<Agent> Agents;
std::vector<Agent*> AliveAgents;
