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

/*///////////////////////////////
Ingraham High School Robotics
FTC Team #7462
Main Robot Code
/*///////////////////////////////
#pragma debuggerWindows("joystickSimple");
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"
#include "JoystickDriver.c"
#include "Motors/servos.c"

// Motor Speeds //
#define WHEEL_MAX (60)
#define LIFT_SPEED (75)
#define WINCH_SPEED (100)

int leftHookVal = 0;
int rightHookVal = 0;
int leftHopperVal = 0;
int rightHopperVal = 0;

///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

////////////////////////////////
///// ROBOT INITIALIZATION /////
#include "MainIncludes.c";
////////////////////////////////


void DriveLeftSide(int power)
{
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
  motor[leftFrontMotor] = power;
	motor[leftRearMotor] = power;
}

void DriveRightSide(int power)
{
	power = (float)power * 100.0/128.0;
	if (power > WHEEL_MAX) {
		power = WHEEL_MAX;
	}
	motor[rightFrontMotor] = power;
	motor[rightRearMotor] = power;
}

void DriveSpinnerMotor(int power)
{
	motor[spinnerMotor] = power;
}

void DriveFlagMotor(int power)
{
	motor[flagMotor] = power;
}

void DriveWinchMotors(int power)
{
	motor[leftWinch] = power;
	motor[rightWinch] = power;
}

void DriveHookServos(int leftPower, int rightPower)
{
	servo[leftHook] = leftPower;
	servo[rightHook] = rightPower;
}

void DriveHopperServos(int leftPower, int rightPower)
{
	servo[leftHopper] = leftPower;
	servo[rightHopper] = rightPower;
}

void DriveLiftMotor(int power)
{
	motor[liftMotor] = power;
}


//////////////////////
///// DRIVE TASK /////
task Drive()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	while(true)
	{
		//Get the Latest joystick values
		getJoystickSettings(joystick);

		//Each of these passes a value to set the motors to under certain circumstances
		//Left Wheels
		if(abs(joystick.joy1_y1) > threshold){
			int power = joystick.joy1_y1;
			if(joy1Btn(7) == 1)
				power *= 0.25;
			DriveLeftSide(power);
		} else {
			DriveLeftSide(0);
		}
		//Right Wheels
		if(abs(joystick.joy1_y2) > threshold) {
			int power = joystick.joy1_y1;
			if(joy1Btn(7) == 1)
				power *= 0.25;
			DriveRightSide(joystick.joy1_y2);
		}	else {
			DriveRightSide(0);
		}
	}
}

task main()
{
  initializeRobot();
  //waitForStart(); // Wait for the beginning of autonomous phase.

  StartTask(Drive);

  int hookPos = HOOK_MIN;
  int threshold = 10;
	//Not really sure what this loop is here for, going to leave it in just in case
	while(true)
	{
		getJoystickSettings(joystick);
		//Spinner
		if(abs(joystick.joy2_y1) > threshold) {
			DriveSpinnerMotor(joystick.joy2_y1);
		}
		else {
			DriveSpinnerMotor(0);
		}
		//Flag
		if(joystick.joy2_y2 > threshold) {
			DriveFlagMotor(joystick.joy2_y2);
		}
		else {
			DriveFlagMotor(0);
		}

		//Winches
		if(joy2Btn(6) == 1) {
			DriveWinchMotors(WINCH_SPEED);
		}
		else if(joy2Btn(8) == 1) {
			DriveWinchMotors(-WINCH_SPEED);
		}
		else {
			DriveWinchMotors(0);
		}

		//Hooks
		if(joy2Btn(5) == 1) {
			if (hookPos == HOOK_MIN) {
				hookPos = HOOK_MID;
			} else if (hookPos == HOOK_MID) {
				hookPos = HOOK_MAX;
			} else {
				hookPos = HOOK_MIN;
			}
			SetHookServos(hookPos);
			while(joy2Btn(5) == 1) {}
		}
		if(joy2Btn(7) == 1) {
			SetHookServos(HOOK_MAX);
		}

		//Hoppers
		if(joy2Btn(1) == 1) {
			MoveHopperServos(HOPPER_INCR);
		}	else if(joy2Btn(2) == 1) {
			MoveHopperServos(-HOPPER_INCR);
		}

		//Lift
		if(joy2Btn(4) == 1) {
			DriveLiftMotor(LIFT_SPEED);
		}
		else if(joy2Btn(3) == 1) {
			DriveLiftMotor(-LIFT_SPEED);
		}
		else {
			DriveLiftMotor(0);
		}
	}

}
