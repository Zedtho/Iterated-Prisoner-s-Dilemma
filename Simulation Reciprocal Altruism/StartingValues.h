#pragma once
int InitAmountCoop = 0;
int InitAmountTFT = 0;
int InitAmountDef = 0;
int InitAmountCrossEye = 0;
int InitAmountTF2T = 0;
const float ClusteringCoefficient = 0.5; // should be between 0 and 1, it's the chance a TFT will meet ANY other TFT - possible problem as covariance does not scale but okay
const float nMeetingsProportion = 0.5; //(amount of meetings per round)/(amount of characters)
const int suckersPayoff = 0;
const int temptation = 5;
const int reward = 3;
const int punishment = 1;
const int DeathScore = 0;
const int ReproduceScore = 20;
int AmountRounds;
int AmountGenerations;