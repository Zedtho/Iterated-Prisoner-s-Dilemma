#include "stdafx.h"
#include "Cooperator.h"

Cooperator::Cooperator() : Agent()
{
	strategy = Strategy::Cooperator;
	Score = StartScore;

}
