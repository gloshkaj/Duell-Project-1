#include "Computer.h"
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

Computer::Computer()
{
	// Initialize all variables
	m_direction = "";
	m_NextRow = 1;
	m_NextCol = 1;
	m_frontMove = 0;
	m_lateralMove = 0;
	m_secondDirection = "";
	srand(time(0));
}
/* Function Name : TakeSuggestion
Purpose : To allow the human player to choose whether to automatically make the move the computer suggested.
Parameters : None
Returns: True if the user types 'Y' or 'y' for whether they want to use the move, false otherwise
********************************************************************* */
bool Computer::TakeSuggestion() {
	char choice;
	// Validate input from the user. If the user enters yes, then they took the help from the computer, otherwise they would explicitly enter coordinates.
	do {
		cout << "Garen, do you want to use this move?" << endl;
		cin >> choice;
		if (toupper(choice) == 'Y') {
			return true;
		}
	} while (toupper(choice) != 'Y' && toupper(choice) != 'N');
	return false;
}
/* *********************************************************************
Function Name: GetAllCoordsInBlockingPath
Purpose: To get all the blocking paths and all the coordinates in the blocking paths
Parameters:
a_coords, the array of coordinate pairs passed by reference. It holds all the empty squares in the blocking paths.
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_count, an integer passed by reference. It refers to the number of empty squares in the blocking paths.
Algorithm:
1) Get the frontal and lateral distance.
2) If they both are not zero, then check if the paths are valid. Populate the coordinate array with all empty squares in all valid paths.
3) If frontal is zero, check the lateral path, and vice versa. Populate the path with all empty squares.
4) Set the reference parameter, a_count, equal to the number of empty squares found so far for the next call of the function.
Assistance Received: none
********************************************************************* */
void Computer::GetAllCoordsInBlockingPath(pair<int, int> a_coords[], string ** a_board, int & a_count) {
	m_frontMove = abs(m_DestRow - m_NextRow);
	m_lateralMove = abs(m_DestCol - m_NextCol);
	// Get frontal and lateral movement. If they are both not zero, then this must have a 90 degree turn.
	int count;
	if (m_frontMove != 0 && m_lateralMove != 0) {
		if (IsValidFrontLatPath(a_board) && IsValidLatFrontPath(a_board)) { // If both routes are valid, get all the empty coordinates in the path between start and end
			count = a_count;
			bool occupied = false;
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i <= m_DestRow; i++) {
					a_coords[count] = make_pair(i, m_NextCol);
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i >= m_DestRow; i--) {
					a_coords[count] = make_pair(i, m_NextCol);
					count++;
				}
			}
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i < m_DestCol; i++) {
					a_coords[count] = make_pair(m_DestRow, i);
					count++;
				}
			}
			// Check the frontal path before the lateral path if there is a 90 degree turn and frontally is selected as the first direction.
			// Otherwise if laterally is selected as the first direction check the lateral path first.
			else {
				for (int i = m_NextCol - 1; i > m_DestCol; i--) {
					a_coords[count] = make_pair(m_DestRow, i);
					count++;
				}
			}
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i <= m_DestCol; i++) {
					a_coords[count] = make_pair(m_NextRow, i);
					count++;
				}
			}
			else {
				for (int i = m_NextCol - 1; i >= m_DestCol; i--) {
					a_coords[count] = make_pair(m_NextRow, i);
					count++;
				}
			}
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i < m_DestRow; i++) {
					a_coords[count] = make_pair(i, m_DestCol);
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i > m_DestRow; i--) {
					a_coords[count] = make_pair(i, m_DestCol);
					count++;
				}
			}
		}
		else if (IsValidFrontLatPath(a_board)) { // Then only the frontal/lateral path is valid. Algorithm is the same as above.
			count = a_count;
			bool occupied = false;
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i <= m_DestRow; i++) {
					a_coords[count] = make_pair(i, m_NextCol);
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i >= m_DestRow; i--) {
					a_coords[count] = make_pair(i, m_NextCol);
					count++;
				}
			}
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i < m_DestCol; i++) {
					a_coords[count] = make_pair(m_DestRow, i);
					count++;
				}
			}
			// Check the frontal path before the lateral path if there is a 90 degree turn and frontally is selected as the first direction.
			// Otherwise if laterally is selected as the first direction check the lateral path first.
			else {
				for (int i = m_NextCol - 1; i > m_DestCol; i--) {
					a_coords[count] = make_pair(m_DestRow, i);
					count++;
				}
			}
		}
		else if (IsValidLatFrontPath(a_board)) { // Then only lateral/frontal path is valid. Use the same algorithm as above.
			count = a_count;
			bool occupied = false;
			if (m_NextCol < m_DestCol) {
				for (int i = m_NextCol + 1; i <= m_DestCol; i++) {
					a_coords[count] = make_pair(m_NextRow, i);
					count++;
				}
			}
			else {
				for (int i = m_NextCol - 1; i >= m_DestCol; i--) {
					a_coords[count] = make_pair(m_NextRow, i);
					count++;
				}
			}
			if (m_NextRow < m_DestRow) {
				for (int i = m_NextRow + 1; i < m_DestRow; i++) {
					a_coords[count] = make_pair(i, m_DestCol);
					count++;
				}
			}
			else {
				for (int i = m_NextRow - 1; i > m_DestRow; i--) {
					a_coords[count] = make_pair(i, m_DestCol);
					count++;
				}
			}
		}
	}
	else if (m_lateralMove != 0) {
		// This must be a lateral move. Get all coordinates in the row between start and end.
		count = a_count;
		bool occupied = false;
		if (m_NextCol < m_DestCol) {
			for (int i = m_NextCol + 1; i < m_DestCol; i++) {
				a_coords[count] = make_pair(m_NextRow, i);
				count++;
			}
		}
		else {
			for (int i = m_NextCol - 1; i > m_DestCol; i--) {
				a_coords[count] = make_pair(m_NextRow, i);
				count++;
			}
		}
	}
	else if (m_frontMove != 0) {
		// This must be a frontal move. Get coordinates of all empty squares between start and end in same column.
		count = a_count;
		bool occupied = false;
		// If there is no 90 degree turn then check the frontal path or the lateral path depending on the coordinates given.
		// In all cases, report error if there is at least one square on the path to the destination with a die on it, except at the destination coordinates.
		if (m_NextRow < m_DestRow) {
			for (int i = m_NextRow + 1; i < m_DestRow; i++) {
				a_coords[count] = make_pair(i, m_NextCol);
				count++;
			}
		}
		else {
			for (int i = m_NextRow - 1; i > m_DestRow; i--) {
				a_coords[count] = make_pair(i, m_NextCol);
				count++;
			}
		}
	}
	// Must set the reference parameter equal to use it to make the blocking move.
	a_count = count;
}
/* *********************************************************************
Function Name: MakeBlockingMove
Purpose: To perform the move to block the human from winning.
Parameters:
a_game, the board object passed by reference.
a_coords, the array of coordinate pairs passed by reference. It holds all the empty squares in the blocking paths.
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_count, an integer passed by reference. It refers to the number of empty squares in the blocking paths.
a_player, the character referring to whether the computer or the human is playing.
Returns: False if no blocking path was found or no die can arrive in the blocking path, True otherwise.
Algorithm:
1) For each die on the board, get the distance to the blocking path.
2) If it can move into the blocking path and it is not the key die, make the move if the computer is playing, and suggest the move if the human is playing.
Assistance Received: none
********************************************************************* */
bool Computer::MakeBlockingMove(Board & a_game, pair<int, int> a_coords[], string ** a_board, int & a_count, char a_player) {
	int allowedDist;
	int dist;
	string DieToRoll = "";
	string player = "";
	if (a_count == 0) { // If the only winning move was a die with a 1 on top adjacent to the enemy key die, then there are no paths, so just move the key piece at random later on.
		return false;
	}
	// For each coordinate in the blocking paths, and for each die on the board, check that it can get to the path to block.
	for (int i = 0; i < a_count; i++) {
		for (int j = 8; j >= 1; j--) {
			for (int k = 9; k >= 1; k--) {
				if (a_board[9 - j][k][0] == a_player) {
					int col = k;
					int row = j;
					allowedDist = (a_board[9 - j][k][1] - '0') % 48;
					dist = abs(row - a_coords[i].first) + abs(col - a_coords[i].second);
					// If this is not the key die and the die can get to the path, check if the path is valid
					if (dist == allowedDist) {
						m_NextCol = col;
						m_NextRow = row;
						m_DestRow = a_coords[i].first;
						m_DestCol = a_coords[i].second;
						DieToRoll = a_board[9 - j][k];
						if (!IsValidPath(a_board)) {
							// Invalid path. Move on.
							continue;
						}
						if (a_player == 'C') {
							player = "Computer";
						}
						else {
							player = "Human";
						}
						// If the computer is playing, make the move, if the human is playing, then the human is asking for help.
						if (player == "Computer") {
							cout << "The computer chose to move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") to block!" << endl;
							if (m_direction == "frontally") {
								cout << "It moved it frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ")! ";
							}
							else {
								cout << "It moved it laterally by " << m_lateralMove << " and frontally by " << m_frontMove << " to square (" << m_DestRow << ", " << m_DestCol << ")! ";
							}
							cout << "Now Garen's path to win the game is blocked! ";
							// Update and display the board
							a_game.UpdateComputerMove(a_board, m_frontMove, m_lateralMove, m_direction, m_secondDirection, DieToRoll, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
							m_model.DisplayBoard(a_game);
						}
						else {
							cout << "Move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") to block!" << endl;
							if (m_direction == "frontally") {
								cout << "Move it frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ")! ";
							}
							else {
								cout << "Move it laterally by " << m_lateralMove << " and frontally by " << m_frontMove << " to square (" << m_DestRow << ", " << m_DestCol << ")! ";
							}
							cout << "That will block the computer's path to win the game! ";
						}
						return true;
					}
				}
			}
		}
	}
	return false; // If we get here then there are no dice the computer can move besides its key die to block.
}
/* *********************************************************************
Function Name: IsValidPath
Purpose: To check if a path is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
Algorithm:
1) Get the frontal and lateral distance.
2) If they both are not zero, then check if the paths are valid. If there are dice in the way, return false.
3) If frontal is zero, check the lateral path, and vice versa. If there are dice in the way, return false.
Assistance Received: none
********************************************************************* */
bool Computer::IsValidPath(string ** a_board) {
	m_frontMove = abs(m_DestRow - m_NextRow);
	m_lateralMove = abs(m_DestCol - m_NextCol);
	// Get frontal and lateral movement
	// If they are both not zero and both routes are blocked, then the path is not valid
	if (m_frontMove != 0 && m_lateralMove != 0) {
		if (!IsValidFrontLatPath(a_board) && !IsValidLatFrontPath(a_board)) {
			return false;
		}
		// Otherwise there exists a valid path of the two. Set the directions accordingly.
		else if (!IsValidFrontLatPath(a_board)) {
			m_direction = "laterally";
			m_secondDirection = "frontally";
			return true;
		}
		else {
			m_direction = "frontally";
			m_secondDirection = "laterally";
			return true;
		}
	}
	else if (m_lateralMove != 0) { 
		// If there is only lateral movement check if the path is valid. Same for only frontal movement.
		if (!IsValidLatPath(a_board)) {
			return false;
		}
		m_direction = "laterally";
		m_secondDirection = "frontally";
		return true;
	}
	else if (m_frontMove != 0) {
		if (!IsValidFrontPath(a_board)) {
			return false;
		}
		m_direction = "frontally";
		m_secondDirection = "laterally";
		return true;
	}
	return false;
}
/* *********************************************************************
Function Name: IsValidFrontPath
Purpose: To check if a frontal path is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
Assistance Received: none
********************************************************************* */
bool Computer::IsValidFrontPath(string ** a_board) {
	int count = 0;
	bool occupied = false;
	// In all cases, the path is invalid if there is at least one square on the path to the destination with a die on it, except at the destination coordinates.
	if (m_NextRow < m_DestRow) {
		for (int i = m_NextRow + 1; i < m_DestRow; i++) {
			if (a_board[9 - i][m_NextCol] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	else {
		for (int i = m_NextRow - 1; i > m_DestRow; i--) {
			if (a_board[9 - i][m_NextCol] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	if (occupied) {
		return false;
	}
	return true;
}
/* *********************************************************************
Function Name: IsValidFrontLatPath
Purpose: To check if a frontal/lateral path is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
Assistance Received: none
********************************************************************* */
bool Computer::IsValidFrontLatPath(string ** a_board) {
	int count = 0;
	bool occupied = false;
	if (m_NextRow < m_DestRow) {
		for (int i = m_NextRow + 1; i <= m_DestRow; i++) {
			if (a_board[9 - i][m_NextCol] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	else {
		for (int i = m_NextRow - 1; i >= m_DestRow; i--) {
			if (a_board[9 - i][m_NextCol] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	if (m_NextCol < m_DestCol) {
		for (int i = m_NextCol + 1; i < m_DestCol; i++) {
			if (a_board[9 - m_DestRow][i] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	// Check the frontal path before the lateral path
	else {
		for (int i = m_NextCol - 1; i > m_DestCol; i--) {
			if (a_board[9 - m_DestRow][i] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	if (occupied) {
		return false;
	}
	return true;
}
/* *********************************************************************
Function Name: IsValidLatFrontPath
Purpose: To check if a lateral/frontal path is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
Assistance Received: none
********************************************************************* */
bool Computer::IsValidLatFrontPath(string ** a_board) {
	// Otherwise if laterally is selected as the first direction check the lateral path first.
	int count = 0;
	bool occupied = false;
	if (m_NextCol < m_DestCol) {
		for (int i = m_NextCol + 1; i <= m_DestCol; i++) {
			if (a_board[9 - m_NextRow][i] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	else {
		for (int i = m_NextCol - 1; i >= m_DestCol; i--) {
			if (a_board[9 - m_NextRow][i] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	if (m_NextRow < m_DestRow) {
		for (int i = m_NextRow + 1; i < m_DestRow; i++) {
			if (a_board[9 - i][m_DestCol] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	else {
		for (int i = m_NextRow - 1; i > m_DestRow; i--) {
			if (a_board[9 - i][m_DestCol] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	if (occupied) {
		return false;
	}
	return true;
}
/* *********************************************************************
Function Name: IsValidLatPath
Purpose: To check if a lateral path is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
Assistance Received: none
********************************************************************* */
bool Computer::IsValidLatPath(string ** a_board) {
	int count = 0;
	bool occupied = false;
	// Check the lateral path. If any dice invade it the path is invalid.
	if (m_NextCol < m_DestCol) {
		for (int i = m_NextCol + 1; i < m_DestCol; i++) {
			if (a_board[9 - m_NextRow][i] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	else {
		for (int i = m_NextCol - 1; i > m_DestCol; i--) {
			if (a_board[9 - m_NextRow][i] != "0") {
				occupied = true;
			}
			count++;
		}
	}
	if (occupied) { // In all cases if we find an occupied die, the path must be invalid.
		return false;
	}
	return true;
}
/* *********************************************************************
Function Name: IsValidDestinationSquare
Purpose: To check if the ending square of a computer's move is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_top, an integer. It refers to the number at the top of the die before the move.
Assistance Received: none
**********************************************************************/
bool Computer::IsValidDestinationSquare(string ** a_board, int a_top) {
	// Report error if the user attempts to capture his own dice or tries to move out of bounds of the board.
	if (m_DestRow < 1 || m_DestRow > 8 || m_DestCol < 1 || m_DestCol > 9) {
		return false;
	}	
	if (toupper(a_board[9 - m_DestRow][m_DestCol][0]) == 'C') {
		return false;
	}
	// Report error if the number of spaces covered is not equal to the number on the top of the die
	// Must use absolute value because the user can move their dice in the following directions.
	// Up, down, left, and right
	if (abs(abs(m_DestRow - m_NextRow) + abs(m_DestCol - m_NextCol)) != abs(a_top)) {
		return false;
	}
	return true;
}
/* *********************************************************************
Function Name: IsValidHumanDestinationSquare
Purpose: To check if the ending square of a user's move is valid
Returns: True if valid, false if not.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_top, an integer. It refers to the number at the top of the die before the move.
Assistance Received: none
**********************************************************************/
bool Computer::IsValidHumanDestinationSquare(string ** a_board, int a_top) {
	// Report error if the user attempts to capture his own dice or tries to move out of bounds of the board.
	if (m_DestRow < 1 || m_DestRow > 8 || m_DestCol < 1 || m_DestCol > 9) {
		return false;
	}
	if (toupper(a_board[9 - m_DestRow][m_DestCol][0]) == 'H') {
		return false;
	}
	// Report error if the number of spaces covered is not equal to the number on the top of the die
	// Must use absolute value because the user can move their dice in the following directions.
	// Up, down, left, and right
	if (abs(abs(m_DestRow - m_NextRow) + abs(m_DestCol - m_NextCol)) != abs(a_top)) {
		return false;
	}
	return true;
}
/* *********************************************************************
Function Name: Play
Purpose: To allow the computer player to make a move
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_turn, an integer. It refers to the current turn number
a_first, a string passed by value to get the first player
a_player, a string passed by value to get the current player
Local Variables:
currentBoard, a pointer to a pointer to an array of strings (2D array containing the board)
coords, a array of (x, y) pairs containing all dice in a blocking path on the board
Algorithm:
1) Access the board using the getter function of a_board.
2) Get the row and column of the human and computer key dice.
3) For each space on the board, check if there is a die that will lead to a win. If there is, use that move (call UpdateComputerDie then RotateComputerDie)
4) For each human die on the board, see if it can get to the computer key die right away. If it can, determine all possible paths that be invaded.
5) If none of them result in a blocking move or if the key die is adjacent to a die with 1 on the top, move the key piece. Otherwise, use the piece that blocks the human from winning the game. This prevents the human from winning even if they had many moves to win though does not fit with certain cases.
6) If 3, 4, and 5 don't result in a successful move made by the computer, Move the die which is the minimum of the distance to the key piece minus the number at the top of the die before the move.
7) If 6 is what results in a reasonable move, choose the directions at random until the computer chooses a valid path. If the computer made 10 incorrect paths it forfeits its turn.
8) Update the board and the faces of the dice by calling a_board::UpdateComputerDie, then Die::RotateComputerDie.
Assistance Received: none
Notes: The computer's strategy is by far the hardest part of the project.
However, we decided to use the following strategy:
If the computer does not have a direct move to the human's key die or it cannot block it should move the die that:
Can be moved the most squares (has the highest number on top before the move) towards the human's key piece
and that would be the closest to the key piece after its turn has ended. The movement is chosen at random.
********************************************************************* */
void Computer::Play(Board & a_board, int a_turn, string a_first, string a_player) {
	string ** currentBoard = a_board.GetBoard();
	string DieToRoll = "";
	// Get the row and column of the key dice.
	int rowOfHumanKeyPiece = a_board.FindRowKeyPiece();
	int colOfHumanKeyPiece = a_board.FindColKeyPiece();
	int rowOfCompKeyPiece = a_board.FindRowCompKeyPiece();
	int colOfCompKeyPiece = a_board.FindColCompKeyPiece();
	bool isOnKeySquare = false;
	int min = 25;
	int dist, allowedDist, distToOtherKeySquare;
	int currentRow;
	int currentCol;
	int comp = 0;
	int human = 0;
	int humanRow, humanCol;
	int distToCompKeyDie;
	int humanAllowedDist;
	cout << "Turn # " << a_turn << " for computer: " << endl;
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 9; j++) {
			currentRow = i;
			currentCol = j;
			if (currentBoard[9 - i][j][0] == 'C') {
				// Get the distance between each computer dice and the human's key die
				dist = abs(currentRow - rowOfHumanKeyPiece) + abs(currentCol - colOfHumanKeyPiece);
				distToOtherKeySquare = abs(currentRow - 1) + abs(currentCol - 5);
				allowedDist = (currentBoard[9 - i][j][1] - '0') % 48;
				isOnKeySquare = (distToOtherKeySquare == allowedDist && currentBoard[9 - i][j][1] == '1' && currentBoard[9-i][j][1] == '1');
				if (dist == allowedDist || isOnKeySquare) { // If the distance to the key piece is equal to the allowed distance and the path is not blocked, then this is a move that captures the key piece
					m_NextRow = currentRow;
					m_NextCol = currentCol;
					DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
					if (dist == allowedDist) {
						m_DestCol = colOfHumanKeyPiece;
						m_DestRow = rowOfHumanKeyPiece;
					}
					else if (isOnKeySquare) {
						m_DestCol = 5;
						m_DestRow = 1;
					}
					if (!IsValidPath(currentBoard)) {
						// Invalid path. Computer does not win. Move on.
						continue;
					}
					cout << "The computer chose to move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") to finish the game!" << endl;
					if (m_direction == "frontally") {
						cout << "It moved it frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ") to win the round! ";
					}
					else {
						cout << "It moved it laterally by " << m_lateralMove << " and frontally by " << m_frontMove << " to square (" << m_DestRow << ", " << m_DestCol << ") to win the round! ";
					}
					// Update and display the board
					a_board.UpdateComputerMove(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, DieToRoll, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
					m_model.DisplayBoard(a_board);
					return;
				}
				// If this gets the computer close to the key piece, but not exactly at the key piece, update the minimum distance
				if (dist - allowedDist < min) {
					min = dist - allowedDist;
				}
			}
		}
	}
	int count = 0;
	// Have an array of 200 (x, y) pairs in case there are multiple blocking paths
	pair<int, int> coords[200];
	int blocking = 0;
	for (int i = 8; i >= 1; i--) {
		for (int j = 9; j >= 1; j--) {
			humanCol = j;
			humanRow = i;
			if (currentBoard[9 - i][j][0] == 'H') {
				distToCompKeyDie = abs(humanRow - rowOfCompKeyPiece) + abs(humanCol - colOfCompKeyPiece);
				humanAllowedDist = (currentBoard[9 - i][j][1] - '0') % 48;
				// Check if the computer can block.
				if (humanAllowedDist == distToCompKeyDie) {
					// If it can the computer should move a die that will prevent the human from using the winning move
					m_NextRow = humanRow;
					m_NextCol = humanCol;
					m_DestRow = rowOfCompKeyPiece;
					m_DestCol = colOfCompKeyPiece;
					if (!IsValidPath(currentBoard)) {
						// Invalid path. Move on.
						continue;
					}
					blocking++;
					// Increment number of blocking moves available.
					if (distToCompKeyDie < 2) { 
						// If the winning move is only one square away, move on
						continue;
					}
					// Get all the paths that the human can take to win and the coordinates in those paths
					GetAllCoordsInBlockingPath(coords, currentBoard, count);
				}
			}
		}
	}
	if (MakeBlockingMove(a_board, coords, currentBoard, count, 'C')) {
		// If a successful blocking move was made, there is nothing left to do.
		return;
	}
	else if (blocking >= 1) {
		// Otherwise if there were at least one blocking move, move the key piece in a random direction by one while the destination is not the player's own dice.
		m_NextRow = rowOfCompKeyPiece;
		m_NextCol = colOfCompKeyPiece;
		DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
		cout << "The computer chose to move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") to attempt to block Garen from winning!" << endl;
		do {
			int flag = rand() % 4;
			if (flag == 0) {
				m_DestCol = m_NextCol;
				m_DestRow = m_NextRow - 1;
			}
			else if (flag == 1) {
				m_DestCol = m_NextCol + 1;
				m_DestRow = m_NextRow;
			}
			else if (flag == 2) {
				m_DestCol = m_NextCol;
				m_DestRow = m_NextRow + 1;
			}
			else {
				m_DestCol = m_NextCol - 1;
				m_DestRow = m_NextRow;
			}
		} while (!IsValidDestinationSquare(currentBoard, 1));
		m_frontMove = abs(m_DestRow - m_NextRow);
		m_lateralMove = abs(m_DestCol - m_NextCol);
		m_direction = "frontally";
		m_secondDirection = "laterally";
		cout << "It moved it frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ") to defend the special die! ";
		a_board.UpdateComputerMove(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, DieToRoll, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
		m_model.DisplayBoard(a_board);
		// Again, update and display the board and then get out of the function.
		return;
	}
	// If we get here then the computer cannot win nor block.
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 9; j++) {
			currentRow = i;
			currentCol = j;
			dist = abs(currentRow - rowOfHumanKeyPiece) + abs(currentCol - colOfHumanKeyPiece);
			int allowedDist = (currentBoard[9 - i][j][1] - '0') % 48;
			if (currentBoard[9 - i][j][0] == 'C' && dist - allowedDist == min) {
				// If the move gets the computer closer to the key piece, check if the path is valid and choose the directions and movement at random.
				// But the die to move is not random though.
				m_NextRow = currentRow;
				m_NextCol = j;
				int invalid = 0;
				DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
				cout << "The computer chose to move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") to get closer to Garen's key piece!" << endl; 
				do {
					if (invalid == 10) { // If the computer made 10 wrong guesses they forfeit.
						cout << "The computer forfeited its turn!" << endl;
						return;
					}
					int firstMove = ((rand() % allowedDist) + 1);
					int flag = (rand() % 2);
					int secondMove = allowedDist - firstMove;
					int secondflag = (rand() % 2);
					if (flag == 0) {
						firstMove *= -1;
					}
					if (secondflag == 0) {
						secondMove *= -1;
					}
					m_DestCol = m_NextCol + firstMove;
					m_DestRow = m_NextRow + secondMove;
					m_frontMove = abs(m_DestRow - i);
					m_lateralMove = abs(m_DestCol - m_NextCol);
					if (!IsValidDestinationSquare(currentBoard, allowedDist) || !IsValidPath(currentBoard)) {
						invalid++;
						continue;
					}
				} while (!IsValidDestinationSquare(currentBoard, allowedDist) || !IsValidPath(currentBoard));
				if (m_direction == "frontally") {
					cout << "It moved it frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ") because it had no moves to win the game or block the human's dice! ";
				}
				else {
					cout << "It moved it laterally by " << m_lateralMove << " and frontally by " << m_frontMove << " to square (" << m_DestRow << ", " << m_DestCol << ") because it had no moves to win the game or block the human's dice! ";
				}
				a_board.UpdateComputerMove(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, DieToRoll, i, m_NextCol, m_DestRow, m_DestCol);
				m_model.DisplayBoard(a_board);
				// Update the board and get out of the function.
				return;
			}
		}
	}
}
/* *********************************************************************
Function Name: HelpHuman
Purpose: To allow the computer player to suggest a move to the human if it asks for help.
Returns: True if the human took the suggestion, false otherwise.
Parameters:
a_board, the current board passed by reference. It holds the all the computer and human dice.
a_turn, an integer. It refers to the current turn number
a_first, a string passed by value to get the first player
a_player, a string passed by value to get the current player
Local Variables:
currentBoard, a pointer to a pointer to an array of strings (2D array containing the board)
coords, a array of (x, y) pairs containing all dice in a blocking path on the board
Algorithm:
1) Access the board using the getter function of a_board.
2) Get the row and column of the human and computer key dice.
3) For each space on the board, check if there is a die that will lead to a win. If there is, suggest that move.
4) For each computer die on the board, see if it can get to the human key die right away. If it can, determine all possible paths that be invaded.
5) If none of them result in a blocking move or if the key die is adjacent to a die with 1 on the top, suggest moving the key piece. Otherwise, suggest the piece that blocks the human from winning the game. This prevents the computer from winning even if they had many moves to win though does not fit with certain cases.
6) If 3, 4, and 5 don't result in a successful move made by the human, suggest the die which is the minimum of the distance to the key piece minus the number at the top of the die before the move.
7) If 6 is what results in a reasonable move, choose the directions at random until the computer chooses a valid path. If the computer made 10 incorrect paths it has nothing to say to the human.
8) If the human took the suggestion, update the board and the faces of the dice by calling a_board::UpdateBoard, then Die::Rotate.
********************************************************************* */
bool Computer::HelpHuman(Board & a_board) {
	string ** currentBoard = a_board.GetBoard();
	string DieToRoll = "";
	// Get row and column of all the key dice.
	int rowOfHumanKeyPiece = a_board.FindRowKeyPiece();
	int colOfHumanKeyPiece = a_board.FindColKeyPiece();
	int rowOfCompKeyPiece = a_board.FindRowCompKeyPiece();
	int colOfCompKeyPiece = a_board.FindColCompKeyPiece();
	bool isOnKeySquare = false;
	int min = 25;
	int dist, allowedDist, distToOtherKeySquare;
	int currentRow;
	int currentCol;
	int comp = 0;
	int human = 0;
	int humanRow, humanCol;
	int distToCompKeyDie;
	int humanAllowedDist;
	// Check if the human can win the game.
	for (int i = 8; i >= 1; i--) {
		for (int j = 9; j >= 1; j--) {
			currentRow = i;
			currentCol = j;
			if (currentBoard[9 - i][j][0] == 'H') {
				dist = abs(currentRow - rowOfCompKeyPiece) + abs(currentCol - colOfCompKeyPiece);
				distToOtherKeySquare = abs(currentRow - 8) + abs(currentCol - 5);
				allowedDist = (currentBoard[9 - i][j][1] - '0') % 48;
				isOnKeySquare = (distToOtherKeySquare == allowedDist && currentBoard[9 - i][j][1] == '1' && currentBoard[9 - i][j][1] == '1');
				if (dist == allowedDist || isOnKeySquare) { // If the distance to the key piece is equal to the allowed distance and the path is not blocked, then this is a move that captures the key piece
					m_NextRow = currentRow;
					m_NextCol = currentCol;
					DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
					if (dist == allowedDist) {
						m_DestCol = colOfCompKeyPiece;
						m_DestRow = rowOfCompKeyPiece;
					}
					else if (isOnKeySquare) {
						m_DestCol = 5;
						m_DestRow = 8;
					}
					m_frontMove = abs(m_DestRow - m_NextRow);
					m_lateralMove = abs(m_DestCol - m_NextCol);
					if (!IsValidPath(currentBoard)) {
						// Invalid path. Move on.
						continue;
					}
					// Suggest the move.
					cout << "Move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ")";
					if (m_direction == "frontally") {
						cout << " frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ") to win the round!" << endl;
					}
					else {
						cout << " laterally by " << m_lateralMove << " and frontally by " << m_frontMove << " to square (" << m_DestRow << ", " << m_DestCol << ") to win the round!" << endl;
					}
					// If the human took the suggestion have the human automatically use the move.
					if (TakeSuggestion()) {
						if (m_direction == "frontally") {
							m_secondDirection = "laterally";
							cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_frontMove << " and laterally by " << m_lateralMove << " ";
						}
						else {
							m_secondDirection = "frontally";
							cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_lateralMove << " and frontally by " << m_frontMove << " ";
						}
						cout << "to square (" << m_DestRow << ", " << m_DestCol << ")! ";
						string currentDie = currentBoard[9 - m_NextRow][m_NextCol];
						a_board.UpdateBoard(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, currentDie, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
						// Display the updated board on the screen
						m_model.DisplayBoard(a_board);
						return true;
					}
					return false;
				}
				if (dist - allowedDist < min) { // Otherwise, set the minimum equal to the difference between the distance to the key die and the allowed distance
					min = dist - allowedDist;
				}
			}
		}
	}
	int count = 0;
	int blocking = 0;
	pair<int, int> coords[200];
	// Check for blocking moves.
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 9; j++) {
			humanRow = i;
			humanCol = j;
			if (currentBoard[9 - i][j][0] == 'C') {
				distToCompKeyDie = abs(humanRow - rowOfHumanKeyPiece) + abs(humanCol - colOfHumanKeyPiece);
				humanAllowedDist = (currentBoard[9 - i][j][1] - '0') % 48;
				if (humanAllowedDist == distToCompKeyDie) {
					m_NextRow = humanRow;
					m_NextCol = humanCol;
					DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
					m_DestCol = colOfHumanKeyPiece;
					m_DestRow = rowOfHumanKeyPiece;
					if (!IsValidPath(currentBoard)) {
						// Invalid path. Move on.
						continue;
					}
					blocking++;
					// If this is adjacent to the key die, move on.
					if (distToCompKeyDie < 2) {
						continue;
					}
					// Get all the coordinates in the blocking path.
					GetAllCoordsInBlockingPath(coords, currentBoard, count);
				}
			}
		}
	}
	// If the blocking move was successful, suggest it.
	// If the human took the suggestion, automatically use the move.
	if (MakeBlockingMove(a_board, coords, currentBoard, count, 'H')) {
		if (TakeSuggestion()) {
			if (m_direction == "frontally") {
				m_secondDirection = "laterally";
				cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_frontMove << " and laterally by " << m_lateralMove << " ";
			}
			else {
				m_secondDirection = "frontally";
				cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_lateralMove << " and frontally by " << m_frontMove << " ";
			}
			cout << "to square (" << m_DestRow << ", " << m_DestCol << ")! ";
			string currentDie = currentBoard[9 - m_NextRow][m_NextCol];
			a_board.UpdateBoard(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, currentDie, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
			// Display the updated board on the screen
			m_model.DisplayBoard(a_board);
			return true;
		}
		return false;
	}
	else if (blocking >= 1) {
		// Otherwise if there exists one blocking move, move the key die.
		m_NextRow = rowOfHumanKeyPiece;
		m_NextCol = colOfHumanKeyPiece;
		DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
		do {
			int flag = rand() % 4;
			if (flag == 0) {
				m_DestCol = m_NextCol;
				m_DestRow = m_NextRow - 1;
			}
			else if (flag == 1) {
				m_DestCol = m_NextCol + 1;
				m_DestRow = m_NextRow;
			}
			else if (flag == 2) {
				m_DestCol = m_NextCol;
				m_DestRow = m_NextRow + 1;
			}
			else {
				m_DestCol = m_NextCol - 1;
				m_DestRow = m_NextRow;
			}
		} while (!IsValidHumanDestinationSquare(currentBoard, 1));
		m_frontMove = abs(m_DestRow - m_NextRow);
		m_lateralMove = abs(m_DestCol - m_NextCol);
		if (m_frontMove != 0) {
			m_direction = "frontally";
			m_secondDirection = "laterally";
		}
		else if (m_lateralMove != 0) {
			m_direction = "laterally";
			m_secondDirection = "frontally";
		}
		// Suggest the move.
		cout << "Move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") " << m_direction << " by " << m_frontMove << " and " << m_secondDirection << " by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ") to defend the special die!" << endl;
		// If the human took the suggestion use the move.
		if (TakeSuggestion()) {
			if (m_direction == "frontally") {
				m_secondDirection = "laterally";
				cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_frontMove << " and laterally by " << m_lateralMove << " ";
			}
			else {
				m_secondDirection = "frontally";
				cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_lateralMove << " and frontally by " << m_frontMove << " ";
			}
			cout << "to square (" << m_DestRow << ", " << m_DestCol << ")! ";
			string currentDie = currentBoard[9 - m_NextRow][m_NextCol];
			a_board.UpdateBoard(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, currentDie, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
			// Display the updated board on the screen
			m_model.DisplayBoard(a_board);
			return true;
		}
		return false;
	}
	// If we get here there were no winning or blocking moves that the computer could recommend.
	for (int i = 8; i >= 1; i--) {
		for (int j = 9; j >= 1; j--) {
			currentRow = i;
			currentCol = j;
			dist = abs(currentRow - rowOfCompKeyPiece) + abs(currentCol - colOfCompKeyPiece);
			int allowedDist = (currentBoard[9 - i][j][1] - '0') % 48;
			if (currentBoard[9 - i][j][0] == 'H' && dist - allowedDist == min) {
				// Suggest the move that will get closest to the human's key piece.
				m_NextRow = currentRow;
				m_NextCol = j;
				int invalid = 0;
				DieToRoll = currentBoard[9 - m_NextRow][m_NextCol];
				cout << "Move " << DieToRoll << " located at (" << m_NextRow << ", " << m_NextCol << ") to get closer to the computer's key piece!" << endl;
				do {
					if (invalid == 10) { // If ten invalid inputs were given, then the computer can't help.
						cout << "The computer does not know what to tell the human to do!" << endl;
						return false;
					}
					int firstMove = ((rand() % allowedDist) + 1);
					int flag = (rand() % 2);
					int secondMove = allowedDist - firstMove;
					int secondflag = (rand() % 2);
					if (flag == 0) {
						firstMove *= -1;
					}
					if (secondflag == 0) {
						secondMove *= -1;
					}
					m_DestCol = m_NextCol + firstMove;
					m_DestRow = m_NextRow + secondMove;
					m_frontMove = abs(m_DestRow - i);
					m_lateralMove = abs(m_DestCol - m_NextCol);
					if (!IsValidHumanDestinationSquare(currentBoard, allowedDist) || !IsValidPath(currentBoard)) {
						invalid++;
						continue;
					}
				} while (!IsValidHumanDestinationSquare(currentBoard, allowedDist) || !IsValidPath(currentBoard));
				if (m_direction == "frontally") {
					cout << "Move it frontally by " << m_frontMove << " and laterally by " << m_lateralMove << " to square (" << m_DestRow << ", " << m_DestCol << ") because there are no moves to win the game or block the opponent's dice! " << endl;
				}
				else {
					cout << "Move it laterally by " << m_lateralMove << " and frontally by " << m_frontMove << " to square (" << m_DestRow << ", " << m_DestCol << ") because there are moves to win the game or block the opponents's dice! " << endl;
				}
				if (TakeSuggestion()) {
					// If the human took the suggestion use the suggested move.
					if (m_direction == "frontally") {
						m_secondDirection = "laterally";
						cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_frontMove << " and laterally by " << m_lateralMove << " ";
					}
					else {
						m_secondDirection = "frontally";
						cout << "Garen has decided to move " << currentBoard[9 - m_NextRow][m_NextCol] << " located at (" << m_NextRow << " , " << m_NextCol << ") " << m_direction << " by " << m_lateralMove << " and frontally by " << m_frontMove << " ";
					}
					cout << "to square (" << m_DestRow << ", " << m_DestCol << ")! ";
					string currentDie = currentBoard[9 - m_NextRow][m_NextCol];
					a_board.UpdateBoard(currentBoard, m_frontMove, m_lateralMove, m_direction, m_secondDirection, currentDie, m_NextRow, m_NextCol, m_DestRow, m_DestCol);
					// Display the updated board on the screen
					m_model.DisplayBoard(a_board);
					return true;
				}
				return false;
			}
		}
	}
	return false;
}