#include <iostream>
#include "Human.h"
#include "Player.h"
#include "Board.h"
#include "BoardView.h"
#include "Computer.h"
#include <string>
#include <cmath>
using namespace std;

Human::Human()
{
	m_direction = "";
	m_NextRow = 1;
	m_NextCol = 1;
	m_frontMove = 0;
	m_lateralMove = 0;
	m_secondDirection = "";
}
/* Function Name : Play
Purpose : To allow the human player to make a move.
Parameters :
a_board, the current board passed by reference.It holds the all the computer and human dice.
a_turn, an integer. It refers to the current turn number
a_first, a string. It represent the player who goes first each turn.
a_player, a string. It represents the computer player.
Algorithm:
1) Print the turn number, the current player, and the next player.
2) Call the GetInput() function to get input from the human player.
Assistance Received : none
********************************************************************* */
void Human::Play(Board & a_board, int a_turn, string a_first, string a_player) {
	// Get the input from the user as well as the player who went first each turn.
	if (a_first == "Garen") {
		cout << "Turn # " << a_turn << " for " << a_first << ": (" << a_player << " goes next) " << endl;
	}
	else {
		cout << "Turn # " << a_turn << " for " << a_player << ": (" << a_first << " goes next) " << endl;
	}
	// Get input from the user.
	GetInput(a_board, a_turn);
}
/* *********************************************************************
Function Name: GetInput
Purpose: To get the input from the human player
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_turn, an integer. It refers to the current turn number
Local Variables:
currentBoard, a pointer to a pointer to an array of strings (2D array containing the board)
Algorithm:
1) Access the board using the getter function of a_board.
2) Check that the user did not make ten mistakes with their input. If they did, return -> they forfeited their turn.
3) Ask the user if they want help. If they say yes (y), display the strategy on the screen. If the user took the computer's suggestion, update the board with that recommended move
4) Otherwise ask the user for start coordinates
5) Validate start coordinates. Report error if the coordinates are invalid or don't correspond to a human die
6) Ask the user for end coordinates. Validate these end coordinates. Report error if the coordinates are out of range or they don't correspond to an empty square or an opponent's dice.
7) If both x coordinates and both y coordinates are not equal then there is a 90 degree turn. Have the user specify frontally or laterally as the first direction.
8) Check the path of the die that no other dice are in the way. Report error if the path is occupied.
9) Update the board and the faces of the dice by calling a_board::UpdateBoard, then Die::Rotate.
Assistance Received: none
********************************************************************* */
void Human::GetInput(Board & a_board, int a_turn) {
	// Get the current board
	string ** currentBoard = a_board.GetBoard();
	// to check for occupied squares
	bool occupied = false;
	// To determine the top of the chosen die
	int top = 0;
	// To count invalid inputs
	int invalid = 0;
	// To determine whether to ask for help
	char help;
	do {
		// If the human made 10 wrong inputs then his turn is over.
		if (invalid == 10) {
			cout << "Garen has forfeited this turn since he made too many incorrect inputs!" << endl;
			return;
		}
		// If the user typed Y then he is asking the computer for the recommended strategy. Display the recommendation on the screen.
		do {
			cout << "Do you want to ask the computer for help?" << endl;
			cin >> help;
			if (toupper(help) == 'Y') { // Ask if the user wants to take the computer's suggestion. If so, it would update the board
				// using the recommended move and then end the human's turn
				system("pause");
				if (m_comp.HelpHuman(a_board)) {
					return;
				}
			}
		} while (toupper(help) != 'Y' && toupper(help) != 'N');
		occupied = false;
		// Ask the user for the start coordinates of the die
		cout << "Garen, which row and column do you want to search for the die to move?" << endl;
		cin >> m_NextRow >> m_NextCol;
		// Report error if not numeric
		if (cin.fail()) {
			cout << "Must enter numeric values for the starting coordinates. Try again." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			invalid++;
			continue;
		}
		// If the coordinates are not in the required range then report error that the coordinates are out of bounds of the array and continue.
		if (m_NextRow < 1 || m_NextRow > 8) {
			cout << "Row out of bounds. Try again." << endl;
			invalid++;
			continue;
		}
		if (m_NextCol < 1 || m_NextCol > 9) {
			cout << "Column out of bounds. Try again." << endl;
			invalid++;
			continue;
		}
		// Report error if the user does not pick their own dice.
		if (toupper(currentBoard[9 - m_NextRow][m_NextCol][0]) != 'H') {
			cout << "You can only move your own dice. Try again." << endl;
			invalid++;
			continue;
		}
		// Get the top number of the die. Must convert ASCII character to integer
		top = (currentBoard[9 - m_NextRow][m_NextCol][1] - '0') % 48;
		int count = 0;
		// Ask the user for the end coordinates of the roll. Must subtract the row variable by 9 since y coordinates start at the bottom of the screen
		cout << "Ok. And to which row and column do you want to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ")?" << endl;
		cin >> m_DestRow >> m_DestCol;
		// Report error if the destination coordinates are out of bounds in the array or not numeric and continue.
		if (cin.fail()) {
			cout << "Must enter numeric values for destination. Try again." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			invalid++;
			continue;
		}
		if (m_DestRow < 1 || m_DestRow > 8) {
			cout << "Row out of bounds. Try again." << endl;
			invalid++;
			continue;
		}
		if (m_DestCol < 1 || m_DestCol > 9) {
			cout << "Column out of bounds. Try again." << endl;
			invalid++;
			continue;
		}
		// Report error if the user attempts to capture his own dice.
		if (currentBoard[9 - m_DestRow][m_DestCol] != "0" && toupper(currentBoard[9 - m_DestRow][m_DestCol][0]) != 'C') {
			cout << "Either you are not moving the die or you chose an invalid square. You can only move your own dice onto empty spaces or your opponent's dice. Try again." << endl;
			invalid++;
			continue;
		}
		// Report error if the number of spaces covered is not equal to the number on the top of the die
		// Must use absolute value because the user can move their dice in the following directions.
		// Up, down, left, and right
		if (abs(abs(m_DestRow - m_NextRow) + abs(m_DestCol - m_NextCol)) != abs(top)) {
			cout << "You can only move as many spaces as the number on the top of your dice. Try again." << endl;
			invalid++;
			continue;
		}
		// Empty the string containing the movement of the die if it was not empty to get the next input from the user
		if (!m_direction.empty()) {
			m_direction = "";
		}
		cin.ignore(INT_MAX, '\n');
		// If the start and end x and the start and end y are BOTH not equal ask for the first direction of the die
		if (abs(m_NextRow) != abs(m_DestRow) && abs(m_NextCol) != abs(m_DestCol)) {
			cout << "There is a 90 degree turn. Which direction do you want to move " << currentBoard[9 - m_NextRow][m_NextCol] << " at (" << m_NextRow << " , " << m_NextCol << ") first? Frontally or laterally?" << endl;
			while (m_direction != "frontally" && m_direction != "laterally") {
				getline(cin, m_direction);
				if (m_direction != "frontally" && m_direction != "laterally") {
					cout << "Can only enter one of the following words: frontally or laterally all lowercase. Try again." << endl;
					cout << "Which direction do you want to move " << currentBoard[9 - m_NextRow][m_NextCol] << " at (" << m_NextRow << " , " << m_NextCol << ") first (frontal or lateral, with only one 90 degree turn)?" << endl;
				}
			}
		}
		else if (abs(m_NextRow) != abs(m_DestRow)) { // Otherwise if the rows are not equal then the die is moving frontally
			m_direction = "frontally";
		}
		else if (abs(m_NextCol) != abs(m_DestCol)) { // If the columns are not equal then the die is moving laterally
			m_direction = "laterally";
		}
		// Check the frontal path before the lateral path if there is a 90 degree turn and frontally is selected as the first direction.
		// Otherwise if laterally is selected as the first direction check the lateral path first.
		if (m_direction == "frontally" && abs(m_NextRow) != abs(m_DestRow) && abs(m_NextCol) != abs(m_DestCol)) {
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i <= m_DestRow; i++) {
					if (currentBoard[9 - i][m_NextCol] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i >= m_DestRow; i--) {
					if (currentBoard[9 - i][m_NextCol] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i < m_DestCol; i++) {
					if (currentBoard[9 - m_DestRow][i] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			else {
				for (int i = m_NextCol - 1; i > m_DestCol; i--) {
					if (currentBoard[9 - m_DestRow][i] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			if (occupied) {
				cout << "Cannot move through other dice. Try again." << endl;
				invalid++;
				continue;
			}
		}
		else if (m_direction == "laterally" && abs(m_NextRow) != abs(m_DestRow) && abs(m_NextCol) != abs(m_DestCol)){
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i <= m_DestCol; i++) {
					if (currentBoard[9 - m_NextRow][i] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			else {
				for (int i = m_NextCol - 1; i >= m_DestCol; i--) {
					if (currentBoard[9 - m_NextRow][i] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i < m_DestRow; i++) {
					if (currentBoard[9 - i][m_DestCol] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i > m_DestRow; i--) {
					if (currentBoard[9 - i][m_NextCol] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			if (occupied) {
				cout << "Cannot move through other dice. Try again." << endl;
				invalid++;
				continue;
			}
		}
		// If there is no 90 degree turn then check the frontal path or the lateral path depending on the coordinates given.
		// In all cases, report error if there is at least one square on the path to the destination with a die on it, except at the destination coordinates.
		else if (m_direction == "frontally") {
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i < m_DestRow; i++) {
					if (currentBoard[9 - i][m_NextCol] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i > m_DestRow; i--) {
					if (currentBoard[9 - i][m_NextCol] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			if (occupied) {
				cout << "Cannot move through other dice. Try again. " << endl;
				invalid++;
				continue;
			}
		}
		else {
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i < m_DestCol; i++) {
					if (currentBoard[9 - m_NextRow][i] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			else {
				for (int i = m_NextCol - 1; i > m_DestCol; i--) {
					if (currentBoard[9 - m_NextRow][i] != "0") {
						occupied = true;
					}
					count++;
				}
			}
			if (occupied) {
				cout << "Cannot move through other dice. Try again. " << endl;
				invalid++;
				continue;
			}
		}
	} while (cin.fail() || occupied || m_NextRow < 1 || m_NextRow > 8 || m_NextCol < 1 || m_NextCol > 9 || abs(abs(m_DestRow - m_NextRow) + abs(m_DestCol - m_NextCol)) != abs(top) || m_DestRow < 1 || m_DestRow > 8 || m_DestCol < 1 || m_DestCol > 9 || currentBoard[9 - m_DestRow][m_DestCol] != "0" && toupper(currentBoard[9 - m_DestRow][m_DestCol][0]) != 'C');
	// Number of spaces to move frontally
	m_frontMove = abs(m_DestRow - m_NextRow);
	// Number of spaces to move laterally
	m_lateralMove = abs(m_DestCol - m_NextCol);
	// Print out the turn number and the movement of the die on the screen.
	cout << "In turn #" << a_turn << ", ";
	if (m_direction == "frontally") {
		m_secondDirection = "laterally";
		cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_frontMove << " and laterally by " << m_lateralMove << " ";
	}
	else {
		m_secondDirection = "frontally";
		cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_lateralMove << " and frontally by " << m_frontMove << " ";
	}
	cout << "to square (" << m_DestRow << ", " << m_DestCol << ")! ";
	// Update the board and the faces of the die after the roll
	string currentDie = currentBoard[9 - m_NextRow][m_NextCol];
	a_board.UpdateBoard(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, currentDie, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
	// Display the updated board on the screen
	m_model.DisplayBoard(a_board);
}