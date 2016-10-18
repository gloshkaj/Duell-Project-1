#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include "Round.h"
using namespace std;
// Initialize all variables
Round::Round()
{
	srand(time(0));
	m_NextPlayer = "";
	m_CompWins = 0;
	m_HumanWins = 0;
	m_numRounds = 0;
	m_turnNo = 0;
	m_humanTurns = 0;
	m_compTurns = 0;
}
/* *********************************************************************
Function Name: GameOver
Purpose: To check if the opponent's key die was captured or if the key piece was placed on the opponent's key square.
Parameters:
None
Returns: True if the opponent's key die cannot be found or if the key piece was placed on the opponent's key square. False otherwise.
********************************************************************* */
bool Round::GameOver() { // In every case that returns true, reset the board.
	if (m_board.GetBoard()[1][5] == "H11") { // Human placed key piece on computer's key square. Human wins. Increment human wins.
		cout << "Garen placed his key die on the computer's key square! Garen has won this round!" << endl;
		m_HumanWins++;
		cout << "The computer won " << m_CompWins << " rounds and Garen won " << m_HumanWins << " rounds. " << endl;
		ResetBoard();
		return true;
	}
	else if (!m_board.FindKeyPiece("H11")) { // Computer captured human's key piece. Computer wins. Increment computer score.
		cout << "The computer has captured Garen's key piece! The computer has won this round!" << endl;
		m_CompWins++;
		cout << "The computer won " << m_CompWins << " rounds and Garen won " << m_HumanWins << " rounds. " << endl;
		ResetBoard();
		return true;
	}
	else if (m_board.GetBoard()[8][5] == "C11") { // Computer placed key piece on human's key square. Computer wins. Increment computer wins.
		cout << "The computer placed its key die on Garen's key square! The computer has won this round!" << endl;
		m_CompWins++;
		cout << "The computer won " << m_CompWins << " rounds and Garen won " << m_HumanWins << " rounds. " << endl;
		ResetBoard();
		return true;
	}
	else if (!m_board.FindKeyPiece("C11")) { // Human captured computer's key piece. Human wins. Increment human score.
		cout << "Garen has captured the computer's key piece! Garen has won this round!" << endl;
		m_HumanWins++;
		cout << "The computer won " << m_CompWins << " rounds and Garen won " << m_HumanWins << " rounds. " << endl;
		ResetBoard();
		return true;
	}
	return false;
}
/* *********************************************************************
Function Name: IsSavedGame
Purpose: To check if the player saved the game to a file
Parameters:
None
Returns: True if the user types 'y' or 'Y', False otherwise.
********************************************************************* */
bool Round::IsSavedGame() {
	string filename;
	char choice;
	do { // Ask the user if they want to save the game.
		cout << "Do you want to save the progress of this game right now? " << endl;
		cin >> choice;
		// If they say yes, validate the file name and have them keep inputting values until they enter a valid file name.
		if (toupper(choice) == 'Y') {
			ofstream out;
			do {
				cout << "Where should this game's progress be saved?" << endl;
				cin >> filename;
				out.open(filename);
				if (out.fail()) {
					cout << "Cannot write to " << filename << endl;
				}
			} while (out.fail());
			// Print the board as well as the statistics of the game.
			m_board.PrintBoard(out);
			out << "Number of rounds won by computer: " << m_CompWins << endl;
			out << "Number of rounds won by human player: " << m_HumanWins << endl;
			out << "Next Player: " << m_NextPlayer << endl;
			out << "Currently on round # " << m_numRounds << endl;
			out << "Currently on turn # " << m_turnNo << endl;
			out << "Currently Garen's turn # " << m_humanTurns << endl;
			out << "Currently Computer's turn # " << m_compTurns << endl;
			return true;
		}
	} while (toupper(choice) != 'Y' && toupper(choice) != 'N');
	return false; // If we get here then the user said no to saving the game and wants to continue.
}
// Getters and setters
int Round::GetHumanWins() const {
	return m_HumanWins;
}

void Round::SetHumanWins(int a_humanWins) {
	m_HumanWins = a_humanWins;
}
int Round::GetComputerWins() const {
	return m_CompWins;
}

void Round::SetComputerWins(int a_CompWins) {
	m_CompWins = a_CompWins;
}

int Round::GetRoundNo() const {
	return m_numRounds;
}

void Round::SetRoundNo(int a_roundNo) {
	m_numRounds = a_roundNo;
}

string Round::GetNextPlayer() const {
	return m_NextPlayer;
}

void Round::SetNextPlayer(string & a_NextPlayer) {
	m_NextPlayer = a_NextPlayer;
}
int Round::GetTurnNo() const {
	return m_turnNo;
}

void Round::SetTurnNo(int a_turn) {
	m_turnNo = a_turn;
}

int Round::GetCompTurn() const {
	return m_compTurns;
}

int Round::GetHumanTurn() const {
	return m_humanTurns;
}

void Round::SetCompTurn(int a_turn) {
	m_compTurns = a_turn;
}

void Round::SetHumanTurn(int a_turn) {
	m_humanTurns = a_turn;
}
/* *********************************************************************
Function Name: Rewind
Purpose: To set the file pointer to the beginning of the file
Parameters:
a_in, the file stream passed by reference that contains the saved game
********************************************************************* */
void Round::Rewind(ifstream & a_in) {
	// Clear the file flag and go to the beginning of the file.
	a_in.clear();
	a_in.seekg(0, ios::beg);
}
/* *********************************************************************
Function Name: RestoreGameData
Purpose: To restore the scores of the computer and human from the serialization file
Parameters:
a_in, the file stream passed by reference that contains the saved game
a_lines, an integer passed by reference referring to the number of lines in the file.
Local Variables:
lines, a vector of strings where the lines of the file will be added to.
Algorithm:
1) Read each line of the file and insert into the vector.
2) Read from the first line after the board to the end of the file. It will set the computer score, human score, next player, round number, turn number, human turn number, and computer turn number respectively. 
********************************************************************* */
void Round::RestoreGameData(ifstream & a_in, int & a_lines) {
	string newLine;
	vector<string> lines;
	// Read each line from the file.
	while (getline(a_in, newLine)) {
		lines.push_back(newLine);
	}
	// Note: this function is called after the board was printed. So we don't need to print the board again.
	// Use istringstream to parse the integer at the end of each line following the board for a particular statistic of the game.
	for (unsigned i = a_lines; i < lines.size(); i++) {
		cout << lines.at(i) << endl;
		istringstream iss(lines.at(i));
		string item1, item2, item3, item4, item5, item6, item7, item8;
		iss >> item1 >> item2 >> item3 >> item4 >> item5 >> item6 >> item7 >> item8;
		if (i == a_lines) {
			SetComputerWins(stoi(item7));
		}
		else if (i == 10) {
			SetHumanWins(stoi(item8));
		}
		else if (i == 11) {
			SetNextPlayer(item3);
		}
		else if (i == 12) {
			SetRoundNo(stoi(item5));
		}
		else if (i == 13){
			SetTurnNo(stoi(item5));
		}
		else if (i == 14) {
			SetHumanTurn(stoi(item5));
		}
		else {
			SetCompTurn(stoi(item5));
		}
	}
}
/* *********************************************************************
Function Name: ResetBoard
Purpose: To reset the board to the start state for the beginning of a new round
Parameters:
None
********************************************************************* */
void Round::ResetBoard() {
	// Reset the x and y coordinates and the top and right faces
	m_board.SetX(1);
	m_board.SetY(8);
	m_board.SetTop(1);
	m_board.SetRight(1);
	// Reset the turn numbers and the board.
	SetTurnNo(0);
	SetCompTurn(0);
	SetHumanTurn(0);
	m_board.DrawBoard();
}
/* *********************************************************************
Function Name: DetermineFirstPlayer
Purpose: To determine who goes first for a given round
Returns: Computer if it rolled the higher number, and Garen if he rolled the higher number.
Parameters:
None
********************************************************************* */
string Round::DetermineFirstPlayer() {
	int compRoll, humanRoll;
	// While the rolls are the same number, have the computer and human roll a die. The result will be random numbers.
	do {
		cout << "Rolling the dice....." << endl;
		system("pause");
		compRoll = (rand() % 6) + 1;
		cout << "The computer rolled " << compRoll << endl;
		humanRoll = (rand() % 6) + 1;
		cout << "Garen rolled " << humanRoll << endl;
		if (compRoll == humanRoll) {
			cout << "Both players rolled the same number. Repeating the process...." << endl;
			system("pause");
		}
	} while (compRoll == humanRoll);
	// If the computer had the greater roll, the computer should go first. Otherwise the human would go first.
	if (compRoll < humanRoll) {
		return "Garen";
	}
	else {
		return "Computer";
	}
}
/* *********************************************************************
Function Name: PlayGame
Purpose: To play a round.
Parameters:
None
Local Variables:
in, a filestream object to determine the file to load from.
Algorithm:
1) If this is the first round, ask if the user want to restore from a saved state. Otherwise, go to step 2.
2) If they say no or this is not the first round, start a new game, draw the initial board, and determine the first player.
3) Otherwise, determine the file to restore from. Check that the file exists, and restore the game from the saved state.
4) In either case, the players will alternte turns. Call GameOver() to check if the game is over, then call IsSavedGame() if the game is not over and a turn was made.
5) If any of the conditions for the game being over were met, return.
********************************************************************* */
void Round::PlayGame() {
	char load;
	string restore;
	string firstPlayer;
	int numLines = 0;
	// If this is the first round, ask if the user wants to load from a previously saved state.
	if (m_numRounds == 0) {
		cout << "Welcome to Duell in C++, assigned to OPL Fall 2016 taught by Amruth Kumar, played by Garen Loshkajian!" << endl;
		do { // Validate the user's choice
			cout << "Do you want to restore a Duell game from a saved file?" << endl;
			cin >> load;
		} while (toupper(load) != 'Y' && toupper(load) != 'N');
		if (toupper(load) == 'N') { 
			// If they say no, initialize the board and determine the first player
			cout << "Starting a new tournament!" << endl;
			m_board.DrawBoard();
			m_model.DisplayBoard(m_board);
			firstPlayer = DetermineFirstPlayer();
			m_numRounds++;
			// Declare the first player on the screen for the current round
			if (firstPlayer == "Garen") {
				cout << "Garen gets to move first in round # " << m_numRounds << "!" << endl;
			}
			else {
				cout << "The computer gets to move first in round # " << m_numRounds << "!" << endl;
			}
			// While the conditions for the game being over are not met, have the human and computer alternate turns. Ask to serialize after every turn. If they said yes, the program would terminate when the user gives the filename to save the game to.
			while (m_board.FindKeyPiece("C11") && m_board.FindKeyPiece("H11") && m_board.GetBoard()[1][5] != "H11" && m_board.GetBoard()[8][5] != "C11") {
				m_turnNo++;
				if (firstPlayer == "Garen") {
					m_NextPlayer = "Computer";
					m_humanTurns++;
					m_player = &m_human;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
					if (GameOver()) { // In all cases, if the conditions are met for the game being over, get out of the function.
						return;
					}
					cout << "Next player: " << m_NextPlayer << endl; // Next player would be first player in all cases after each player took a turn.
					if (IsSavedGame()) {
						exit(1);
					}
					m_compTurns++;
					m_player = &m_computer;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer); // Polymorphic behavior behind the scenes
				}
				else {
					m_NextPlayer = "Garen";
					m_compTurns++;
					m_player = &m_computer;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
					if (GameOver()) {
						return;
					}
					cout << "Next player: " << m_NextPlayer << endl;
					if (IsSavedGame()) {
						exit(1);
					}
					m_humanTurns++;
					m_player = &m_human;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
				}
				if (GameOver()) {
					return;
				}
				m_NextPlayer = firstPlayer;
				if (IsSavedGame()) {
					exit(1);
				}
			}
		}
		else {
			// If the user said yes to restoring from a previously saved state, Determine the file to restore from.
			// Validate the selection. Have the user keep entering the file name while it cannot be found.
			ifstream in;
			do {
				cout << "Which file do you want to restore your progress from?" << endl;
				cin >> restore;
				in.open(restore);
				if (in.fail()) {
					cout << "File not found. Try again." << endl;
				}
			} while (in.fail());
			// Read the board and the game data from the file and resume playing from the saved state. Algorithm is the same as before from that point on.
			m_board.ReadSerializationFile(in, numLines);
			m_model.DisplayBoard(m_board);
			Rewind(in);
			RestoreGameData(in, numLines);
			firstPlayer = m_NextPlayer;
			if (GameOver()) {
				return;
			}
			while (m_board.FindKeyPiece("C11") && m_board.FindKeyPiece("H11") && m_board.GetBoard()[1][5] != "H11" && m_board.GetBoard()[8][5] != "C11") {
				if (m_compTurns == m_humanTurns) {
					m_turnNo++;
				}
				if (firstPlayer == "Garen") {
					m_NextPlayer = "Computer";
					m_humanTurns++;
					m_player = &m_human;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
					if (GameOver()) {
						return;
					}
					if (IsSavedGame()) {
						exit(1);
					}
					if (m_compTurns == m_humanTurns) {
						m_turnNo++;
					}
					cout << "Next player: " << m_NextPlayer << endl;
					m_compTurns++;
					m_player = &m_computer;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
				}
				else {
					m_NextPlayer = "Garen";
					m_compTurns++;
					m_player = &m_computer;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
					if (GameOver()) {
						return;
					}
					cout << "Next player: " << m_NextPlayer << endl;
					if (IsSavedGame()) {
						exit(1);
					}
					if (m_compTurns == m_humanTurns) {
						m_turnNo++;
					}
					m_humanTurns++;
					m_player = &m_human;
					m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
				}
				if (GameOver()) {
					return;
				}
				m_NextPlayer = firstPlayer;
				if (IsSavedGame()) {
					exit(1);
				}
			}
		}
	}
	else { // If this is not the first round, the algorithm is the same as before but for a new round. We don't ask to reload from a saved state in this case.
		cout << "Starting a new round!" << endl;
		cout << m_HumanWins << " " << m_CompWins << endl;
		m_model.DisplayBoard(m_board);
		firstPlayer = DetermineFirstPlayer();
		m_numRounds++;
		if (firstPlayer == "Garen") {
			cout << "Garen gets to move first in round # " << m_numRounds << "!" << endl;
		}
		else {
			cout << "The computer gets to move first in round # " << m_numRounds << "!" << endl;
		}
		while (m_board.FindKeyPiece("C11") && m_board.FindKeyPiece("H11") && m_board.GetBoard()[1][5] != "H11" && m_board.GetBoard()[8][5] != "C11") {
			m_turnNo++;
			if (firstPlayer == "Garen") {
				m_NextPlayer = "Computer";
				m_humanTurns++;
				m_player = &m_human;
				m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
				if (GameOver()) {
					return;
				}
				cout << "Next player: " << m_NextPlayer << endl;
				if (IsSavedGame()) {
					exit(1);
				}
				m_compTurns++;
				m_player = &m_computer;
				m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
			}
			else {
				m_NextPlayer = "Garen";
				m_compTurns++;
				m_player = &m_computer;
				m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
				if (GameOver()) {
					return;
				}
				cout << "Next player: " << m_NextPlayer << endl;
				if (IsSavedGame()) {
					exit(1);
				}
				m_humanTurns++;
				m_player = &m_human;
				m_player->Play(m_board, m_turnNo, firstPlayer, m_NextPlayer);
			}
			if (GameOver()) {
				return;
			}
			m_NextPlayer = firstPlayer;
			if (IsSavedGame()) {
				exit(1);
			}
		}
	}
}
Round::~Round()
{
}