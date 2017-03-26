const int POW = 50;
const int DELTA_T = 25;

float speed(short motorN) {
	nMotorEncoder[motorN] = 0;
	wait1Msec(DELTA_T);
	return (nMotorEncoder[motorN] / (DELTA_T / 1000));
}

task main() {
	top:
	while (nNxtButtonPressed != 3) {
		if (nNxtButtonPressed == 1) {
			motor[motorA] = POW;
		}
		else if (nNxtButtonPressed == 2) {
			motor[motorA] = -POW;
		}
		displayString(0, "SPEED = %f", speed(motorA))
	}
	while (nNxtButtonPressed != 3) {
		if (nNxtButtonPressed == 1) {
			motor[motorB] = POW;
		}
		else if (nNxtButtonPressed == 2) {
			motor[motorB] = -POW;
		}
		displayString(0, "SPEED = %f", speed(motorB))
	}
	goto top;
}