const int ONE_SQUARE = 148; // 2.25 inches * 25.4 mm/inch * 2pi*radius /180 = 148, where radius = 22.1mm
const int POW = 60;

void getInPosition(int currentRow, int currentCol, int toRow, int toCol) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	int deltaX = (toCol - currentCol) * ONE_SQUARE;
	int deltaY = (toRow - currentCol) * ONE_SQUARE;
	if(deltaX > 0){
	  motor[motorA] = POW;
	}
	else{
	  motor[motorA] = -POW;
	}
	if(deltaY > 0){
	  motor[motorB] = POW;
	}
  else{
    motor[motorB] = -POW;
  }
	if (currentRow == -1){
	  while(motor[motorA] != 0 || motor[motorB] != 0){
	    deltaX -= ONE_SQUARE;
	    deltaY -= ONE_SQUARE;
	    if(nMotorEncoder[motorA] == deltaX + 0){ // +0 needs to be determined
	      motor[motorA] = 0;
	    }
	    if(nMotorEncoder[motorB] == deltaY + 0){ 
	      motor[motorB] = 0;
	    }
	  }
	}
	else{
	  while(motor[motorA] != 0 || motor[motorB] != 0){
	    if(nMotorEncoder[motorA] == deltaX){
	      motor[motorA] = 0;
	    }
	    if(nMotorEncoder[motorB] == deltaY){
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

void moveDiagonal(int deltaX, int deltaY) {
  nMotorEncoder[motorA] = 0;
  nMotorEncoder[motorB] = 0;
  deltaX *= ONE_SQUARE;
  deltaY *= ONE_SQUARE;
  motor[motorA] = POW * sgn(deltaX);
  motor[motorB] = POW * sgn(deltaY);
  while (abs(nMotorEncoder[motorA]) < deltaX ||
         abs(nMotorEncoder[motorB]) < deltaY) {}
  motor[motorA] = 0;
  motor[motorB] = 0;
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
}

void removePiece(int jumpRow, int jumpCol){
  moveZ(true);			// magnet up
	if(jumpCol<4){
		moveLeft();
		if(jumpCol != 0){
			if ((7 - jumpRow) > jumpCol){
				moveDiagonal(-jumpCol, jumpCol);
				jumpCol = 0;
			}
			else{
				moveDiagonal(jumpRow-7, 7-jumpRow);
				jumpCol += jumpRow - 7;
				moveDiagonal(-jumpCol, -jumpCol);
			}
		}
	}
	else{
		moveRight();
		jumpCol = 7 - jumpCol;
		if(jumpCol != 0){
			if ((7 - jumpRow) > jumpCol){
				moveDiagonal(jumpCol, jumpCol);
				jumpCol = 0;
			}
			else{
				moveDiagonal(jumpRow-7, 7-jumpRow);
				jumpCol += jumpRow - 7;
				moveDiagonal(jumpCol, -jumpCol);
			}
		}
		
	}	
}
