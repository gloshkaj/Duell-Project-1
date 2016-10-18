#include "BoardView.h"
#include "Board.h"

BoardView::BoardView()
{
	// Initialize
	displayed = false;
}
/* *********************************************************************
Function Name: DisplayBoard
Parameters:
a_board: the board object passed by reference.
********************************************************************* */
void BoardView::DisplayBoard(Board & a_board) {
	// Display the board on the screen to standard output (cout)
	a_board.PrintBoard(cout);
}