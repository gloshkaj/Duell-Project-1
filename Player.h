#include <iostream>
#include <string>
#include "Board.h"
#include "BoardView.h"
using namespace std;
#pragma once
class Player
{
public:
	Player();
	// Pure virtual function. So we have to use a pointer to a player when we declare an object of the class.
	virtual void Play(Board & a_board, int a_turn, string a_first, string a_player) = 0;
	~Player();
};

