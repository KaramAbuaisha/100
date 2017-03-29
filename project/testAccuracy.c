#include "motion.h"

task main() {
	SensorType[S4] = sensorTouch;
	calibrate();
  moveDiagonal(7, 7);
}
