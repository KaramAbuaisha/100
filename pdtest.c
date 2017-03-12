const float WHEEL_RADIUS = 22.5;		// mm
const float CONVERT = PI / 180 * WHEEL_RADIUS;

float angToDist(float angle) {
	return angle * CONVERT;
}

float distToAng(float distance) {
	return distance / CONVERT;
}

void move(float distance, int power) {
	/* Simply runs motor at set power until
	   correct distance is reached */
	nMotorEncoder[motorA] = 0;
	distance = distToAng(distance);
	motor[motorA] = power;
	while (nMotorEncoder[motorA] < distance) {}
	motor[motorA] = 0;
	return;
}

void gradMove(float distance, int maxPow, int startPow) {
	/* Increases motor power linearly up to the
	   midpoint then linearly decreases it until
	   the correct distance is reached */
	int currentPos = 0, power = 0;

	nMotorEncoder[motorA] = 0;
	distance = distToAng(distance);
	float mid = distance / 2;

	while (currentPos < distance) {
		currentPos = nMotorEncoder[motorA];
		power = (-abs(currentPos - mid)/mid + 1) * (maxPow - startPow) + startPow;
		displayString(0, "pos = %d", angToDist(currentPos));
		displayString(1, "powr = %d", power);
		motor[motorA] = power;
	}
	motor[motorA] = 0;
}

void movePD(float distance, float kp, float kd) {
	/* Moves the motor a certain distance with a
	   PD controller. kp and kd are gains for the
	   proportional and differential parts. */
	nMotorEncoder[motorA] = 0;
	distance = distToAng(distance);

	float error = distance, prevError;
	while (nMotorEncoder[motorA] < distance) {
		prevError = error;
		error = distance - nMotorEncoder[motorA];

		displayString(0, "prevErr = %f", prevError);
		displayString(1, "err = %f", error);
		displayString(2, "dEnc = %d", nMotorEncoder[motorA]);
		displayString(3, "prop = %f", kp * error);
		displayString(4, "deriv = %f", kd * (error - prevError));
		displayString(5, "power = %f", kp * error + kd * (error - prevError));

		motor[motorA] = kp * error + kd * (error - prevError);
		wait1Msec(10);
	}
	motor[motorA] = 0;
}

task main()
{
	movePD(500, 1, 2);
}
