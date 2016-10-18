#include "Tournament.h"
Tournament::Tournament()
{
}
/* Function name: DetermineWinner
Purpose: To determine who won the tournament
Parameters: None
*/
void Tournament::DetermineWinner() {
	int compWins = m_round.GetComputerWins();
	int humanWins = m_round.GetHumanWins();
	// Get the scores of the computer and human. If the computer's score is greater than the human's, the computer won.
	// If the human's was greater, then the human won.
	// Otherwise, the scores are tied and the game is a draw.
	cout << "The computer won " << compWins << " rounds and Garen won " << humanWins << " rounds. " << endl;
	cout << "The winner of this tournament is.....";
	system("pause");
	if (compWins < humanWins) {
		cout << "Garen!" << endl;
	}
	else if (compWins > humanWins) {
		cout << "The computer!" << endl;
	}
	else {
		cout << "Nobody! The scores were tied, so this tournament was a draw!" << endl;
	}
	cout << "Thank you for playing Duell in C++, assigned to OPL Fall 2016 taught by Amruth Kumar, played by Garen Loshkajian!" << endl;
}
/* Function name: PlayTournament
Purpose: To play a series of rounds
Parameters: None
*/
void Tournament::PlayTournament() {
	char choice;
	// While the user wants to play more rounds,
	do {
		// Play a new round
		m_round.PlayGame();
		// Ask if the user wants to play again
		do {
			cout << "Do you want to play another round?" << endl;
			cin >> choice;
		} while (toupper(choice) != 'Y' && toupper(choice) != 'N');
	} while (toupper(choice) != 'N');
	// Get the scores of the computer and human player and determine the winner
	cout << "This tournament has ended!" << endl;
	DetermineWinner();
}
Tournament::~Tournament()
{
}