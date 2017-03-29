#include "motion.h"

task main() {
	SensorType[S4] = sensorTouch;
	for (int i=1; i<8; i++){
		moveZ(true);
  	moveDiagonal(i,i);
  	calibrate();
	}
}
