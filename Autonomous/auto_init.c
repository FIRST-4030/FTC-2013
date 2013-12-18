#ifndef FTC_AUTO_INIT
#define FTC_AUTO_INIT
#include "../init_robot.c"; // initializeRobot() Routine //

typedef enum {
	RIGHT = 0,
	LEFT  = 1,
} START_SIDE;
#define NUM_START_SIDES (2)
#define NUM_BASKETS (4)
int basketPositions[NUM_START_SIDES][NUM_BASKETS];

void initBasketPositions() {
	basketPositions[LEFT][0] = 500;
	basketPositions[LEFT][1] = 2200;
	basketPositions[LEFT][2] = 4850;
	basketPositions[LEFT][3] = 6600;

	basketPositions[RIGHT][0] = 500;
	basketPositions[RIGHT][1] = 2200;
	basketPositions[RIGHT][2] = 4850;
	basketPositions[RIGHT][3] = 6600;
}

void AutonomousInit() {
	initializeRobot();
	initBasketPositions();

	// Medium hopper speed
	servoChangeRate[leftHopper] = 2;
	servoChangeRate[rightHopper] = 2;

	SetHopperServos(HOPPER_MAX);
	// Initialize the sensor and motor configuration
	setLightSensorHeight(5.0);
	setDriveMotors(leftFrontMotor, leftRearMotor, rightFrontMotor, rightRearMotor);
	setLineSensors(lightLeft, lightRight);

	// Initialize Motor Encoders //
	resetDriveEncoder();

	// Stop All Drive Motors //
	stopDriveMotors();

	// Enable the light sensors
	FlashLights(1, 0);
}
#endif
