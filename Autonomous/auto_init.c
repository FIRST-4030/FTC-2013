#ifndef FTC_AUTO_INIT
#define FTC_AUTO_INIT
#include "../init_robot.c"; // initializeRobot() Routine //

void AutonomousInit() {
	initializeRobot();

	bFloatDuringInactiveMotorPWM = false;

	// Init Global Variables //
	if(HTIRS2readACDir(IRSeeker) > 5){
		STARTED_ON_LEFT = false;
	}


	// Maximize Hopper Change Rates //
	servoChangeRate[leftHopper] = 0;
	servoChangeRate[rightHopper] = 0;

	SetHopperServos(HOPPER_MAX);
	// Initialize the sensor and motor configuration
	setLightSensorHeight(5.0);
	setDriveMotors(leftFrontMotor, leftRearMotor, rightFrontMotor, rightRearMotor);
	setLineSensors(lightLeft, lightRight);

	// Initialize Motor Encoders //
	resetDriveEncoder();

	// Stop All Drive Motors //
	stopDriveMotors();

	// Cycle Light Sensor Lights //
	// Indicates Initialization Complete //
	FlashLights(5,50);
	return;
}
#endif
