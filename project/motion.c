const float SCALE = 3 * 25.4;		// 3 in/square to millimetres
const float WHEEL_RADIUS = 22.1;		// mm
const float CONVERT = PI / 180 * WHEEL_RADIUS;
const short MAX_M_POW = 60;
const short START_POW = 10;

/**********  CONVERSION  **********/
float angToDist(float angle) {
	return angle * CONVERT;
}

float distToAng(float distance) {
	return distance / CONVERT;
}
/*
void move(short starti, short startj, short fini, short finj) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	float deltaX = distToAng((finj - startj) * SCALE);
	float deltaY = distToAng((fini - starti) * SCALE);
	float midX = deltaX/2, midY = deltaY/2;
	short xPow, yPow;
	if (deltaX < deltaY) {
		yPow = MAX_M_POW;
		xPow = MAX_M_POW * deltaX/deltaY;
	}
	else {
		xPow = MAX_M_POW;
		yPow = MAX_M_POW * deltaY/deltaX;
	}
	if (deltaX < 0) {
		xPow = -xPow;
	}
	if (deltaY < 0) {
		yPow = -yPow;
	}
	do {
		displayString(0, "dX = %d", angToDist(nMotorEncoder[motorA])/SCALE);
		displayString(1, "dY = %d", angToDist(nMotorEncoder[motorB])/SCALE);
		displayString(2, "dTot = %d", angToDist(nMotorEncoder[motorA] + nMotorEncoder[motorB])/SCALE);
		// increase power linearly to midpoint, then
		// decrease it linearly to finish.
		if (deltaX != 0) {
			motor[motorA] = (-abs(nMotorEncoder[motorA] - midX)/midX + 1) * (xPow - START_POW) + START_POW;
		}
		if (deltaY != 0) {
			motor[motorB] = (-abs(nMotorEncoder[motorB] - midY)/midY + 1) * (yPow - START_POW) + START_POW;
		}
	} while (motor[motorA] > 0 || motor[motorB] > 0);
	motor[motorA] = 0;
	motor[motorB] = 0;
	return;
}
*/

void move(short starti, short startj, short fini, short finj, bool debug = false) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	float deltaX = distToAng((finj - startj) * SCALE);
	float deltaY = distToAng((fini - starti) * SCALE);
	float dTot = sqrt(deltaX * deltaX + deltaY * deltaY);
	short xPow = 0, yPow = 0;
	if (deltaX != 0) {
		xPow = MAX_M_POW;
		if (deltaX < 0) xPow = -xPow;
	}
	if (deltaY != 0) {
		yPow = MAX_M_POW;
		if (deltaY < 0) yPow = -yPow;
	}
	while (nMotorEncoder[motorA] + nMotorEncoder[motorB] < dTot) {
		if (debug) {
			displayString(0, "dX = %d", angToDist(nMotorEncoder[motorA])/SCALE);
			displayString(1, "dY = %d", angToDist(nMotorEncoder[motorB])/SCALE);
			displayString(2, "dTot = %d", angToDist(nMotorEncoder[motorA] + nMotorEncoder[motorB])/SCALE);
		}
	}
	motor[motorA] = 0;
	motor[motorB] = 0;
	return;
}

/*
void moveSin(short starti, short startj, short fini, short finj) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	float deltaX = distToAng((finj - startj) * SCALE);
	float deltaY = distToAng((fini - starti) * SCALE);
	float midX = deltaX/2, midY = deltaY/2;
	short xPow, yPow;
	if (deltaX < deltaY) {
		yPow = MAX_M_POW;
		xPow = MAX_M_POW * deltaX/deltaY;
	}
	else {
		xPow = MAX_M_POW;
		yPow = MAX_M_POW * deltaY/deltaX;
	}
	if (deltaX < 0) {
		xPow = -xPow;
	}
	if (deltaY < 0) {
		yPow = -yPow;
	}
	do {
		displayString(0, "dX = %d", angToDist(nMotorEncoder[motorA])/SCALE);
		displayString(1, "dY = %d", angToDist(nMotorEncoder[motorB])/SCALE);
		displayString(2, "dTot = %d", angToDist(nMotorEncoder[motorA] + nMotorEncoder[motorB])/SCALE);
		// increase power linearly to midpoint, then
		// decrease it linearly to finish.
		if (deltaX != 0) {
			motor[motorA] = (-abs(nMotorEncoder[motorA] - midX)/midX + 1) * (xPow - START_POW) + START_POW;
		}
		if (deltaY != 0) {
			motor[motorB] = (-abs(nMotorEncoder[motorB] - midY)/midY + 1) * (yPow - START_POW) + START_POW;
		}
	} while (motor[motorA] > 0 || motor[motorB] > 0);
	motor[motorA] = 0;
	motor[motorB] = 0;
	return;
}
*/

/**********  GENERIC MOVEMENT  **********/
void moveForward() {		// move one space forward
	nMotorEncoder[motorB] = 0;
	float deltaOmega = distToAng(SCALE);
	motor[motorB] = MAX_M_POW;
	while (nMotorEncoder[motorB] < deltaOmega) {}
	motor[motorB] = 0;
}

void moveBackward() {			// move one space backward
	nMotorEncoder[motorB] = 0;
	float deltaOmega = distToAng(-SCALE);
	motor[motorB] = -MAX_M_POW;
	while (nMotorEncoder[motorB] > deltaOmega) {}
	motor[motorB] = 0;
}

void moveRight() {		// move ones space right
	nMotorEncoder[motorA] = 0;
	float deltaOmega = distToAng(SCALE);
	motor[motorA] = MAX_M_POW;
	while (nMotorEncoder[motorA] < deltaOmega) {}
	motor[motorA] = 0;
}

void moveLeft() {			// move one space left
	nMotorEncoder[motorA] = 0;
	float deltaOmega = distToAng(-SCALE);
	motor[motorA] = -MAX_M_POW;
	while (nMotorEncoder[motorA] > deltaOmega) {}
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

/**********  MOVE MAGNET ONLY  **********/

void getinPosition(short ) {}
