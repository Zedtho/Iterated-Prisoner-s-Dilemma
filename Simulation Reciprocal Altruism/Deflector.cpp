#include "stdafx.h"
#include "Deflector.h"

Deflector::Deflector() : Agent()
{
	strategy = Strategy::Deflector;
	Score = StartScore;
}
