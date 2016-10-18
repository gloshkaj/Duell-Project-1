#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Die.h"
using namespace std;

#pragma once
class Board
{
public:
	Board();
	typedef string(&Duell)[9][10];
	void DrawBoard();
	void PrintBoard(ostream & a_out);
	string GetStartingPiece(string a_col[], int a_index, string a_player);
	string ** GetBoard();
	void UpdateComputerMove(string ** a_board, int a_front, int a_lat, string & a_firstDirection, string & a_secondDirection, string & a_die, int a_NextRow, int a_NextCol, int a_DestRow, int a_DestCol);
	void UpdateBoard(string ** a_board, int a_front, int a_lat, string & a_firstDirection, string & a_secondDirection, string & a_die, int a_NextRow, int a_NextCol, int a_DestRow, int a_DestCol);
	bool FindKeyPiece(string a_key);
	int FindColKeyPiece();
	int FindRowKeyPiece();
	int FindRowCompKeyPiece();
	int FindColCompKeyPiece();
	int GetTopPiece() const;
	int GetRightPiece() const;
	int GetX() const;
	int GetY() const;
	void SetX(int a_xcoord);
	void SetY(int a_ycoord);
	void SetTop(int a_top);
	void SetRight(int a_right);
	void ReadSerializationFile(ifstream & a_in, int & a_lines);
private:
	string **m_board;
	Die m_die;
	int m_xcoord;
	int m_ycoord;
	int m_topPiece;
	int m_rightPiece;
};