#define LIGHT_SENSOR_PORT_TYPE tMUXSensor
//#define LIGHT_SENSOR_PORT_TYPE tSensors

// Store the light sensor ports for use in line functions
LIGHT_SENSOR_PORT_TYPE lineLeft;
LIGHT_SENSOR_PORT_TYPE lineRight;
void setLineSensors(LIGHT_SENSOR_PORT_TYPE left, LIGHT_SENSOR_PORT_TYPE right) {
	lineLeft  = left;
	lineRight = right;
}

// Follow a line, after we've been aligned to it, stopping based on color, distance, or time
void _followLine(FloorColor color, int speed, FloorColor stopColor, int stopDistance, int stopTime) {
	// Reset the drive encoder if we're going to use it
	if (stopDistance != 0) {
		resetDriveEncoder();
	}

	// Loop until we hit a stop condition
	while (true) {
		if (stopColor != UNKNOWN && (onColor(stopColor, LSvalRaw(lineLeft)) || onColor(stopColor, LSvalRaw(lineRight)))) {
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
void _alignLine(FloorColor color, int speed, FloorColor stop, bool reverse) {

	// Map sensors and speed to "front" and "back" based on the reverse switch
	LIGHT_SENSOR_PORT_TYPE front = lineLeft;
	LIGHT_SENSOR_PORT_TYPE back  = lineRight;
	if (reverse) {
		LIGHT_SENSOR_PORT_TYPE front = lineLeft;
		LIGHT_SENSOR_PORT_TYPE back  = lineRight;
		speed *= -1;
	}

	// Start our turn to get the front sensor back on the line
	while(!onColor(color, LSvalRaw(front))) {
		runDriveMotors(speed, -1 * speed);
	}
	stopDriveMotors();

	// When the back sensor is on the line, we're aligned
	while(!onColor(color, LSvalRaw(back))) {

		// Stop alignment efforts if we hit the specified stop floor color
		if (stop != UNKNOWN && (onColor(stop, LSvalRaw(front)) || onColor(stop, LSvalRaw(back)))) {
			break;
		}

		// Move forward while the left sensor is on the line
		while(onColor(color, LSvalRaw(front))) {
			runDriveMotors(speed, speed);
		}
		stopDriveMotors();

		// Turn clockwise (right) when neither sensor is on the line
		while(!onColor(color, LSvalRaw(front)) && !onColor(color, LSvalRaw(back))) {
			runDriveMotors(speed, 0);
		}
		stopDriveMotors();
	}

	// Always stop when we're done
	stopDriveMotors();
}

// Align to a line, assuming we start at or just beyond it
void alignLine(FloorColor color, int speed) {
	_alignLine(color, speed, UNKNOWN, false);
}
