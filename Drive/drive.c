#ifndef FTC_DRIVE
#define FTC_DRIVE

#define BLIPS_PER_DEGREE (2900.0 / 90.0)

// Motor Speeds //
#define WHEEL_MAX (100)
#define LIFT_SPEED (75)
#define WINCH_SPEED (100)

// Drive until we exceed the specified distance
void driveToDistance(int distance, int speed) {
	// Sanity check
	if (distance == 0) {
		return;
	}

	// Ensure the distance and the speed have the same sign
	if ((speed < 0 && distance > 0) || (speed > 0 && distance < 0)) {
		distance *= -1;
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
	wait1Msec(100);
}

// Drive to target encoder value
void driveToTargetValue(int target, int speed)
{
	driveToDistance(target-readDriveEncoder(),speed);
}

void driveToNearestBasket(int speed)
{
	int enVal = readDriveEncoder();
	// B1 = 3000		2500
		// div = 3600
	// B2 = 4400
		// div = 5700
	// B3 = 7000
		// div 7700
	// B4 = 8400
	if(enVal < 3600)
		driveToTargetValue(3000,speed);
	else if(enVal < 5700)
		driveToTargetValue(4400,speed);
	else if(enVal < 7700)
		driveToTargetValue(7000,speed);
	else
		driveToTargetValue(8400,speed);
}

void turnInPlace(int distance, int speed, bool left = true) {
	// Sanity check
	if (distance == 0) {
		return;
	}

	// Turn right if requested
	if (!left) {
		speed *= -1;
		distance *= -1;
	}

	// Reset the encode and start driving
	resetDriveEncoder();
	runDriveMotors(-speed, speed);

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

void turnInPlaceDegrees(int degrees, int speed, bool left = true) {
	turnInPlace((BLIPS_PER_DEGREE * (float)degrees), speed, left);
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

void StopSpinnerMotor() {
	motor[spinnerMotor] = 0;
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
