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
	basketPositions[RIGHT][0] = 1250;
	basketPositions[RIGHT][1] = 2200;
	basketPositions[RIGHT][2] = 4850;
	basketPositions[RIGHT][3] = 6600;

	basketPositions[LEFT][0] = basketPositions[RIGHT][0] + 700;
	basketPositions[LEFT][1] = basketPositions[RIGHT][1] + 700;
	basketPositions[LEFT][2] = basketPositions[RIGHT][2] + 700;
	basketPositions[LEFT][3] = basketPositions[RIGHT][3] + 700;
}

void AutonomousInit() {
	initializeRobot();
	initBasketPositions();

	// Medium hopper speed
	servoChangeRate[leftHopper] = 2;
	servoChangeRate[rightHopper] = 2;

	// Initialize the sensor and motor configuration
	setLightSensorHeight(5.0);
	setDriveMotors(leftFrontMotor, leftRearMotor, rightFrontMotor, rightRearMotor);
	setLineSensors(lightLeft, lightRight);

	// Stop All Drive Motors //
	stopDriveMotors();
}
#endif
