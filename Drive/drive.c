// Drive until we exceed the specified distance
void driveToDistance(int distance, int speed) {
	// Sanity check
	if (distance == 0) {
		return;
	}

	// Reset the encode and start driving
	resetDriveEncoder();
	runDriveMotors(speed, speed);

	// Loop until we hit a stop condition
	while (true) {
		if (distance > 0 && readDriveEncoder() > distance) {
			break;
		} else if (distance < 0 && readDriveEncoder() < distance) {
			break;
		}
	}

	// Always stop when we're done
	stopDriveMotors();
}

// Drive until we hit the specified color
void driveToColor(FloorColor color, int speed) {
	while (!onColor(color, LSvalRaw(lineLeft)) && !onColor(color, LSvalRaw(lineRight))) {
		runDriveMotors(speed, speed);
	}
	stopDriveMotors();
}
