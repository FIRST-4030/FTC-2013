// Store the motor ports for use in drive functions
tMotor driveLeft;
tMotor driveRight;
void setDriveMotors(tMotor left, tMotor right) {
	driveLeft  = left;
	driveRight = right;
}

// Run motors at the specified speed indefinately
void runDriveMotors(int left, int right) {
	motor[driveLeft]  = left;
	motor[driveRight] = right;
}

// Stop all drive motion
void stopDriveMotors() {
	runDriveMotors(0, 0);
	wait1Msec(100);
}

// Run motors at the specified speed, stopping after DURATION milliseconds
void driveMotors(int left, int right, const int duration) {
	runDriveMotors(left, right);
	if (duration >= 0) {
		wait1Msec(duration);
	}
}

// Reset the left drive encoder
void resetDriveEncoder() {
	nMotorEncoder[driveLeft] = 0;
}

int readDriveEncoder() {
	return nMotorEncoder[driveLeft];
}
