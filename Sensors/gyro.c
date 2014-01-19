#ifndef FTC_GYRO
#define FTC_GYRO

#include "../drivers/hitechnic-gyro.h"

#define GYRO_PERIOD (10)
#define GYRO_FLOAT_SPEED (10.0)
#define GYRO_CAL_SAMPLES (50)

bool GYRO_READY = false;
float GYRO_ANGLE = 0.0;

task gyro() {
	GYRO_READY = false;
	GYRO_ANGLE = 0.0;

	// Calibrate -- assume we are stationary
	float cal = 0.0;
	HTGYROsetCal(gyroSensor, 0);
	for (int i = 0; i < GYRO_CAL_SAMPLES; i++) {
		cal += HTGYROreadRot(gyroSensor);
		wait1Msec(5);
	}
	HTGYROsetCal(gyroSensor, cal / (float)GYRO_CAL_SAMPLES);

	time1[T4] = 0;
	while (true) {

		// Wait in small slices
		while (time1[T4] < GYRO_PERIOD) {
			wait1Msec(1);
		}

		// Immediately reset the timer in case we get de-scheduled
		time1[T4] = 0;

		// Read and integrate
		float speed = HTGYROreadRot(gyroSensor);
		if (abs(speed) < GYRO_FLOAT_SPEED) {
			speed = 0.0;
		}
		GYRO_ANGLE += speed * ((float)GYRO_PERIOD / 1000.0);
		GYRO_READY = true;
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
