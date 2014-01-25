#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

void MoveLift(bool down = true, int duration = 0) {
	int speed = LIFT_SPEED;

	// Run longer up than down
	int wait = 3400;
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
void autoBasketRamp(START_SIDE side = RIGHT, FloorColor color) {
	// Start raising the lift so it's ready when we arrive
	StartTask(liftUp);

	// Drive to the IR beacon, recording our distance
	resetDriveEncoder();
	bool validIR = driveToIR(FULL_IMPULSE, 5, 10000);
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
			adjustDistance = FAR_BASKET_OFFSET;
		} else {
			adjustDistance = NEAR_BASKET_OFFSET;
		}

		// We don't turn symetrically, so adjust when we're starting on the left
		if (side == LEFT) {
			adjustDistance += START_LEFT_OFFSET;
		}
	} else {
		adjustDistance = (basketPositions[side][basket] - traveled);
	}
	if (adjustDistance < 0) {
		adjustSpeed *= -1;
	}
	driveToEncoder(adjustSpeed, adjustDistance);

	// Warn if we didn't detect an IR beacon
	if (!validIR) {
		FlashLights(3, 250);
	}
	// Turn to face baskets
	driveToGyro(90, (bool)side);

	// Wait for the lift to be up
	while (!IS_LIFT_UP) {
		wait1Msec(100);
	}

	// Drive to the line, then back off
	driveToColors(QUARTER_IMPULSE, COLOR_TO_BITMAP(BLUE) | COLOR_TO_BITMAP(RED), 2000);
	driveToEncoder(-QUARTER_IMPULSE, -475, 1000);

	// Dump
	DumpHopper();

	// Nudge back slightly
	driveToEncoder(-FULL_IMPULSE, -250);

	// Start lowering the lift
	StartTask(liftDown);

	// Turn back to original orientation
	driveToGyro(90, (!(bool)side));

	// Drive backward to the corner
	// After our turns we lose a bit of distance, so provide a "slop" adjustment
	int reverseSlop = 600;
	if (side == LEFT) {
		reverseSlop = 750;
	}
	driveToEncoder(-FULL_IMPULSE, (-1 * (traveled + adjustDistance - reverseSlop)), 10000);

	// Turn to avoid the ramp
	driveToGyro(110, (bool)side);

	// Drive to white line
	driveToColor(FULL_IMPULSE, WHITE);

	// Turn to ramp
	driveToGyro(100, (!(bool)side));

	// Drive up ramp
	driveToEncoder(FULL_IMPULSE, 7250);
}
#endif
