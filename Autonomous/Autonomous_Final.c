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

/*///////////////////////////////
Ingraham High School Robotics
FTC Team #7462
Main Robot Code
/*///////////////////////////////

///// Includes /////
#pragma debuggerWindows("joystickSimple");
#include "../drivers/hitechnic-sensormux.h"
#include "../drivers/hitechnic-irseeker-v2.h"
#include "../drivers/lego-ultrasound.h"
#include "../drivers/lego-touch.h"
#include "../drivers/lego-light.h"
#include "../sensors/colors.c"
#include "../Motors/motors.c"
#include "../Motors/servos.c"
#include "../Drive/lines.c"
#include "../Drive/drive.c"
#include "JoystickDriver.c"

///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

///// CONSTANTS /////
#define BLIPS_PER_INCH (1440.0 / 12.6)
#define INCH_PER_BLIPS (12.6 / 1440.0)
#define FULL_IMPULSE (100)
#define HALF_IMPULSE (50)
#define QUARTER_IMPULSE (25)
#define EIGHTH_IMPULSE (12)
#define WALL_TO_MID (3000)

int motorEncoder_out = 0;
int motorEncoder_inches = 0;
int B2I(int x)
{
	return x / BLIPS_PER_INCH;
}
int I2B(int x)
{
	return x * INCH_PER_BLIPS;
}

void FlashLights(int times, int delay)
{
	for(int i=0; i<times; i++)
	{
		LSsetInactive(lightRight);
	  LSsetInactive(lightLeft);
		wait1Msec(delay);
	  LSsetActive(lightRight);
  	LSsetActive(lightLeft);
		wait1Msec(delay);
	}
}

////////////////////////////////
///// ROBOT INITIALIZATION /////
#include "../MainIncludes.c";
// Additional Inits For Autonomous Mode //
void AutonomousInit() {
	initializeRobot();

	bFloatDuringInactiveMotorPWM = false;
	servoChangeRate[leftHopper] = 0;
	servoChangeRate[rightHopper] = 0;

	SetHopperServos(HOPPER_MIN);
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

void InsideLeftTurn(bool reverse)
{
	if(reverse == false)
		driveMotors(-FULL_IMPULSE,0,-1);
	else
		driveMotors(FULL_IMPULSE,0,-1);
}
void OutsideLeftTurn(bool reverse)
{
	if(reverse == false)
		driveMotors(FULL_IMPULSE,0,-1);
	else
		driveMotors(-FULL_IMPULSE,0,-1);
}

void FollowLine(int lineColor)
{
	if(LSvalRaw(lightLeft) > lineColor)
		driveMotors(0,QUARTER_IMPULSE,-1);
	else if(LSvalRaw(lightRight) > lineColor)
		driveMotors(QUARTER_IMPULSE,0,-1);
	else
		driveMotors(QUARTER_IMPULSE,QUARTER_IMPULSE,-1);
}

void Wait() {
	wait1Msec(10000);
}

//////////////////////////////
//				DRIVE TASK			  //
//////////////////////////////
task Drive() {
	int threshold = 10;
	while(true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > threshold)
			DriveLeftSide(joystick.joy1_y1);
		else
			DriveLeftSide(0);
		if(abs(joystick.joy1_y2) > threshold)
			DriveRightSide(joystick.joy1_y2);
		else
			DriveRightSide(0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         AUTONOMOUS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void dump() {
	// Lift hopper
	DriveLiftMotor(-FULL_IMPULSE);
	wait1Msec(5000);
	DriveLiftMotor(0);

	// Drive forward to set distance
	while(USreadDist(sonar) > 41) {
		runDriveMotors(QUARTER_IMPULSE, QUARTER_IMPULSE);
	}
	stopDriveMotors();

	// Unload
	SetHopperServos(HOPPER_MIN);
	DriveSpinnerMotor(HALF_IMPULSE);
	wait1Msec(2000);
	DriveSpinnerMotor(0);
}


// Start the robot with the back right wheel touching the wall and the right wheels lined up with the flag line.
// Face the robot along the flag line.
void OnFlagLineRightCorner_Basket()  //Add a bool variable that can be passed and call Wait?
{

	if(HTIRS2readACDir(IRSeeker) != 0) {
		// Count distance from our starting point
		resetDriveEncoder();

		// Start timing our drive
		ClearTimer(T2);
		int startTurn = 2; // IRSeeker indicates far left
		while(HTIRS2readACDir(IRSeeker) > startTurn) {
			driveMotors(HALF_IMPULSE, HALF_IMPULSE, -1);
			/*
			if (time100[T2] < MAX_AUTO_DRIVE_TIME) {
				break;
			}
			*/
		}
		stopDriveMotors();

		int encoderAtTurn = readDriveEncoder();
		motorEncoder_out = readDriveEncoder();
		int stopTurn = 5;

		// Start timing our turn
		ClearTimer(T2);
		if (readDriveEncoder() < WALL_TO_MID) {
			//Take Inside Left Turn //
			while (HTIRS2readACDir(IRSeeker) != stopTurn) {
				OutsideLeftTurn(false);
				/*
				if (time100[T2] < MAX_AUTO_TURN_TIME) {
					break;
					}
				*/
			}
		} else {
			//Take Outside Left Turn //
			while (HTIRS2readACDir(IRSeeker) != stopTurn) {
				InsideLeftTurn(false);
			}
			/*
			if (time100[T2] < MAX_AUTO_TURN_TIME) {
				break;
				}
			*/
		}
		stopDriveMotors();

		///// PLACEHOLDER FOR DUMPING ROUTINE /////
		dump();
		///////////////////////////////////////////
	}
}
// Start Same as OnFlagLineRightCorner_Basket //
// Turns, finds line, follows line up on ramp and stops //
void OnFlagLineRightCorner_Ramp(bool reverse = false) {
	// Turn Left Dead Reckoning //
	if (reverse) {
		driveMotors(HALF_IMPULSE,-1 * HALF_IMPULSE, 900);
	} else {
		driveMotors(-1 * HALF_IMPULSE, HALF_IMPULSE, 900);
	}

	// Forward to white line
	driveToColor(WHITE, QUARTER_IMPULSE);

	// Align with white line
	alignLine(WHITE, QUARTER_IMPULSE, BLACK, reverse);

	// Follow line to ramp
	followLineToColor(WHITE, HALF_IMPULSE, BLACK);

	// Rear Light Sensor is Mounted about 2" in front of wheels //
	driveMotors(FULL_IMPULSE, FULL_IMPULSE, 100);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibrateColors()
{
	FlashLights(3,250);
	getJoystickSettings(joystick);
	while(joy1Btn(10) != 1)
	{
		// black // A
		if(joy1Btn(2) == 1)
		{
			COLORS[BLACK].min = LSvalRaw(lightLeft)-10;
			COLORS[BLACK].max = LSvalRaw(lightRight)+10;
			FlashLights(2,250);
		}
		// white // Y
		if(joy1Btn(4) == 1)
		{
			COLORS[WHITE].min = LSvalRaw(lightLeft)-10;
			COLORS[WHITE].max = LSvalRaw(lightRight)+10;
			FlashLights(2,250);
		}
		// red // B
		if(joy1Btn(3) == 1)
		{
			COLORS[RED].min = LSvalRaw(lightLeft)-10;
			COLORS[RED].max = LSvalRaw(lightRight)+10;
			FlashLights(2,250);
		}
		// blue // X
		if(joy1Btn(1) == 1)
		{
			COLORS[BLUE].min = LSvalRaw(lightLeft)-10;
			COLORS[BLUE].max = LSvalRaw(lightRight)+10;
			FlashLights(2,250);
		}
	}
	// gray // start
	COLORS[GREY].min = LSvalRaw(lightLeft)-10;
	COLORS[GREY].max = LSvalRaw(lightRight)+10;
	FlashLights(3,250);
}

task main() {
	AutonomousInit();

	// Wait for the beginning of autonomous phase.
	waitForStart();

	// Start counting time from autonomous start in timer T1
	ClearTimer(T1);

	// Optionally wait for our partner
	wait1Msec(6 * 1000);

	// Drive to basket and dump
	OnFlagLineRightCorner_Basket();
}
