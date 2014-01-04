#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

void MoveLift(bool down = true, int duration = 0) {
	int speed = LIFT_SPEED;

	// Run longer up than down
	int wait = 3800;
	if (!down) {
		speed *= -1;
		wait += 800;
	}

	// Respect a specific run duration, if provided
	if (duration > 0) {
		wait = duration;
	}

	// Run the lift
	DriveLiftMotor(speed);
	wait1Msec(wait);
	DriveLiftMotor(0);
}

void DumpHopper() {
	SetHopperServos(HOPPER_DUMP);
	wait1Msec(500);
	DriveSpinnerMotor(30);
	wait1Msec(500);
	DriveSpinnerMotor(50);
	wait1Msec(250);
	StopSpinnerMotor();
	SetHopperServos(HOPPER_MAX);
}

void SonarFailed() {
	driveToDistance(50, HALF_IMPULSE);
	return;
}

void ApproachBasket() {
	int range = USreadDist(sonarSensor);

	// Ensure sonar is sane
	if (range < 10 || range > 100) {
		SonarFailed();
		return;
	}

	// Until all is tested, always use SonarFailed()
	SonarFailed();
	return;

	// Drive forward to set distance
	while(USreadDist(sonarSensor) > 41 ) {
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

void Wall_DirectToRamp() {
	resetDriveEncoder();

	while(readDriveEncoder() < 10000) {
		runDriveMotors(HALF_IMPULSE,HALF_IMPULSE);
	}
}

// Tasks for background lift movement
bool IS_LIFT_UP = false;
task liftUp() {
	IS_LIFT_UP = false;
	MoveLift(false);
	IS_LIFT_UP = true;
}
task liftDown() {
	IS_LIFT_UP = true;
	MoveLift(true);
	IS_LIFT_UP = false;
}

// Drive to the IR beacon, dump in the basket, return to start, drive up ramp
void autoBasketRamp(START_SIDE side = RIGHT) {
	// Start raising the lift so it's ready when we arrive
	StartTask(liftUp);

	// Drive to the IR beacon, recording our distance
	resetDriveEncoder();
	bool validIR = driveToIR();
	int traveled = readDriveEncoder();

	// Figure out which basket we're at
	// If we didn't get a valid IR run, prefer the 1st basket
	int basket = 0;
	if (validIR) {
		// If nothing matches we're at the first basket, so default to 0 if IR is valid
		basket = 0;
		for (int i = NUM_BASKETS - 1; i > 0; i--) {
			// Since the sensor is behind the midpoint we should always overshoot
			if (traveled >= basketPositions[side][i]) {
				basket = i;
				break;
			}
		}
	}

	// Adjust back to the correct turn point for the selected basket
	int adjustSpeed = HALF_IMPULSE;
	int adjustDistance = 0;
	// In theory we can just drive to the basket position but our encoder
	// is pretty sloppy, so put more trust in the IR when available
	if (validIR) {

		// Back up a bit to get aligned -- alignment varies between baskets 1/2 and 3/4
		if (basket > 1) {
			adjustDistance = -700;
		} else {
			adjustDistance = -100;
		}

		// We don't turn symetrically, so adjust when we're starting on the left
		if (START_SIDE == LEFT) {
			adjustDistance += 400;
		}
	} else {
		adjustDistance = (basketPositions[side][basket] - traveled);
	}
	if (adjustDistance < 0) {
		adjustSpeed *= -1;
	}
	driveToDistance(adjustDistance, adjustSpeed);

	// Warn if we didn't detect an IR beacon
	if (!validIR) {
		FlashLights(5, 200);
	}
	// Turn to face baskets
	turnInPlaceDegrees(90, HALF_IMPULSE, (bool)side);

	// Wait for the lift to be up
	while (!IS_LIFT_UP) {
		wait1Msec(100);
	}

	// Move forward to basket
	ApproachBasket();

	// Dump
	DumpHopper();

	// Nudge back for safety
	driveToDistance(-400, -FULL_IMPULSE);

	// Star lowering the lift
	StartTask(liftDown);

	// Turn back to original orientation
	turnInPlaceDegrees(90, FULL_IMPULSE, (!(bool)side));

	// Drive backward to the corner
	driveToDistance((-1 * (traveled + adjustDistance)), -FULL_IMPULSE);

	// Drive back some more to get aligned with the wall
	driveToDistance(-3000, -FULL_IMPULSE);

	// Turn to avoid ramp
	turnInPlaceDegrees(70, FULL_IMPULSE, (bool)side);

	// Drive to white line
	driveToColor(WHITE, FULL_IMPULSE);

	// Turn to ramp
	turnInPlaceDegrees(95, FULL_IMPULSE);

	// Drive up ramp
	driveToDistance(8000, FULL_IMPULSE);
}
#endif
