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

//Added code from MainController for controlling motors other than the wheels
void DriveSpinnerMotor(int power)
{
	motor[spinnerMotor] = power;
}

void DriveFlagMotor(int power)
{
	motor[flagMotor] = power;
}

void DriveWinchMotors(int power)
{
	motor[leftWinch] = power;
	motor[rightWinch] = power;
}

void DriveLiftMotor(int power)
{
	motor[liftMotor] = power;
}
