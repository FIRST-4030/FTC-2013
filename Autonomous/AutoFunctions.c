void dump() {
	// Lift
	DriveLiftMotor(-FULL_IMPULSE);
	wait1Msec(5000);
	DriveLiftMotor(0);

	// Drive forward to set distance
	while(USreadDist(sonar) > 41) {
		runDriveMotors(QUARTER_IMPULSE, QUARTER_IMPULSE);
	}
	stopDriveMotors();

	// Deploy hopper
	SetHopperServos(HOPPER_MIN);

	// Unload
	DriveSpinnerMotor(HALF_IMPULSE);
	wait1Msec(2000);
	DriveSpinnerMotor(0);
}


// Start the robot with the back right wheel touching the wall and the right wheels lined up with the flag line.
// Face the robot along the flag line.
void OnFlagLineRightCorner_Basket()  //Add a bool variable that can be passed and call Wait?
{

	// Count distance from our starting point
	resetDriveEncoder();

	// IR failed -- static drive (i.e. hope)
	if(HTIRS2readACDir(IRSeeker) == 0) {

		// Forward left for 0.5 seconds
		runDriveMotors(HALF_IMPULSE, FULL_IMPULSE);
		wait1Msec(500);
		stopDriveMotors();

		// Forward for 0.5 seconds
		runDriveMotors(FULL_IMPULSE, FULL_IMPULSE);
		wait1Msec(500);
		stopDriveMotors();

		// Nothing more to do but hope
		return;
	}

	// Start timing our drive
	ClearTimer(T2);

	int startTurn = 2; // IRSeeker indicates far left
	while(HTIRS2readACDir(IRSeeker) > startTurn) {
		driveMotors(HALF_IMPULSE, HALF_IMPULSE, -1);
		/* Stop driving if it takes too long
		if (time100[T2] < MAX_AUTO_DRIVE_TIME) {
			break;
		}
		*/
	}
	stopDriveMotors();

	motorEncoder_out = readDriveEncoder();
	int stopTurn = 5;

	// Start timing our turn
	ClearTimer(T2);

	if (readDriveEncoder() < WALL_TO_MID) {
		//Take Inside Left Turn //
		while (HTIRS2readACDir(IRSeeker) != stopTurn) {
			OutsideLeftTurn(false);
			/* Stop turning if it takes too long
			if (time100[T2] < MAX_AUTO_TURN_TIME) {
				break;
				}
			*/
		}
	} else {
		//Take Outside Left Turn //
		while (HTIRS2readACDir(IRSeeker) != stopTurn) {
			InsideLeftTurn(false);
		}
		/* Stop turning if it takes too long
		if (time100[T2] < MAX_AUTO_TURN_TIME) {
			break;
			}
		*/
	}
	stopDriveMotors();
}

// Start Same as OnFlagLineRightCorner_Basket //
// Turns, finds line, follows line up on ramp and stops //
void OnFlagLineRightCorner_Ramp(bool reverse = false) {
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
	driveMotors(FULL_IMPULSE, FULL_IMPULSE, 100);

}
