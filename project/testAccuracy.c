#include "motion.h"

task main() {
	SensorType[S4] = sensorTouch;

	moveZ(true);
  moveDiagonal(6, 6);
  calibrate();
}
