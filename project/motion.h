const int ONE_SQUARE = 136; // 2.25 inches * 25.4 mm/inch * 2pi*radius /180 = 148, where radius = 22.1mm
const int POW = 30;
const bool DEBUG = true;

void getInPosition(int currentRow, int currentCol, int toRow, int toCol);	// Karam
void moveForward();															// Karam
void moveBackward();														// Karam
void moveRight();															// Karam
void moveLeft();															// Karam
void moveDiagonal(int deltaX, int deltaY);									// Jin
void moveZ(bool up);														// Jin
void jump(int currentRow, int currentCol, int toRow, int toCol);			// Karam
void step(int currentRow, int currentCol, int toRow, int toCol);			// Jin
void removePiece(int jumpRow, int jumpCol);									// Karam
void calibrate();															// Jin

void getInPosition(int currentRow, int currentCol, int toRow, int toCol) {
	if (DEBUG) displayString(6, "getInPosition()");
	int deltaX = (toCol - currentCol);
	int deltaY = (toRow - currentRow);
	/*if (currentRow == -1){
		deltaX -= 1;
		deltaY -= 1;
	}*/
	moveDiagonal(deltaX, deltaY);
}

/**********  GENERIC MOVEMENT  **********/
void moveForward() {	// move one space forward
	if (DEBUG) displayString(6, "moveForward()");
	nMotorEncoder[motorB] = 0;
	motor[motorB] = POW;
	while (nMotorEncoder[motorB] < ONE_SQUARE) {}
	motor[motorB] = 0;
}

void moveBackward() {			// move one space backward
	if (DEBUG) displayString(6, "moveBackward()");
	nMotorEncoder[motorB] = 0;
	motor[motorB] = -POW;
	while (-nMotorEncoder[motorB] < ONE_SQUARE) {}
	motor[motorB] = 0;
}

void moveRight() {		// move ones space right
	if (DEBUG) displayString(6, "moveRight()");
	nMotorEncoder[motorA] = 0;
	motor[motorA] = -POW;
	while (-nMotorEncoder[motorA] < ONE_SQUARE) {}
	motor[motorA] = 0;
}

void moveLeft() {			// move one space left
	if (DEBUG) displayString(6, "moveLeft()");
	nMotorEncoder[motorA] = 0;
	motor[motorA] = POW;
	while (nMotorEncoder[motorA] < ONE_SQUARE) {}
	motor[motorA] = 0;
}

void moveDiagonal(int deltaX, int deltaY) {
		// assumes that |deltaX| == |deltaY|
  	if (DEBUG) displayString(6, "moveDiagonal()");
	
  	nMotorEncoder[motorA] = 0;
 	nMotorEncoder[motorB] = 0;
  	deltaX *= -ONE_SQUARE;
	deltaY *= ONE_SQUARE;
  	motor[motorA] = POW * sgn(deltaX);
  	motor[motorB] = POW * sgn(deltaY);
  	while(motor[motorA] != 0 || motor[motorB] != 0){
		if((abs(nMotorEncoder[motorA]) < deltaX){
  			motor[motorA] = 0;
		}
		if((abs(nMotorEncoder[motorB]) < deltaY){
  			motor[motorB] = 0;
		}
	}
}

/**********  MOVE PIECES  **********/
void moveZ(bool up) {
	if (DEBUG) displayString(6, "moveZ()");
	/* Moves the z-axis arm upward or downwards
	   until it encounters resistance. */
	nMotorEncoder[motorC] = 0;
	int prev = -10;
	if (up) {
		motor[motorC] = -20;
	}
	else {
		motor[motorC] = 20;
	}
	while (!(abs(nMotorEncoder[motorC] - prev) < 0.1)) {
		prev = nMotorEncoder[motorC];
		wait1Msec(50);
	}
	motor[motorC] = 0;
}

//if jump code

void jump(int currentRow, int currentCol, int toRow, int toCol){
	if (DEBUG) displayString(6, "jump()");
  	int deltaY = toRow - currentRow;
  	int deltaX = toCol - currentCol;

  	moveZ(true);//magnet up

  	if (deltaY > 0){
    		moveForward();

    		if (deltaX > 0){
      			moveDiagonal(1, 1);
      			moveRight();
		 }
    		else{ //deltaX < 0
     			moveDiagonal(-1, 1);
      			moveLeft();
    			}
  		}

  	else{ //deltaY < 0
   		moveBackward();
   		if (deltaX > 0){
      			moveDiagonal(1, -1);
     			moveRight();
    		}
    		else{ //deltaX < 0
      			moveDiagonal(-1, -1);
      			moveLeft();
    		}
  	}
  	moveZ(false);//magnet down
}

void step(int currentRow, int currentCol, int toRow, int toCol) {
	if (DEBUG) displayString(6, "step()");
	// steps one space in stated direction in separate dx and dy steps
	int deltaY = toRow - currentRow;
  	int deltaX = toCol - currentCol;
	moveZ(true);			// magnet up
	if (deltaY > 0) {
		moveForward();
	}
	else {
		moveBackward();
	}
	if (deltaX > 0) {
		moveRight();
	}
	else {
		moveLeft();
	}
	moveZ(false);
}

void removePiece(int jumpRow, int jumpCol){
	if (DEBUG) displayString(6, "removePiece()");
  	moveZ(true);	// magnet up
	moveRight();
	if ((7 - jumpRow) > jumpCol){
		moveDiagonal(-jumpCol, jumpCol);
		jumpCol = 0;
	}
	else{
		moveDiagonal(jumpRow-7, 7-jumpRow);
		jumpCol += jumpRow - 7;
		moveDiagonal(-jumpCol, -jumpCol);
	}

	moveZ(false);
}

void calibrate() {		// move to -1, -1
	// motorA is stopped when motorB is stopped by the button
	if (DEBUG) displayString(6, "calibrate()");
	motor[motorA] = POW;
	motor[motorB] = -POW;
	time1[T2] = 0;

	while (time1[T2] < 10000) {		// should not take longer than 10 sec
		if (SensorValue[S4] == 1) {
			wait1Msec(100);
			break;
		}
	}
	motor[motorA] = 0;
	motor[motorB] = 0;
}
