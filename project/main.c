#include <algorithm.c>
#include <motion.c>
int board[8][8];
int blackCounter = 0, whiteCounter = 0;

task main() {
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorSONAR;
	displayString(0, "GROUP 100");
	displayString(1, "AUTOCHECKERS");
	wait1Msec(750);

	// MENU
	eraseDisplay();
	displayString(0, "USE GATE TO START");
	displayString(1, "WHEN PIECES ARE");
	displayString(2, "SET");
	while (SensorValue[S2] > 10) {} //this value needs to be tested
	eraseDisplay();

	// GAME
	bool blacksTurn = true;
	newGame();
	while(!checkWinner()){
		makeMove(blacksTurn);				// NOTE: Need to confirm this is an actual function
		blacksTurn = !blacksTurn;
	}
}
