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

task main() {
	AutonomousInit();

	// Wait for the beginning of autonomous phase.
	waitForStart();

	// Wait 10 seconds and then go //
	wait1Msec(10 * 1000);

	// Basket Routine //
	FlagLine_DriveToBasket();
	PrepareToDump();
	int SonarBeforeBasketApproach = USreadDist(sonar);
	ApproachBasket();
	DumpHopper();
	FlagLine_ReturnFromBasket(SonarBeforeBasketApproach);

	// Ramp Routine //
	FlagLine_GoToRamp();
}