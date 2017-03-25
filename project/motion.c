const int ONE_SQUARE = 3 * 25.4 * 2 * PI * 22.1 / 180; // 3 inches * 25.4 mm/inch * 2pi*radius /180
const int POW = 60;
int CURRENT_ROW = -1;
int CURRENT_COL = -1;

void getInPosition	(int moveRow, int moveCol) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	distX = (moveCol - CURRENT_COL) * ONE_SQUARE;
	distY = (moveROW - CURRENT_ROW) * ONE_SQUARE;
	if(distX > 0){
	  motor[motorA] = POW;
	}
	else{
	  motor[motorA] = -POW;
	}
	if(distY > 0){
	  motor[motorB] = POW;
	}
  else{
    motor[motorB] = -POW;
  }
	if (CURRENT_ROW == -1){
	  while(motor[motorA] != 0 || motor[motorB] != 0){
	    distX -= ONE_SQUARE;
	    distY -= ONE_SQUARE;
	    if(nMotorEncoder[motorA] == distX + 0){ // +0 needs to be determined
	      motor[motorA] = 0;
	    }
	    if(nMotorEncoder[motorB] == distY + 0){ 
	      motor[motorB] = 0;
	    }
	  }
	}
	else{
	  while(motor[motorA] != 0 || motor[motorB] != 0){
	    if(nMotorEncoder[motorA] == distX){
	      motor[motorA] = 0;
	    }
	    if(nMotorEncoder[motorB] == distY){
	      motor[motorB] = 0;
	    }
	  }
	}

}

/**********  GENERIC MOVEMENT  **********/
void moveForward() {		// move one space forward
	nMotorEncoder[motorB] = 0;
	motor[motorB] = POW;
	while (nMotorEncoder[motorB] < ONE_SQUARE) {}
	motor[motorB] = 0;
}

void moveBackward() {			// move one space backward
	nMotorEncoder[motorB] = 0;
	motor[motorB] = -POW;
	while (nMotorEncoder[motorB] > ONE_SQUARE) {}
	motor[motorB] = 0;
}

void moveRight() {		// move ones space right
	nMotorEncoder[motorA] = 0;
	motor[motorA] = POW;
	while (nMotorEncoder[motorA] < ONE_SQUARE) {}
	motor[motorA] = 0;
}

void moveLeft() {			// move one space left
	nMotorEncoder[motorA] = 0;
	motor[motorA] = -POW;
	while (nMotorEncoder[motorA] > ONE_SQUARE) {}
	motor[motorA] = 0;
}

/**********  MOVE PIECES  **********/
void moveZ(bool up) {
	/* Moves the z-axis arm upward or downwards
	   until it encounters resistance. */
	nMotorEncoder[motorC] = 0;
	int prev = -10;
	if (up) {
		motor[motorC] = -10;
	}
	else {
		motor[motorC] = 10;
	}
	while (!(abs(nMotorEncoder[motorC] - prev) < 0.1)) {
		prev = nMotorEncoder[motorC];
		wait1Msec(50);
	}
	motor[motorC] = 0;
}

//if jump code

void jump(int currentRow, int currentCol, int toRow, int toCol){

  int deltaY = toRow - currrentRow;
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
	// steps one space in stated direction in separate dx and dy steps
	int deltaY = toRow - currrentRow;
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
}

void removePiece(int jumpRow, int jumpCol){
  void getInPosition (jumpRow, jumpCol);
  moveZ(true);			// magnet up
  
}
/**********  MOVE MAGNET ONLY  **********/

