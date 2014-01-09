#ifndef FTC_DRIVE
#define FTC_DRIVE

#define TURN_DEGREE_SPEED (75)
#define BLIPS_PER_DEGREE (2650.0 / 90.0)

// Motor Speeds //
#define WHEEL_MAX (100)
#define LIFT_SPEED (75)
#define WINCH_SPEED (100)

// Drive until we hit any of the specified parameters
void driveToParam(int speed, int distance = 0, FloorColor color = UNKNOWN, int time = 5000, bool turn = false) {
	// Ensure the time is less than 32k (16-bit timer limit)
	if (time > 32000) {
		time = 32000;
	}

	// Sanity checks -- we need a valid speed and at least one stop paramter
	if (speed == 0) {
		return;
	} else if (distance == 0 && color == UNKNOWN && time == 0) {
		return;
	}

	// Assume the sign of our speed and distance match (they must to be sane)
	distance = abs(distance);

	// Reset the encoder and timer
	resetDriveEncoder();
	ClearTimer(T1);

	// Drive straight or turn
	if (turn) {
		runDriveMotors(-speed, speed);
	} else {
		runDriveMotors(speed, speed);
	}

	// Loop until we hit a stop condition
	while (true) {
		if (color != UNKNOWN && (onColor(color, LSvalRaw(lineLeft)) || onColor(color, LSvalRaw(lineRight)))) {
			break;
		} else if (distance != 0 && (abs(readDriveEncoder()) > distance)) {
			break;
		} else if (time != 0 && (time1[T1] > time)) {
			break;
		}
	}

	// Always stop for just a moment when we're done
	stopDriveMotors();
	wait1Msec(50);
}

// Shorthand for distance-based driving
void driveToDistance(int speed, int distance, int time = 5000) {
	driveToParam(speed, distance, UNKNOWN, time, false);
}

// Shorthand for in-place turns
void turnInPlace(int speed, int distance, bool left = true, int time = 5000) {
	// Turn right if requested
	if (!left) {
		speed *= -1;
		distance *= -1;
	}
	driveToParam(speed, distance, UNKNOWN, time, true);
}

// Translate via BLIPS_PER_DEGREE for ease-of-use
void turnInPlaceDegrees(int degrees, bool left = true, int time = 5000) {
	turnInPlace(TURN_DEGREE_SPEED, (BLIPS_PER_DEGREE * (float)degrees), left, time);
}

// Drive until we hit the specified color
void driveToColor(int speed, FloorColor color, int time = 0) {
	driveToParam(speed, 0, color, time, false);
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
	DriveSpinnerMotor(0);
}

void DriveFlagMotor(int power)
{
	motor[flagMotorA] = power;
	motor[flagMotorB] = power;
}

void StopFlagMotor() {
	DriveFlagMotor(0);
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
