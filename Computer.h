#pragma once
#include "Player.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;
class Computer :
	public Player
{
public:
	Computer();
	void Play(Board & a_board, int a_turn, string a_first, string a_player);
	bool HelpHuman(Board & a_board);
	bool IsValidDestinationSquare(string ** a_board, int a_top);
	bool IsValidHumanDestinationSquare(string ** a_board, int a_top);
	bool IsValidFrontPath(string ** a_board);
	bool IsValidFrontLatPath(string ** a_board);
	bool IsValidLatFrontPath(string ** a_board);
	bool IsValidLatPath(string ** a_board);
	bool IsValidPath(string ** a_board);
	bool TakeSuggestion();
	void GetAllCoordsInBlockingPath(pair<int, int> a_coords[], string ** a_board, int & a_count);
	bool MakeBlockingMove(Board & a_game, pair<int, int> a_coords[], string ** a_board, int & a_count, char a_player);
private:
	string m_direction;
	int m_NextRow;
	int m_NextCol;
	int m_DestRow;
	int m_DestCol;
	int m_frontMove;
	int m_lateralMove;
	string m_secondDirection;
	Board m_board;
	BoardView m_model;
};

