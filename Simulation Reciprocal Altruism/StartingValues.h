#pragma once
#include <iostream>
#include <fstream>
//Game parameters
int InitAmountCoop = 0;
int InitAmountTFT = 5;
int InitAmountDef = 100;
int InitAmountCrossEye = 0;
int InitAmountTF2T = 0;
float ClusteringCoefficient = 0.5f; // should be between 0 and 1, it's the chance a TFT will meet ANY other TFT - possible problem as covariance does not scale but okay
const float nMeetingsProportion = 0.5; //(amount of meetings per round)/(amount of agents)
int AmountRounds = 200;
int AmountTrials = 100;

// Prisoner's dilemma
const int suckersPayoff = 0;
const int temptation = 5;
const int reward = 3;
const int punishment = 1;

//Output variables
bool DoOutputAvgCumulativeScore = false;
std::string AvgPointsPerTrialName = "AvgPointsPerTrial";
std::string AvgPointsPerRoundName = "AvgPointsPerRound";
std::string StatsName = "Statistics";