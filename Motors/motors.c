// Store the motor ports for use in drive functions
tMotor driveLeft  = null;
tMotor driveRight = null;
void setMotors(tMotor left, tMotor right) {
	driveLeft  = left;
	driveRight = right;
}

// Run motors at the specified speed indefinately
void runMotors(int left, int right) {
	motor[driveLeft]  = left;
	motor[driveRight] = right;	
}

// Run motors at the specified speed, stopping after DURATION milliseconds
void driveMotors(int left, int right, const int duration) {
	runMotors(left, right);
	if (duration >= 0) {
		wait1Msec(duration);
	}
}