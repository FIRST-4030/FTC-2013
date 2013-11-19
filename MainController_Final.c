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

#define FULL_IMPULSE (100)
#define HALF_IMPULSE (50)
#define QUARTER_IMPULSE (25)
#define EIGHTH_IMPULSE (12)

///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

////////////////////////////////
///// ROBOT INITIALIZATION /////
void initializeRobot()
{

	// Initialize Motor Encoders //
	nMotorEncoder[leftRearMotor] = 0;

	// Stop All Motors //
	motor[leftFrontMotor] = 0;
	motor[leftRearMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightRearMotor] = 0;
	motor[spinnerMotor] = 0;

	// Cycle Light Sensor Lights //
	// Indicates Initialization Complete //
	int delay = 50;
	for(int i=0; i<10; i++)
	{
		LSsetInactive(lightRight);
  	LSsetInactive(lightLeft);
		wait1Msec(delay);
	  LSsetActive(lightRight);
  	LSsetActive(lightLeft);
		wait1Msec(delay);
	}

	return;
}

void DriveLeftSide()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(abs(joystick.joy1_y1) > threshold){
		motor[leftFrontMotor] = joystick.joy1_y1;
		motor[leftRearMotor] = joystick.joy1_y1;
	}	else {
		motor[leftFrontMotor] = 0;
		motor[leftRearMotor] = 0;
	}
}

void DriveRightSide()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(abs(joystick.joy1_y2) > threshold) {
		motor[rightFrontMotor] = joystick.joy1_y2;
		motor[rightRearMotor] = joystick.joy1_y2;
	} else {
		motor[rightFrontMotor] = 0;
		motor[rightRearMotor] = 0;
	}
}

void DriveSpinnerMotor()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(abs(joystick.joy2_y1) > threshold) {
		motor[spinnerMotor] = joystick.joy2_y1;
	}
	else {
		motor[spinnerMotor] = 0;
	}
}

void DriveFlagMotor()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	//Flag Motor only goes one direction
	if(joystick.joy2_y2 > threshold) {
		motor[flagMotor] = joystick.joy2_y2;
	}
	else {
		motor[flagMotor] = 0;
	}
}

void DriveWinchMotors()
{
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(joy2Btn(6) == 1) {
		motor[leftWinch] = 50;
		motor[rightWinch] = 50;
	}
	else {
		motor[leftWinch] = 0;
		motor[rightWinch] = 0;
	}
	if(joy2Btn(8) == 1) {
		motor[leftWinch] = -50;
		motor[rightWinch] = -50;
	}
	else {
		motor[leftWinch] = 0;
		motor[rightWinch] = 0;
	}
}

void DriveHookServos()
{
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(joy2Btn(5) == 1) {
		servo[leftHook] = 50;
		servo[rightHook] = 50;
	}
	else {
		servo[leftHook] = 0;
		servo[rightHook] = 0;
	}
	if(joy2Btn(7) == 1) {
		servo[leftHook] = -50;
		servo[rightHook] = -50;
	}
	else {
		servo[leftHook] = 0;
		servo[rightHook] = 0;
	}

}

void DriveHopperServos()
{
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(joy2Btn(1) == 1) {
		servo[leftHopper] = 50;
		servo[rightHopper] = 50;
	}
	else {
		servo[leftHopper] = 0;
		servo[rightHopper] = 0;
	}
	if(joy2Btn(2) == 1) {
		servo[leftHopper] = -50;
		servo[rightHopper] = -50;
	}
	else {
		servo[leftHopper] = 0;
		servo[rightHopper] = 0;
	}
}

void DriveLiftMotor()
{
	//Get the Latest joystick values
	getJoystickSettings(joystick);
	if(joy2Btn(4) == 1) {
		motor[liftMotor] = 50;
	}
	else {
		motor[liftMotor] = 0;
	}
	if(joy2Btn(3) == 1) {
		motor[liftMotor] = -50;
	}
	else {
		motor[liftMotor] = 0;
	}
}

//////////////////////
///// DRIVE TASK /////
task Drive()
{
	while(true)
	{
	DriveLeftSide();
		DriveRightSide();
		DriveSpinnerMotor();
		DriveFlagMotor();
		DriveWinchMotors();
		DriveHookServos();
		DriveHopperServos();
		DriveLiftMotor();
	}
}

task main()
{
  initializeRobot();
  //waitForStart(); // Wait for the beginning of autonomous phase.

  StartTask(Drive);

  int threshold = 10;
	//Loop Forever
	while(true)
	{
	}
}
