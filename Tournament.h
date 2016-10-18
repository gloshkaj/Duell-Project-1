#pragma once
#include <iostream>
#include <string>
#include "Round.h"
class Tournament
{
public:
	Tournament();
	void PlayTournament();
	void DetermineWinner();
	~Tournament();
private:
	Round m_round;
};

