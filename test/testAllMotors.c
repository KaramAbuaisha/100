const int POW = 50;

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
	start:
	while (nNxtButtonPressed != 3) {
		eraseDisplay();
		displayString(0, "X AXIS");
		if (nNxtButtonPressed == 1) {
			displayString(1, "+VE POWER");
			motor[motorA] = POW;
		}
		else if (nNxtButtonPressed == 2) {
			displayString(1, "-VE POWER");
			motor[motorA] = -POW;
		}
		while (nNxtButtonPressed != -1) {}
		motor[motorA] = 0;
	}
	while (nNxtButtonPressed != -1) {}
	while (nNxtButtonPressed != 3) {
		eraseDisplay();
		displayString(0, "Y AXIS");
		if (nNxtButtonPressed == 1) {
			displayString(1, "+VE POWER");
			motor[motorB] = POW;
		}
		else if (nNxtButtonPressed == 2) {
			displayString(1, "-VE POWER");
			motor[motorB] = -POW;
		}
		while (nNxtButtonPressed != -1) {}
		motor[motorB] = 0;
	}
	while (nNxtButtonPressed != -1) {}
	while (nNxtButtonPressed != 3) {
		eraseDisplay();
		displayString(0, "Z AXIS");
		if (nNxtButtonPressed == 1) {
			displayString(1, "+VE POWER");
			moveZ(true);
		}
		else if (nNxtButtonPressed == 2) {
			displayString(1, "-VE POWER");
			moveZ(false);
		}
	}
	while (nNxtButtonPressed != -1) {}
	goto start;
}
