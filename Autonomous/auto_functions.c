#ifndef FTC_AUTO_FUNCTIONS
#define FTC_AUTO_FUNCTIONS

// Autonomous Mode Operational Functions //
// Put functions here which do specific actions on the robot. //

void MoveLift(bool down = true) {
	int speed = LIFT_SPEED;
	if (!down) {
		speed *= -1;
	}

	DriveLiftMotor(speed);
	wait1Msec(5000);
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
	wait1Msec(5000);
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

void IRFailed() {
	driveToDistance(1750, HALF_IMPULSE);
	turnInPlace(3000, HALF_IMPULSE);
}

void SonarFailed() {
	driveToDistance(1800, HALF_IMPULSE);
	return;
}

void ApproachBasket() {
	int range = USreadDist(sonar);

	// Ensure sonar is sane
	if (range < 10 || range > 100) {
		SonarFailed();
		return;
	}

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

// Start the robot with the back right wheel touching the wall and the right wheels lined up with the flag line.
// Face the robot along the flag line.
void FlagLine_DriveToBasket()  //Add a bool variable that can be passed and call Wait?
{

	// Count distance from our starting point
	resetDriveEncoder();
	int IRVal = HTIRS2readACDir(IRSeeker);

	// IR failed -- static drive (i.e. hope)
	if(IRVal < 1 || IRVal > 8) {
		IRFailed();
		return;
	}

	// Drive Forward Until Aligned With Basket //
	// @Zach - yes this is redundant code but it is easier to follow than setting a default and other //
	if(STARTED_ON_LEFT == true)
	{
		int startTurn = 2; // Starting on the Left
		while(HTIRS2readACDir(IRSeeker) > startTurn) {
			runDriveMotors(HALF_IMPULSE, HALF_IMPULSE);
		}
	}
	else if(STARTED_ON_LEFT == false)
	{
		int startTurn = 8; // Starting on the Right
		while(HTIRS2readACDir(IRSeeker) < startTurn) {
			runDriveMotors(HALF_IMPULSE, HALF_IMPULSE);
		}
	}
	stopDriveMotors();
	return;

	// Turn Until Facing IR Beacon //
	motorEncoder_out = readDriveEncoder();
	int stopTurn = 5;
	if (readDriveEncoder() < WALL_TO_MID) {
		while (HTIRS2readACDir(IRSeeker) != stopTurn) {
			if(STARTED_ON_LEFT == true){
				EarlyBasketTurnLeft(false);
			} else {
				EarlyBasketTurnRight(false);
			}
		}
	} else {
		while (HTIRS2readACDir(IRSeeker) != stopTurn) {
			if(STARTED_ON_LEFT == true){
				LateBasketTurnLeft(false);
			} else {
				LateBasketTurnRight(false);
			}
		}
	}
	stopDriveMotors();
}

void FlagLine_ReturnFromBasket(int sonarTarget) {
	// Reverse To Turn Location //
	while(USreadDist(sonar) < sonarTarget) {
		runDriveMotors(-QUARTER_IMPULSE, -QUARTER_IMPULSE);
	}
	stopDriveMotors();

	int IRTarget = 2; // target for a start on the left
	if(STARTED_ON_LEFT == false)
		IRTarget = 8;

	// Reverse Turn //
	if (readDriveEncoder() < WALL_TO_MID) {
		while (HTIRS2readACDir(IRSeeker) != IRTarget) {
			OutsideTurn(true);
		}
	} else {
		while (HTIRS2readACDir(IRSeeker) != IRTarget) {
			InsideTurn(true);
		}
	}

	// Backup To Starting Location //
	while(readDriveEncoder() > 0) {
		runDriveMotors(-QUARTER_IMPULSE,-QUARTER_IMPULSE);
	}
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