#include <iostream>
#include <string>
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Board.h"
#include "BoardView.h"
#include "Die.h"
using namespace std;
#pragma once
class Round
{
public:
	Round();
	void PlayGame();
	int GetHumanWins() const;
	void SetHumanWins(int a_humanWins);
	int GetComputerWins() const;
	void SetComputerWins(int a_CompWins);
	string DetermineFirstPlayer();
	string GetNextPlayer() const;
	void SetNextPlayer(string & a_NextPlayer);
	void ResetBoard();
	int GetTurnNo() const;
	void SetTurnNo(int a_turn);
	int GetRoundNo() const;
	int GetCompTurn() const;
	int GetHumanTurn() const;
	void SetCompTurn(int a_turn);
	void SetHumanTurn(int a_turn);
	void SetRoundNo(int a_roundNo);
	bool GameOver();
	void RestoreGameData(ifstream & a_in, int & a_lines);
	void Rewind(ifstream & a_in);
	bool IsSavedGame();
	~Round();
private:
	Board m_board;
	BoardView m_model;
	Human m_human;
	Computer m_computer;
	Player * m_player;
	Die m_die;
	string m_NextPlayer;
	int m_CompWins;
	int m_HumanWins;
	int m_numRounds;
	int m_turnNo;
	int m_compTurns;
	int m_humanTurns;
};