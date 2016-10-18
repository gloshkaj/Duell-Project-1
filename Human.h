#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "Board.h"
#include "BoardView.h"
#include "Computer.h"
#include <cmath>
using namespace std;
class Human :
	public Player
{
public:
	Human();
	void Play(Board & a_board, int a_turn, string a_first, string a_player);
	void GetInput(Board & a_board, int a_turn);
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
	Computer m_comp;
};