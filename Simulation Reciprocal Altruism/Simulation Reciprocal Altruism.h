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
std::random_device rd;
std::mt19937 rng(rd());

int AmountRounds;
int AmountGenerations;
const float nMeetingsProportion = 0.5;
const int suckersPayoff = 0;
const int temptation = 5;
const int reward = 3;
const int punishment = 1;
const int DeathScore = 0;
const int ReproduceScore = 20;
void InitializeAgents();
void InitializeInputs();
void TallyAndOutput();
void Meet();
std::vector<Agent*> Agents;

