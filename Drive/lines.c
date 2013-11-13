// Store the light sensor ports for use in line functions
tSensors lineLeft  = null;
tSensors lineRight = null;
void setLineSensors(tSensors left, tSensors right) {
	lineLeft  = left;
	lineRight = right;
}

// Follow a line, after we've been aligned to it, stopping when we hit the STOP color
void followLineToColor(FloorColor color, int speed, FloorColor stop) {
	_folowLine(color, speed, stop, 0, 0);
}

// Follow a line, after we've been aligned to it, stopping based on color, distance, or time
void _followLine(FloorColor color, int speed, FloorColor stopColor, int stopDistance, int stopTime) {
	// Reset the drive encoder if we're going to use it
	if (stopDistance != 0) {
		resetDriveEncoder();
	}
	
	// Loop until we hit a stop condition
	while (true) {
		if (stopColor != UNKNOWN && (onColor(stop, LSvalRaw(lineLeft)) || onColor(stop, LSvalRaw(lineRight)))) {
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

// Align to a line, assuming we start at or just beyond it
void alignLine(FloorColor color, int speed) {
	_alignLine(color, speed, UNKNOWN);
}

// Align to a line, assuming we start at or just beyond it, but stop if we hit the STOP color with either sensor
void _alignLine(FloorColor color, int speed, FloorColor stop) {
	
	// When the right sensor is on the line, we're aligned
	while(!onColor(color, LSvalRaw(lineRight))) {
		
		// Stop alignment efforts if we hit the specified stop floor color
		if (stop != UNKNOWN && (onColor(stop, LSvalRaw(lineLeft)) || onColor(stop, LSvalRaw(lineRight)))) {
			break;
		}

		// Move forward while the left sensor is on the line
		while(onColor(color, LSvalRaw(lineLeft))) {
			runDriveMotors(speed, speed);
		}

		// Turn clockwise (right) when neither sensor is on the line
		while(!onColor(color, LSvalRaw(lineLeft)) && !onColor(color, LSvalRaw(lineRight))) {
			runDriveMotors(speed, 0);
		}
	}
	
	// Always stop when we're done
	stopDriveMotors();
}
