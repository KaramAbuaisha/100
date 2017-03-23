#include <algorithm.c>
#include <motion.c>
short board[8][8];
int blackCounter = 0, redCounter = 0;

task main() {
	displayString(0, "GROUP 100");
	displayString(1, "AUTOCHECKERS");
	wait1Msec(750);

	// MENU
	eraseDisplay();
	displayString(0, "PRESS ORANGE BUTTON");
	displayString(1, "WHEN PIECES ARE SET");
	while (nNxtButtonPressed != 3) {}

	// GAME
	bool blacksTurn = false;
	newGame();
	while(!checkWinner()){
		makeMove(blacksTurn);				// NOTE: Need to confirm this is an actual function
		blacksTurn = !blacksTurn;
	}
}
