const float SCALE = 3 * 25.4;		// 3 in/square to millimetres
const float WHEEL_RADIUS = 22.5;		// mm
const float CONVERT = PI / 180 * WHEEL_RADIUS;
const short MAX_M_POW = 80;
const short START_POW = 10;

float angToDist(float angle, float c = CONVERT);
float distToAng(float distance, float c = CONVERT);
void move(short starti, short startj, short fini, short finj);
/* assuming that the motor starts at coordinates
   starti and startj, move it to fini and finj.*/

task main()
{
	//short board[8][8];
	while (nNxtButtonPressed == -1) {}
	while (nNxtButtonPressed != -1) {}

	// user input
	short targetX = 0, targetY = 0;

	while (nNxtButtonPressed != 3) {
		eraseDisplay();
		displayString(0, "ENTER TARGET X: ");
		if (nNxtButtonPressed == 1 && targetX < 10) {
			targetX++;
		}
		else if (nNxtButtonPressed == 2 && targetX > -10) {
			targetX--;
		}
		displayString(1, "%d", targetX);
		wait1Msec(250);
	}

	while (nNxtButtonPressed == 3) {}
	while (nNxtButtonPressed != 3) {
		eraseDisplay();
		displayString(2, "ENTER TARGET Y: ");
		if (nNxtButtonPressed == 1 && targetY < 10) {
			targetY++;
		}
		else if (nNxtButtonPressed == 2 && targetY > -10) {
			targetY--;
		}
		displayString(3, "%d", targetY);
		wait1Msec(250);
	}
	eraseDisplay();
	move(0, 0, targetY, targetX);
	eraseDisplay();
	displayString(0, "DONE");
	while (nNxtButtonPressed == -1) {}
	while (nNxtButtonPressed != -1) {}
}

float angToDist(float angle, float c) {
	return angle * c;
}

float distToAng(float distance, float c) {
	return distance / c;
}

void move(short starti, short startj, short fini, short finj) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	float deltaX = distToAng((finj - startj) * SCALE);
	float deltaY = distToAng((fini - starti) * SCALE);
	float midX = deltaX/2, midY = deltaY/2;
	float deltaTot = deltaX + deltaY;
	short xPow, yPow;
	if (deltaX < deltaY) {
		yPow = MAX_M_POW;
		xPow = MAX_M_POW * deltaX/deltaY;
	}
	else {
		xPow = MAX_M_POW;
		yPow = MAX_M_POW * deltaY/deltaX;
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
