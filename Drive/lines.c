#ifndef FTC_LINES
#define FTC_LINES

#include "../Sensors/light.c"

// Follow a line, after we've been aligned to it, stopping based on color, distance, or time
void _followLine(FloorColor color, int speed, FloorColor stopColor, int stopDistance, int stopTime) {
	// Reset the drive encoder if we're going to use it
	if (stopDistance != 0) {
		resetDriveEncoder();
	}

	// Loop until we hit a stop condition
	while (true) {
		if (stopColor != UNKNOWN && (onColor(stopColor, LSvalRaw(lineRight)))) {
			break;
		} else if (stopDistance > 0 && readDriveEncoder() > stopDistance) {
			break;
		} else if (stopDistance < 0 && readDriveEncoder() < stopDistance) {
			break;
		} else if (stopTime > 0 && true) {
			// Can we check elapsed time?
			break;
		}

		if (onColor(color, LSvalRaw(lineLeft))) {
			runDriveMotors(0, speed);
		} else if (onColor(color, LSvalRaw(lineRight))) {
			runDriveMotors(speed, 0);
		} else {
			runDriveMotors(speed, speed);
		}
	}

	// Always stop when we're done
	stopDriveMotors();
}

// Follow a line, after we've been aligned to it, stopping when we hit the STOP color
void followLineToColor(FloorColor color, int speed, FloorColor stop) {
	_followLine(color, speed, stop, 0, 0);
}

// Follow a line, after we've been aligned to it, stopping when we hit the STOP color
void followLineToDistance(FloorColor color, int speed, int stop) {
	_followLine(color, speed, 0, stop, 0);
}

// Align to a line, assuming we start at or just beyond it, but stop if we hit the STOP color with either sensor
void alignLine(FloorColor color, int speed, FloorColor stop = UNKNOWN, bool reverse = false) {

	// Spin ~180 if we've been asked to align in reverse
	if (reverse) {
		// Nudge forward
		runDriveMotors(100, 100);
		wait1Msec(150);

		// Spin in place
		runDriveMotors(100, -100);
		wait1Msec(1500);
		stopDriveMotors();
	}

	// Start our turn to get the front sensor on the line
	while(!onColor(color, LSvalRaw(lineLeft))) {

		// Stop alignment efforts if we hit the specified stop floor color
		if (stop != UNKNOWN && (onColor(stop, LSvalRaw(lineRight)) || onColor(stop, LSvalRaw(lineLeft)))) {
			break;
		}

		// Turn in place
		runDriveMotors(speed, -1 * speed);
	}
	stopDriveMotors();

	// When the back sensor is on the line, we're aligned
	while(!onColor(color, LSvalRaw(lineRight))) {

		// Stop alignment efforts if we hit the specified stop floor color
		if (stop != UNKNOWN && (onColor(stop, LSvalRaw(lineRight)) || onColor(stop, LSvalRaw(lineLeft)))) {
			break;
		}

		// Drive forward until the front sensor is clear of the line
		// TODO: Adjust onColor to provide more useful results, so we can invert this test
		if (!onColor(GREY, LSvalRaw(lineLeft))) {
			runDriveMotors(speed, speed);

		// Turn while neither sensor is on the line
		} else if (!onColor(color, LSvalRaw(lineRight)) && !onColor(color, LSvalRaw(lineLeft))) {
				runDriveMotors(speed, 0);
		}
	}

	// Always stop when we're done
	stopDriveMotors();
}


#endif
