#ifndef FTC_DRIVE
#define FTC_DRIVE


// Motor Speeds //
#define WHEEL_MAX (75)
#define LIFT_SPEED (100)
#define WINCH_SPEED (100)

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

// Direct Drive Functions //
void DriveLeftSide(int power) {
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
  motor[leftFrontMotor] = power;
	motor[leftRearMotor] = power;
}

void DriveRightSide(int power) {
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
	motor[rightFrontMotor] = power;
	motor[rightRearMotor] = power;
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

#endif
