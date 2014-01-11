#ifndef FTC_SONAR
#define FTC_SONAR

#include "../drivers/lego-ultrasound.h"

int readSonar() {
	return USreadDist(sonarSensor);
}

bool sonarValid(int val) {
	if (val < 10) {
		return false;
	} else if (val > 1000) {
		return false;
	}
	return true;
}

#endif
