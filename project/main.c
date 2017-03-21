//#include <algorithm.c>
//#include <motion.c>
const float WHEEL_RADIUS = 21.1;

task main() {
	float distance = 50 / WHEEL_RADIUS * 180 / PI;

	nMotorEncoder[motorA] = 0;
	motor[motorA] = -50;
	while (abs(nMotorEncoder[motorA])*1.125 < abs(distance)) {}
	motor[motorA] = 0;
	displayString(0, "DIST (MM) = %f", nMotorEncoder[motorA] * PI / 180 * WHEEL_RADIUS);
	while (nNxtButtonPressed == -1) {}

	/*
	TODO:
	- Create sin function to move motor:
	- At present:
}
