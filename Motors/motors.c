#define WHEEL_MAX (60)
// Store the motor ports for use in drive functions
tMotor driveLeftFront;
tMotor driveLeftRear;
tMotor driveRightFront;
tMotor driveRightRear;
void setDriveMotors(tMotor leftF, tMotor leftR, tMotor rightF, tMotor rightR) {
	driveLeftFront = leftF;
	driveLeftRear = leftR;
	driveRightFront = rightF;
	driveRightRear = rightR;
}

void DriveLeftSide(int power)
{
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
  motor[leftFrontMotor] = power;
	motor[leftRearMotor] = power;
}

void DriveRightSide(int power)
{
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
	motor[rightFrontMotor] = power;
	motor[rightRearMotor] = power;
}


// Run motors at the specified speed indefinately
void runDriveMotors(int left, int right) {
	motor[driveLeftFront]  = left;
	motor[driveLeftRear]  = left;
	motor[driveRightFront] = right;
	motor[driveRightRear] = right;
}

// Stop all drive motion
void stopDriveMotors() {
	runDriveMotors(0, 0);
	wait1Msec(100);
}

// Run motors at the specified speed, stopping after DURATION milliseconds
void driveMotors(int left, int right, const int duration = 0) {
	runDriveMotors(left, right);
	if (duration >= 0) {
		wait1Msec(duration);
	}
}

// Reset the left drive encoder
void resetDriveEncoder() {
	nMotorEncoder[driveRightRear] = 0;
}

int readDriveEncoder() {
	return nMotorEncoder[driveRightRear];
}
