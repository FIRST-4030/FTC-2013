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
#pragma debuggerWindows("joystickGame");
#include "teleop_includes.h"
#include "drive/drive_tank.c"

task main()
{
  initializeRobot();

  StartTask(Drive);
  FlashLights(2,50);

  int threshold = 10;
	while(true)
	{
		getJoystickSettings(joystick);
		//Spinner // Left Joystick //
		if(abs(joystick.joy2_y1) > threshold) {
			DriveSpinnerMotor(joystick.joy2_y1);
	  } else {
			DriveSpinnerMotor(0);
		}
		//Flag // Right Joystick //
		if(joystick.joy2_y2 > threshold) {
			DriveFlagMotor(joystick.joy2_y2);
		}	else {
			DriveFlagMotor(0);
		}

		//Winches
		if(joy2Btn(6) == 1) { // R1 //
			DriveWinchMotors(WINCH_SPEED);
		}
		else if(joy2Btn(8) == 1) { // R2 //
			DriveWinchMotors(-WINCH_SPEED);
		}	else {
			DriveWinchMotors(0);
		}

		//Hooks
		if(joy2Btn(5) == 1) {         // L1 //
			MoveHookServos(HOOK_INCR);  // UP //
		} else if(joy2Btn(7) == 1) {  // L2 //
			MoveHookServos(-HOOK_INCR); // DOWN //
		}

		//Hoppers
		if(joy2Btn(1) == 1) {             // X //
			MoveHopperServos(HOPPER_INCR);  // UP //
		}	else if(joy2Btn(2) == 1) {      // A //
			MoveHopperServos(-HOPPER_INCR); // DOWN //
		}

		//Lift
		if(joy2Btn(4) == 1) {          // Y //
			DriveLiftMotor(-LIFT_SPEED); // UP //
		}	else if(joy2Btn(3) == 1) {   // B //
			DriveLiftMotor(LIFT_SPEED);  // DOWN //
		} else {
			DriveLiftMotor(0);
		}
	}
}
