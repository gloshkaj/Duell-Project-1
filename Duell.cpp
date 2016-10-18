#include <iostream>
#include "Board.h"
#include "BoardView.h"
#include "Player.h"
#include "Human.h"
#include "Round.h"
#include "Tournament.h"
using namespace std;
/************************************************************
* Project Created by:  Garen Loshkajian                                   
* Project Description: C++ Duell Project (#1)
* Class: CMPS 366, Organization of Programming Languages   
* Project Due on: 10/21/16 (Extended Submission)
* Project Submitted on: 10/18/2016                          
************************************************************/
int main() {
	Tournament tournament; // The object that holds the set of rounds that will be played
	// Play the entire set of rounds.
	tournament.PlayTournament();
}