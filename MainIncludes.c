

void initializeRobot()
{
	wait1Msec(1000);

	// Initialize Motor Encoders //
	nMotorEncoder[leftRearMotor] = 0;

	// Stop All Motors //
	motor[leftFrontMotor] = 0;
	motor[leftRearMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightRearMotor] = 0;
	motor[spinnerMotor] = 0;
	motor[liftMotor] = 0;
	motor[leftWinch] = 0;
	motor[rightWinch] = 0;

	// Set Wheels to Coast //
	bFloatDuringInactiveMotorPWM = true;

	SetHookServos(HOOK_MIN); // Put all the way back //
	SetHopperServos(HOPPER_MAX); // Completely put away //
	servoChangeRate[leftHook] = 1;
	servoChangeRate[rightHook] = 1;
	servoChangeRate[leftHopper] = 1;
	servoChangeRate[rightHopper] = 1;


	// Cycle Light Sensor Lights //
	// Indicates Initialization Complete //
	int delay = 50;
	for(int i=0; i<10; i++)
	{
		LSsetInactive(lightRight);
  	LSsetInactive(lightLeft);
		wait1Msec(delay);
	  LSsetActive(lightRight);
  	LSsetActive(lightLeft);
		wait1Msec(delay);
	}

	return;
}
