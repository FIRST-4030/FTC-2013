#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

void MoveLift(bool down = true) {
	int wait = 4100;
	int speed = LIFT_SPEED;

	if (!down) {
		speed *= -1;
		// Run longer up than down
		wait += 800;
	}

	DriveLiftMotor(speed);
	wait1Msec(wait);
	DriveLiftMotor(0);
}

void RaiseLift() {
	MoveLift(false);
}

void DumpHopperByLoweringIt(){
	SetHopperServos(HOPPER_MIN);
}

void PrepareToDump() {
	// Deploy hopper
	// This operation is not instantaneous but the function does return instantly.
	// It takes a couple seconds for the hopper to deploy. Calling this prior to
	// DriveLiftMotor() will allow the hopper to deploy while the lift goes up.
	SetHopperServos(HOPPER_DUMP);

	// Lift
	DriveLiftMotor(-LIFT_SPEED);
	wait1Msec(4500);
	DriveLiftMotor(0);
}

void DumpHopper() {
	SetHopperServos(HOPPER_DUMP);
	wait1Msec(500);
	DriveSpinnerMotor(30);
	wait1Msec(750);
	DriveSpinnerMotor(50);
	wait1Msec(500);
	StopSpinnerMotor();
	SetHopperServos(HOPPER_MAX);
}

void SonarFailed() {
	driveToDistance(1200, HALF_IMPULSE);
	return;
}

void ApproachBasket() {
	int range = USreadDist(sonar);

	// Ensure sonar is sane
	if (range < 10 || range > 100) {
		SonarFailed();
		return;
	}

	// Until all is tested, always use SonarFailed()
	SonarFailed();
	return;

	// Drive forward to set distance
	while(USreadDist(sonar) > 41 ) {
		//runDriveMotors(HALF_IMPULSE,HALF_IMPULSE);
		if(HTIRS2readACDir(IRSeeker) < 5)
			runDriveMotors(QUARTER_IMPULSE,HALF_IMPULSE); // slight left turn
		else
			runDriveMotors(HALF_IMPULSE,QUARTER_IMPULSE); // slight right turn
	}
	stopDriveMotors();
}

// Return true if the provided value is a valid IR seeker value
bool seekerValid(int seeker) {
	if (seeker < 1) {
		return false;
	} else if (seeker > 8) {
		return false;
	}
	return true;
}

bool driveToIR() {
	// Ensure we have a valid IR reading, otherwise return immediately
	int seeker = HTIRS2readACDir(IRSeeker);
	if (!seekerValid(seeker)) {
		FlashLights(5, 200);
		return false;
	}

	// Drive until we are beside the IR beacon, exiting if we lose the IR signal
	while(seeker != 5) {
		runDriveMotors(FULL_IMPULSE,FULL_IMPULSE);
		seeker = HTIRS2readACDir(IRSeeker);
		if (!seekerValid(seeker)) {
			FlashLights(5, 200);
			return false;
		}
	}
	stopDriveMotors();

	// If all went well, return true
	return true;
}

// Start Same as OnFlagLineRightCorner_Basket //
// Turns, finds line, follows line up on ramp and stops //
void FlagLine_FollowLineToRamp(bool reverse = false) {
	// Turn Left Dead Reckoning //
	if (reverse) {
		driveMotors(HALF_IMPULSE,-1 * HALF_IMPULSE, 900);
	} else {
		driveMotors(-1 * HALF_IMPULSE, HALF_IMPULSE, 900);
	}

	// Forward to white line
	driveToColor(WHITE, QUARTER_IMPULSE);

	// Align with white line
	alignLine(WHITE, QUARTER_IMPULSE, BLACK, reverse);

	// Follow line to ramp
	followLineToColor(WHITE, HALF_IMPULSE, BLACK);

	// Rear Light Sensor is Mounted about 2" in front of wheels //
	driveMotors(FULL_IMPULSE, FULL_IMPULSE, 500);
}

void Wall_DirectToRamp() {
	resetDriveEncoder();

	while(readDriveEncoder() < 10000) {
		runDriveMotors(HALF_IMPULSE,HALF_IMPULSE);
	}
}
#endif
