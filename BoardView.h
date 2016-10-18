#include <iostream>
#include "Board.h"
using namespace std;
#pragma once
class BoardView
{
public:
	BoardView();
	void DisplayBoard(Board & a_board);
private:
	bool displayed;
};