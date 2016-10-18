#include "Board.h"
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
Board::Board()
{
	m_board = new string*[9];
	// Initialize the board as the game begins with empty spots
	for (int i = 0; i < 9; i++) {
		m_board[i] = new string[10];
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			m_board[i][j] = "0";
		}
	}
	// Initialize x and y coordinates
	m_topPiece = 1;
	m_rightPiece = 1;
	m_xcoord = 1;
	m_ycoord = 8;
}/* Function Name : DrawBoard
Purpose : To draw the initial board when a round begins.
Parameters :
None
Algorithm :
1) For each empty space in the multidimensional array, check the subscript.
2) If both row and column are 0 place an empty string in the extreme left and the y coordinate numbers for the rest of the numbers
3) If row is 1, then this is row 8, so populate the computer's home row
4) If row is 8, this is row 1, so populate the human's home row.
5) In either case call GetStartingPiece to determine the die to place at the location.
6) If the row is not 0, 1, or 8, then place zeros in the board and at the extreme left column put the x coordinate numbers
Assistance Received : none
********************************************************************* */
void Board::DrawBoard() {
	for (int i = 0; i < 9; i++) {
		if (i == 0) { // If this is the first row, place the y coordinates on the top
			for (int j = 0; j < 10; j++) {
				if (j == 0) {
					m_board[i][j] = "";
				}
				else {
					m_board[i][j] = to_string(j);
				}
			}
		}
		else if (i == 1) { // If this is the second row, then this is the computer's home row.
			for (int j = 0; j < 10; j++) {
				if (j == 0) {
					m_board[i][j] = to_string(m_ycoord);
					m_ycoord--;
				}
				else {
					// Get the computer's starting die
					m_board[i][j] = GetStartingPiece(m_board[i], j, "C");
				}
			}
		}
		else if (i == 8) { // If this is the last row, this is the human's home row.
			for (int j = 0; j < 10; j++) {
				if (j == 0) {
					m_board[i][j] = to_string(m_ycoord);
					m_ycoord--;
				}
				else {
					m_board[i][j] = GetStartingPiece(m_board[i], j, "H");
				}
			}
		}
		else {
			// Otherwise, populate empty squares with 0's.
			m_board[i][0] = to_string(m_ycoord);
			for (int j = 1; j < 10; j++) {
				if (m_board[i][j] != "0") {
					m_board[i][j] = "0";
				}
			}
			m_ycoord--;
		}
	}
}
/* Function Name : PrintBoard
Purpose : To display the board. This is called by DisplayBoard in BoardView.
Parameters :
a_out, the stream passed by reference for which to display the board.
********************************************************************* */
void Board::PrintBoard(ostream & a_out) {
	// For each line of the board, print it out to the screen.
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			a_out << setw(5) << m_board[i][j];
		}
		a_out << endl;
	}
}
/* Function Name : FindKeyPiece
Purpose : To determine if the game was over because the human captured the key die
Returns: True if found, false if not found.
Parameters :
a_key, the string passed by value which contains the die to search for.
********************************************************************* */
bool Board::FindKeyPiece(string a_key) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (m_board[i][j] == a_key) {
				// If we get here, the piece was found
				return true;
			}
		}
	}
	return false; // Otherwise, it does not exist.
}
/* Function Name : FindColKeyPiece
Purpose : Determines the column of the human key piece
Returns: Column if found, -1 if not found
Parameters :
None
********************************************************************* */
int Board::FindColKeyPiece() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (m_board[i][j] == "H11") { 
				// IF we get here the human's key piece was found
				return j;
			}
		}
	}
	// It was not found
	return -1;
}
/* Function Name : FindRowKeyPiece
Purpose : Determines the row of the human key piece
Returns: Row if found, -1 if not found
Parameters :
None
********************************************************************* */
int Board::FindRowKeyPiece() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (m_board[i][j] == "H11") { // If we get here then the human's key piece was found
				return 9 - i;
			}
		}
	}
	// Otherwise it was not found
	return -1;
}
/* Function Name : FindColCompKeyPiece
Purpose : Determines the column of the computer key piece
Returns: Column if found, -1 if not found
Parameters :
None
********************************************************************* */
int Board::FindColCompKeyPiece() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (m_board[i][j] == "C11") { // If we get here the computer's key piece was found
				return j;
			}
		}
	}
	return -1; // Otherwise it was not found
}
/* Function Name : FindRowCompKeyPiece
Purpose : Determines the row of the computer key piece
Returns: Row if found, -1 if not found
Parameters :
None
********************************************************************* */
int Board::FindRowCompKeyPiece() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			if (m_board[i][j] == "C11") { // If we get here the key piece was found.
				return 9 - i;
			}
		}
	}
	return -1; // It was not found at this point
}
/* Function Name : GetStartingPiece
Purpose : To determine what the top and right faces of the dice should be at the beginning of the game.
Returns: The string representing the die.
Parameters :
a_col[], a string array passed by value which holds the columns in the multidimensional array
a_index, an integer referring to the current index in the inner for loop
a_player, the string representing "C" or "H" to place at the beginning of the string to represent a computer or human die
Algorithm :
1) Check the subscript of the inner for loop.
2) If it is 5, then this is a key die, set top and right to 1.
3) If it is 1, set top to 5 and right to 6
4) If it is 2, set top to 1 and right to 5
5) If it is 6, set top to 6 and right to 2
6) If it is 7, set top to 2 and right to 1
7) Otherwise the die is in the middle, so convert ASCII code to integer and subtract the opposite die's top and right respectively from 7 to get the top and right faces of the middle dice.
8) Set the top and right faces to the results of the function.
9) Return the value as a concatenated string.
Assistance Received : none
********************************************************************* */
string Board::GetStartingPiece(string a_col[], int a_index, string a_player) {
	// Computer or human
	string piece = a_player;
	// If this is in the middle it is the key piece
	if (a_index == 5) {
		m_topPiece = 1;
		m_rightPiece = 1;
	}
	else if (a_index == 1) {
		// if it is 1, then it is a 5/6 die.
		m_topPiece = 5;
		m_rightPiece = 6;
	}
	else if (a_index == 2) {
		// if it is 2, it is a 1/5 die.
		m_topPiece = 1;
		m_rightPiece = 5;
	}
	// If it is close to the middle, subtract the opposite element from 7 to get the top and right faces. Convert ASCII to integer.
	else if (a_index == 3 || a_index == 4 || a_index == 8 || a_index == 9) {
		char firstPiece = a_col[a_index - 2][1];
		char secondPiece = a_col[a_index - 2][2];
		int first = (firstPiece - '0') % 48;
		int second = (secondPiece - '0') % 48;
		m_topPiece = 7 - first;
		m_rightPiece = 7 - second;
	}
	else if (a_index == 6) {
		// if it is 6, it is a 6/2 die.
		m_topPiece = 6;
		m_rightPiece = 2;
	}
	else if (a_index == 7) {
		// if it is 7, it is a 2/1 die.
		m_topPiece = 2;
		m_rightPiece = 1;
	}
	// Update the top and right faces.
	m_die.SetRight(m_rightPiece);
	m_die.SetTop(m_topPiece);
	// Return the die as a string
	return piece + m_die.ToString();
}
/* Function Name : UpdateBoard
Purpose : To update the board from a human's move.
Parameters :
a_board, a pointer to a pointer of strings passed by reference. It contains the board and its dice.
a_front, an integer giving the frontal distance
a_lat, an integer giving the lateral distance
a_firstDirection, a string passed by reference. It gives us the first movement of the die
a_secondDirection, a string passed by reference. It gives us the second movement of the die
a_die, a string passed by reference giving the die to be moved
a_NextRow, an integer indicating the starting x coordinate
a_NextCol, an integer indicating the starting y coordinate
a_DestRow, an integer indicating the ending x coordinate
a_DestCol, an integer indicating the ending y coordinate
Algorithm :
1) Call the Rotate function of the Die class to get the new top and right faces of the die after the move.
2) If there was a human die at the destination tell the human they captured that die.
3) Update the board with the new die.
Assistance Received : none
********************************************************************* */
void Board::UpdateBoard(string ** a_board, int a_front, int a_lat, string & a_firstDirection, string & a_secondDirection, string & a_die, int a_NextRow, int a_NextCol, int a_DestRow, int a_DestCol) {
	// Determine the new top and right faces after the move.
	string newDie = m_die.Rotate(a_board, a_die, a_firstDirection, a_front, a_secondDirection, a_lat, a_NextRow, a_NextCol, a_DestRow, a_DestCol);
	// Change the start to empty after the move
	m_board[9 - a_NextRow][a_NextCol] = "0";
	cout << "The die is now " << newDie << " at (" << a_DestRow << ", " << a_DestCol << ")! ";
	// If there was an enemy die at the destination, say that it was captured.
	if (m_board[9 - a_DestRow][a_DestCol] != "0") {
		cout << "Garen captured " << m_board[9 - a_DestRow][a_DestCol] << " which was previously located at (" << a_DestRow << ", " << a_DestCol << ")!";
	}
	cout << endl;
	// Update the destination.
	m_board[9 - a_DestRow][a_DestCol] = newDie;
}
// Getter function to access the board
string ** Board::GetBoard()
{
	return m_board;
}
/* Function Name : UpdateComputerMove
Purpose : To update the board from a computer's move.
Parameters :
a_board, a pointer to a pointer of strings passed by reference. It contains the board and its dice.
a_front, an integer giving the frontal distance
a_lat, an integer giving the lateral distance
a_firstDirection, a string passed by reference. It gives us the first movement of the die
a_secondDirection, a string passed by reference. It gives us the second movement of the die
a_die, a string passed by reference giving the die to be moved
a_NextRow, an integer indicating the starting x coordinate
a_NextCol, an integer indicating the starting y coordinate
a_DestRow, an integer indicating the ending x coordinate
a_DestCol, an integer indicating the ending y coordinate
Algorithm :
1) Call the RotateComputerDie function of the Die class to get the new top and right faces of the die after the move.
2) If there was a human die at the destination tell the computer they captured that die.
3) Update the board with the new die.
Assistance Received : none
********************************************************************* */
void Board::UpdateComputerMove(string ** a_board, int a_front, int a_lat, string & a_firstDirection, string & a_secondDirection, string & a_die, int a_NextRow, int a_NextCol, int a_DestRow, int a_DestCol) {
	// Determine the new top and right faces after the move
	string newDie = m_die.RotateComputerDie(a_board, a_die, a_firstDirection, a_front, a_secondDirection, a_lat, a_NextRow, a_NextCol, a_DestRow, a_DestCol);
	// Make the starting square empty.
	m_board[9 - a_NextRow][a_NextCol] = "0";
	cout << "The die is now " << newDie << " at (" << a_DestRow << ", " << a_DestCol << ")! ";
	// if the computer captured an enemy die, say that the enemy die was captured
	if (m_board[9 - a_DestRow][a_DestCol] != "0") {
		cout << "The computer captured " << m_board[9 - a_DestRow][a_DestCol] << " which was previously located at (" << a_DestRow << ", " << a_DestCol << ")!";
	}
	cout << endl;
	// Update the destination.
	m_board[9 - a_DestRow][a_DestCol] = newDie;
}
// Getters and setters
int Board::GetTopPiece() const {
	return m_topPiece;
}

int Board::GetRightPiece() const {
	return m_rightPiece;
}

int Board::GetX() const {
	return m_xcoord;
}

int Board::GetY() const {
	return m_ycoord;
}
void Board::SetX(int a_xcoord) {
	m_xcoord = a_xcoord;
}
void Board::SetY(int a_ycoord) {
	m_ycoord = a_ycoord;
}
void Board::SetTop(int a_top) {
	m_topPiece = a_top;
}
void Board::SetRight(int a_right) {
	m_rightPiece = a_right;
}
/* Function Name : ReadSerializationFile
Purpose : To restore the board from the saved game.
Parameters :
a_in, the serialization file passed by reference. It holds the board that the suspended game was saved to, as well as the human's score, computer's score, round #, and turn #. When the function returns, the file pointer will be at the end of the file, so we would have to rewind to the beginning of the file.
a_lines, an integer passed by reference. It contains the number of lines in the board. When the function returns, this value will be modified for use in RestoreGameData in the round class.
Local Variables :
lines, a vector of strings. It carries all the lines of the saved game. We only read the first 9 lines of this file in this function because we specifically want to get the board from this function.
Algorithm :
	1) For each line in the file insert into the vector.
	2) Set the reference parameter, a_lines equal to 9 so it can be used to get the rest of the file. This is why we passed it by reference.
	3) Use istringstream to split the first 9 lines of the file by whitespace. If it is the first row, display the column coordinates at the top.
	4) Replace each square of the board with the die from the file.
	Assistance Received : none
********************************************************************* */
void Board::ReadSerializationFile(ifstream & a_in, int & a_lines) {
	string newLine;
	vector<string> lines;
	// Insert into the vector.
	while (getline(a_in, newLine)) {
		lines.push_back(newLine);
	}
	a_lines = 9;
	// Read only the first 9 lines. This contains the board.
	// For each line in the file, use istringstream to parse it to the screen.
	for (int i = 0; i < a_lines; i++) {
		istringstream iss(lines.at(i));
		string item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11;
		string piece1, piece2, piece3, piece4, piece5, piece6, piece7, piece8, piece9, piece10, piece11;
		iss >> item1 >> item2 >> item3 >> item4 >> item5 >> item6 >> item7 >> item8 >> item9 >> item10 >> item11;
		if (i == 0) {
			piece1 = "";
			piece2 = item1;
			piece3 = item2;
			piece4 = item3;
			piece5 = item4;
			piece6 = item5;
			piece7 = item6;
			piece8 = item7;
			piece9 = item8;
			piece10 = item9;
		}
		else {
			piece1 = item1;
			piece2 = item2;
			piece3 = item3;
			piece4 = item4;
			piece5 = item5;
			piece6 = item6;
			piece7 = item7;
			piece8 = item8;
			piece9 = item9;
			piece10 = item10;
		}
		m_board[i][0] = piece1;
		m_board[i][1] = piece2;
		m_board[i][2] = piece3;
		m_board[i][3] = piece4;
		m_board[i][4] = piece5;
		m_board[i][5] = piece6;
		m_board[i][6] = piece7;
		m_board[i][7] = piece8;
		m_board[i][8] = piece9;
		m_board[i][9] = piece10;
	}
}