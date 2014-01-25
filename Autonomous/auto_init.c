#ifndef FTC_AUTO_INIT
#define FTC_AUTO_INIT
#include "../init_robot.c"; // initializeRobot() Routine //

#define NEAR_BASKET_OFFSET (175)
#define FAR_BASKET_OFFSET (-100)
#define START_LEFT_OFFSET (400)
#define HOPPER_DUMP (HOPPER_MIN + 30)

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

	for (int i = 0; i < NUM_BASKETS; i++) {
		basketPositions[LEFT][i] = basketPositions[RIGHT][i] + START_LEFT_OFFSET;
	}
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
