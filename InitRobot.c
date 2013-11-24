////////////////////////////
///// INITIALIZE ROBOT /////
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
	//bFloatDuringInactiveMotorPWM = true;

	SetHookServos(HOOK_MIN); // Put all the way back //
	servoChangeRate[leftHook] = 2;
	servoChangeRate[rightHook] = 2;
	servoChangeRate[leftHopper] = 1;
	servoChangeRate[rightHopper] = 1;

	return;
}
