// Store the light sensor ports for use in line functions
tSensors lightLeft  = null;
tSensors lightRight = null;
void setLightSensors(tSensors left, tSensors right) {
	lightLeft  = left;
	lightRight = right;
}

// Follow a line, after we've been aligned to it
void FollowLine(FloorColor color, int speed) {
	if(onColor(color, LSvalRaw(lightLeft))) {
		runMotors(0, speed);
	} else if(onColor(color, LSvalRaw(lightRight))) {
		driveMotors(speed, 0);
	} else {
		driveMotors(speed, speed);
	}
}

// Align to a line, assuming we start at or just beyond it
void alignLine(FloorColor color, int speed) {
	alignLineStop(color, speed, UNKNOWN);
}

// Align to a line, assuming we start at or just beyond it, but stop if we hit the STOP color with either sensor
void alignLineStop(FloorColor color, int speed, FloorColor stop) {
	
	// When the right sensor is on the line, we're aligned
	while(!onColor(color, LSvalRaw(lightRight))) {
		
		// Stop alignment efforts if we hit the specified stop floor color
		if (stop != UNKONWN && (onColor(stop, LSvalRaw(lightLeft)) || onColor(stop, LSvalRaw(lightRight)))) {
			break;
		}

		// Move forward while the left sensor is on the line
		while(onColor(color, LSvalRaw(lightLeft))) {
			runMotors(speed, speed);
		}

		// Turn clockwise (right) when neither sensor is on the line
		while(!onColor(color, LSvalRaw(lightLeft)) && !onColor(color, LSvalRaw(lightRight))) {
			runMotors(speed, 0);
		}
	}
}
