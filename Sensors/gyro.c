#ifndef FTC_GYRO
#define FTC_GYRO

#define GYRO_PERIOD (20)
#include "../drivers/hitechnic-gyro.h"

float GYRO_ANGLE = 0.0;

task gyro() {
	GYRO_ANGLE = 0.0;
	HTGYROstartCal(gyroSensor);
	wait1Msec(100);

	time1[T1] = 0;
	while (true) {

		// Wait 20ms in small slices
		while (time1[T4] < GYRO_PERIOD) {
			wait1Msec(1);
		}

		// Immediately reset the timer in case we get de-scheduled
		time1[T1] = 0;

		// Read and integrate
		float speed = HTGYROreadRot(gyroSensor);
		GYRO_ANGLE += speed * (GYRO_PERIOD / 1000.0);
	}
}

float rawReadGyro() {
	return HTGYROreadRot(gyroSensor);
}

void resetGyro() {
	GYRO_ANGLE = 0;
}

float readGyro() {
	return GYRO_ANGLE;
}

#endif
