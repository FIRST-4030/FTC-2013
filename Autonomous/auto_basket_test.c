#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     motors,         sensorNone)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Sensor, S3,     servos,         sensorNone)
#pragma config(Motor,  motorA,          flagMotor,     tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftFrontMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     leftRearMotor, tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     rightFrontMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rightRearMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     spinnerMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     rightWinch,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     leftWinch,     tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S3_C1_1,    leftHook,             tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    rightHook,            tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    unusedS3C13,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_4,    unusedS3C14,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_5,    unusedS3C15,          tServoStandard)
#pragma config(Servo,  srvo_S3_C1_6,    unusedS3C16,          tServoStandard)
#pragma config(Servo,  srvo_S3_C2_1,    leftHopper,           tServoStandard)
#pragma config(Servo,  srvo_S3_C2_2,    rightHopper,          tServoStandard)
#pragma config(Servo,  srvo_S3_C2_3,    unusedS3C23,          tServoStandard)
#pragma config(Servo,  srvo_S3_C2_4,    unusedS3C24,          tServoStandard)
#pragma config(Servo,  srvo_S3_C2_5,    unusedS3C25,          tServoStandard)
#pragma config(Servo,  srvo_S3_C2_6,    unusedS3C26,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma debuggerWindows("joystickSimple");
#include "auto_includes.h"
#include "drive/drive_tank.c"
#define B1 (3000)
#define B1IR (3000)
#define B2 (4400)
#define B2IR (4700)
#define B3 (7000)
#define B3IR (8400)
#define B4 (8600)
#define B4IR (9800)
#include "controllers/auto_testmode.c"

///// MAIN TASK /////
task main() {

	AutonomousInit();
	START_SIDE side = RIGHT;

	// Wait for the beginning of autonomous phase.
	//waitForStart();

	// Drive to the IR beacon, recording our distance
	resetDriveEncoder();
	bool validIR = driveToIR();
	int traveled = readDriveEncoder();

	// Figure out which basket we're at
	// If we didn't get a valid IR run, prefer the 2nd basket
	int basket = 1;
	if (validIR) {
		// If nothing matches we're at the first basket, so default to 0 if IR is valid
		basket = 0;
		for (int i = NUM_BASKETS - 1; i > 0; i--) {
			// Since the sensor is behind the midpoint we should always overshoot
			if (traveled >= basketPositions[side][i]) {
				basket = i;
				break;
			}
		}
	}

	// Adjust back to the correct turn point for the selected basket
	int adjustSpeed = HALF_IMPULSE;
	int adjustDistance = (basketPositions[side][basket] - traveled);
	if (adjustDistance < 0) {
		adjustSpeed *= -1;
	}
	driveToDistance(adjustDistance, adjustSpeed);

	// Turn to face baskets
	turnInPlaceDegrees(90, HALF_IMPULSE, (bool)side);

	// Raise lift so sonar works (and so we can dump)
	MoveLift(false);

	// Move forward to basket
	ApproachBasket();

	// Dump
	DumpHopper();

	// Nudge back for safety
	driveToDistance(-1000, -FULL_IMPULSE);

	// Lower so we can drive
	MoveLift(true);

	// Turn back to original orientation
	turnInPlaceDegrees(90, HALF_IMPULSE, (!(bool)side));

	// Drive backward to the corner
	driveToDistance((-1 * (traveled + adjustDistance)), -FULL_IMPULSE);
}
