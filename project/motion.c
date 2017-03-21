const float SCALE = 3 * 25.4;		// 3 in/square to millimetres
const float WHEEL_RADIUS = 22.5;		// mm
const float CONVERT = PI / 180 * WHEEL_RADIUS;
const short MAX_M_POW = 80;
const short START_POW = 10;

float angToDist(float angle) {
	return angle * CONVERT;
}

float distToAng(float distance) {
	return distance / CONVERT;
}

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
void magnetUp(){
  
}

void magnetDown(){
  
}

void moveForward(){
  
}

void moveBackward(){
  
}

void moveLeft(){
  
}

void moveRight(){
  
}

void moveDiagonal(int x, int y){

}

//if jump code
void getinPosition(short )

void jump(int currentRow, int currentCol, int toRow, int toCol){
  
  deltaY = toRow - currrentRow;
  deltaX = toCol - currentCol;
  
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
