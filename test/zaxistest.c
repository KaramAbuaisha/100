void moveZ(bool up) {
	/* Moves the z-axis arm upward or downwards
	   until it encounters resistance. */
	nMotorEncoder[motorC] = 0;
	int prev = -10;
	if (up) {
		motor[motorC] = -30;
	}
	else {
		motor[motorC] = 30;
	}
	while (true) {
		if (abs(nMotorEncoder[motorC] - prev) < 0.1) {
			break;
		}
		prev = nMotorEncoder[motorC];
		wait1Msec(50);
	}
	motor[motorC] = 0;
}

task main()
{
	while (true) {
		if (nNxtButtonPressed == 1) {
			moveZ(true);
		}
		else if (nNxtButtonPressed == 2) {
			moveZ(false);
		}
		wait1Msec(250);
	}
}
