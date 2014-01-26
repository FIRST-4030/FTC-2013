#ifndef FTC_DRIVE
#define FTC_DRIVE

// Motor Speeds
#define WHEEL_MAX (100)
#define LIFT_SPEED (75)
#define WINCH_SPEED (100)
#define GYRO_SPEED (100)
#define SONAR_SPEED (25)

// Drive until we hit any of the specified parameters
bool driveToParam(int speed, int distance = 0, ColorBitmap colors = 0, int time = 5000, bool turn = false, int ir = 0, int sonar = 0, int gyro = 0) {
	// Stop
	stopDriveMotors();

	// Ensure the time is less than 32k (16-bit timer limit)
	if (time > 32000) {
		time = 32000;
	}

	// Sanity checks -- we need a valid speed and at least one stop paramter (other than time)
	if (speed == 0) {
		return false;
	} else if (distance == 0 && colors == 0 && ir == 0 && sonar == 0 && gyro == 0) {
		return false;
	}

	// Assume the caller was reasonable in matching their signs and bools
	gyro = abs(gyro);
	distance = abs(distance);
	if (gyro != 0) {
		turn = true;
	}

	// Setup the gyro, if requested
	if (gyro != 0) {
		startGyro();
		gyro -= GYRO_OVERRUN;
	}

	// Reset the encoder, gyro, and timer
	resetDriveEncoder();
	resetGyro();
	ClearTimer(T1);

	// Drive straight or turn
	if (turn) {
		runDriveMotors(-speed, speed);
	} else {
		runDriveMotors(speed, speed);
	}

	// Track sensor failures
	bool failed = false;

	// Loop until we hit a stop condition
	while (true) {
		if (colors != 0 && (onColors(colors, readLight(true)) || onColors(colors, readLight(false)))) {
			break;
		} else if (distance != 0 && (abs(readDriveEncoder()) > distance)) {
			break;
		} else if (time != 0 && (time1[T1] > time)) {
			break;
		} else if (ir != 0) {
			int irVal = readIR();

			// Stop if the IR reading is invalid
			if (!irValid(irVal)) {
				failed = true;
				break;
			}

			// Stop when we hit he IR target
			if (ir == irVal) {
				break;
			}
		} else if (sonar != 0) {
			int sonarVal = readSonar();

			// Stop if the sonar reading is invalid
			if (!sonarValid(sonarVal)) {
				failed = true;
				break;
			}

			// Approach when speed is > 0, recede with speed < 0
			if (
				(speed > 0 && (sonarVal < sonar)) ||
				(speed < 0 && (sonarVal > abs(sonar)))
			) {
				break;
			}
		} else if (gyro != 0) {
			// Stop if the gyro reading is invalid
			if (!gyroValid()) {
				failed = true;
				break;
			}

			// Turn until we exceed the requested (absolute) angle
			int angle = abs(readGyro());
			if (angle > gyro) {
				break;
			}
		}
	}

	// Always stop for just a moment when we're done
	stopDriveMotors();

	// Stop the gyro, if we started it
	if (gyro != 0) {
		StopTask(gyro);
	}

	// Return false if there was a sensor error
	return !failed;
}

// Shorthand for IR-based driving
bool driveToIR(int speed, int ir, int time = 5000) {
	return driveToParam(speed, 0, 0, time, false, ir, 0, 0);
}

// Shorthand for sonar-based driving
bool driveToSonar(int sonar, int time = 5000) {
	int speed = SONAR_SPEED;
	if (sonar < 0) {
		speed *= -1;
	}
	return driveToParam(speed, 0, 0, time, false, 0, sonar, 0);
}

// Shorthand for distance-based driving
void driveToEncoder(int speed, int distance, int time = 5000) {
	driveToParam(speed, distance, 0, time, false, 0, 0, 0);
}

// Shorthand for gyro-based driving
bool driveToGyro(int degrees, bool left = true, int time = 5000) {
	int speed = GYRO_SPEED;
	if (!left) {
		speed *= -1;
		degrees *= -1;
	}
	return driveToParam(speed, 0, 0, time, true, 0, 0, degrees);
}

// Shorthand for multi-color-based driving
void driveToColors(int speed, ColorBitmap colors, int time = 5000) {
	driveToParam(speed, 0, colors, time, false, 0, 0, 0);
}

// Shorthand for color-based driving
void driveToColor(int speed, FloorColor color, int time = 5000) {
	driveToColors(speed, COLOR_TO_BITMAP(color), time);
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
