#include <iostream>
#include <string>
#include <cmath>
using namespace std;
#pragma once
class Die
{
public:
	Die();
	Die(int a_top, int a_right);
	int GetTop() const;
	int GetRight() const;
	void SetTop(int a_top);
	void SetRight(int a_right);
	string ToString();
	void DetermineLateralMovement(int a_lateral[], int a_frontal[]);
	void DetermineReverseLateralMovement(int a_lateral[], int a_frontal[]);
	void DetermineFrontalMovement(int a_frontal[], int a_lateral[]);
	void DetermineReverseFrontalMovement(int a_frontal[], int a_lateral[]);
	string Rotate(string** a_board, string & a_die, string & a_front, int a_frontDist, string & a_lat, int a_latDist, int a_NextRow, int a_NextCol, int a_DestRow, int a_DestCol);
	string RotateComputerDie(string** a_board, string & a_die, string & a_front, int a_frontDist, string & a_lat, int a_latDist, int a_NextRow, int a_NextCol, int a_DestRow, int a_DestCol);
private:
	int m_top;
	int m_right;
};

