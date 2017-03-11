const float scale = 3 * 25.4;		// 3 in/square to millimetres
const float wheelRadius = 22.5;		// mm
const float convert = PI / 180 * wheelRadius;
const short maxMPow = 20;

float angToDist(float angle, float c = convert);
float distToAng(float distance, float c = convert);
void move(short starti, short startj, short fini, short finj, short maxPow = maxMPow, float sc = scale);

task main()
{
	//short board[8][8];
	while (nNxtButtonPressed == -1) {}
	while (nNxtButtonPressed != -1) {}
	move(0, 0, 2, 4);
	while (nNxtButtonPressed == -1) {}
	while (nNxtButtonPressed != -1) {}
}

float angToDist(float angle, float c) {
	return angle * c;
}

float distToAng(float distance, float c) {
	return distance / c;
}

void move(short starti, short startj, short fini, short finj, short maxPow, float sc) {
	nMotorEncoder[motorA] = 0;		// x
	nMotorEncoder[motorB] = 0;		// y
	float deltaX = distToAng((finj - startj) * sc);
	float deltaY = distToAng((fini - starti) * sc);
	float deltaTot = deltaX + deltaY;
	if (deltaX < deltaY) {
		motor[motorB] = maxPow;		// longer y, greater power
		motor[motorA] = maxPow * deltaX/deltaY;	// shorter x, less power
	}
	else {
		motor[motorA] = maxPow;
		motor[motorB] = maxPow * deltaY/deltaX;
	}
	while (nMotorEncoder[motorA] + nMotorEncoder[motorB] < deltaTot) {
		displayString(0, "dX = %d", angToDist(nMotorEncoder[motorA])/sc);
		displayString(1, "dY = %d", angToDist(nMotorEncoder[motorB])/sc);
		displayString(2, "dTot = %d", angToDist(nMotorEncoder[motorA] + nMotorEncoder[motorB])/sc);
	}
	motor[motorA] = 0;
	motor[motorB] = 0;
}
