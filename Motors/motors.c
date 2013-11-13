// Store the motor ports for use in drive functions
tMotor driveLeft  = null;
tMotor driveRight = null;
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
	runMotors(0, 0);
}

// Run motors at the specified speed, stopping after DURATION milliseconds
void driveMotors(int left, int right, const int duration) {
	runMotors(left, right);
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
