void AutonomousInit() {
	initializeRobot();

	bFloatDuringInactiveMotorPWM = false;
	servoChangeRate[leftHopper] = 0;
	servoChangeRate[rightHopper] = 0;

	SetHopperServos(HOPPER_MAX);
	// Initialize the sensor and motor configuration
	setLightSensorHeight(5.0);
	setDriveMotors(leftFrontMotor, leftRearMotor, rightFrontMotor, rightRearMotor);
	setLineSensors(lightLeft, lightRight);

	// Initialize Motor Encoders //
	resetDriveEncoder();

	// Stop All Motors //
	stopDriveMotors();

	// Cycle Light Sensor Lights //
	// Indicates Initialization Complete //
	FlashLights(5,50);
	return;
}
