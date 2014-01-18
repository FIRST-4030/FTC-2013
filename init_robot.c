#ifndef FTC_INIT_ROBOT
#define FTC_INIT_ROBOT

///// INITIALIZE ROBOT /////
void initializeRobot() {

	// Stop All Motors //
	motor[leftFrontMotor] = 0;
	motor[leftRearMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightRearMotor] = 0;
	motor[spinnerMotor] = 0;
	motor[liftMotor] = 0;
	motor[leftWinch] = 0;
	motor[rightWinch] = 0;

	// Medium hook rate and retracted position
	SetHookServos(HOOK_MIN);
	servoChangeRate[leftHook] = 2;
	servoChangeRate[rightHook] = 2;

	// Low hopper speed and retracted position
	SetHopperServos(HOPPER_MAX);
	servoChangeRate[leftHopper] = 1;
	servoChangeRate[rightHopper] = 1;

	// Initialize encoders
	resetDriveEncoder();

	// Enable the light sensors
	FlashLights(1, 0);
}

#endif
