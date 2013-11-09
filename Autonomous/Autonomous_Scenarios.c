#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Motor,  motorA,          gripperMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightMotor,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftMotor,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     flagMotor,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     spinnerMotor,  tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
///// Includes /////
#pragma debuggerWindows("joystickSimple");
#include "../drivers/hitechnic-sensormux.h"
#include "../drivers/hitechnic-irseeker-v2.h"
#include "../drivers/lego-ultrasound.h"
#include "../drivers/lego-touch.h"
#include "../drivers/lego-light.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

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

int IR_out = 0;
int Sonar_out = 0;
int LightRight_out = 0;
int LightLeft_out = 0;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    initializeRobot
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
/////////////////////////////////////////////////////////////////////////////////////////////////////
void initializeRobot()
{
	// Initialize Motor Encoders //
	nMotorEncoder[leftMotor] = 0;

	// Stop All Motors //
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[spinnerMotor] = 0;

	// Cycle Light Sensor Lights //
	// Indicates Initialization Complete //
	FlashLights(5,50);
	return;
}

void driveMotors(int powLeft, int powRight, const int nTime)
{
  motor[rightMotor] =  powRight;
  motor[leftMotor]  =  powLeft;
  if(nTime >=0)
  	wait1Msec(nTime);
}

void InsideLeftTurn(bool reverse)
{
	if(reverse == false)
		driveMotors(-HALF_IMPULSE,0,-1);
	else
		driveMotors(HALF_IMPULSE,0,-1);
}
void OutsideLeftTurn(bool reverse)
{
	if(reverse == false)
		driveMotors(-QUARTER_IMPULSE,HALF_IMPULSE,-1);
	else
		driveMotors(HALF_IMPULSE,-HALF_IMPULSE,-1);
}

void FollowLine(int lightTargetOff, int lightTargetOn, int distance)
{
	nMotorEncoder[leftMotor] = 0;
	while(nMotorEncoder[leftMotor] < distance)
	{

	}
}

//////////////////////////////
//				DRIVE TASK			  //
//////////////////////////////
task Drive()
{
	int threshold = 10;
	while(true)
	{
		getJoystickSettings(joystick);
		if(abs(joystick.joy1_y1) > threshold)
			motor[leftMotor] = joystick.joy1_y1;
		else
			motor[leftMotor] = 0;
		if(abs(joystick.joy1_y2) > threshold)
			motor[rightMotor] = joystick.joy1_y2;
		else
			motor[rightMotor] = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         AUTONOMOUS SCENARIOS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
// Start the robot with the right side flush with the wall.
// Face the robot towards the flag.
void OnWallFacingFlag()
{
	int firstTurn = 80; // distance to wall of ~32"
	while(USreadDist(sonar) > firstTurn )
		driveMotors(HALF_IMPULSE, HALF_IMPULSE, -1);

	// Left Turn //
	int stopLeftTurn = 5;
	while(HTIRS2readACDir(IRSeeker) != stopLeftTurn)
		driveMotors(-HALF_IMPULSE, HALF_IMPULSE, -1);

	// Approach Basket //
	while(USreadDist(sonar) > 50) // && LSvalRaw(lightLeft) > 40) Light sensors need recalibrated with SMUX
		driveMotors(QUARTER_IMPULSE, QUARTER_IMPULSE, -1);

	driveMotors(0,0,-1);
}

// Start the robot with the back right wheel touching the wall and the right wheels lined up with the flag line.
// Face the robot along the flag line.
void OnFlagLineRightCorner_Basket()
{
	nMotorEncoder[leftMotor] = 0;
	int startTurn = 8; // IRSeeker indicates far left
	while(HTIRS2readACDir(IRSeeker) < startTurn )
		driveMotors(HALF_IMPULSE, HALF_IMPULSE, -1);

	int encoderAtTurn = nMotorEncoder[leftMotor];
	motorEncoder_out = nMotorEncoder[leftMotor];
	int stopTurn = 5;
	if(nMotorEncoder[leftMotor] < 3000)
	{
		//Take Inside Left Turn //
		while(HTIRS2readACDir(IRSeeker) != stopTurn)
			InsideLeftTurn(false);
  }
	else
	{
		//Take Outside Left Turn //
		while(HTIRS2readACDir(IRSeeker) != stopTurn)
			OutsideLeftTurn(false);
	}

	///// PLACEHOLDER FOR DUMPING ROUTINE /////
	driveMotors(0,0,-1);
	FlashLights(5,50);
	///////////////////////////////////////////

	// Return to Starting Point //
	while(HTIRS2readACDir(IRSeeker) != startTurn)
	{
		if(encoderAtTurn < 3000)
			InsideLeftTurn(true);
		else
			OutsideLeftTurn(true);
	}
	while(nMotorEncoder[leftMotor] > 0)
		driveMotors(-HALF_IMPULSE,-HALF_IMPULSE,-1);

	driveMotors(0,0,-1);
}
void OnFlagLineRightCorner_Ramp()
{
	// Turn Left Dead Reckoning //
	driveMotors(-HALF_IMPULSE,HALF_IMPULSE,850);

	while(LSvalRaw(lightLeft) < 370)
		driveMotors(HALF_IMPULSE,HALF_IMPULSE,-1);
	wait1Msec(200);

	////////////////////// NEEDS TESTING BEYOND HERE ///////////////////
	while(LSvalRaw(lightLeft) < 430)
		driveMotors(QUARTER_IMPULSE,-QUARTER_IMPULSE,-1);

	// Follow Line To Ramp //
	while(LSvalRaw(lightLeft) > 300)
	{
		if(LSvalRaw(lightLeft) > 370)
			motor[leftMotor] = motor[leftMotor] - 10;
		else if(LSvalRaw(lightRight) > 370)
			motor[rightMotor] = motor[rightMotor] -10;
		else
			driveMotors(QUARTER_IMPULSE,QUARTER_IMPULSE,-1);
	}
	FollowLine(300,430,3000);

	driveMotors(0,0,-1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
task main()
{
  initializeRobot();
  //waitForStart(); // Wait for the beginning of autonomous phase.

  StartTask(Drive); // Allows control of robot between scenarios //

  while(true)
	{
		getJoystickSettings(joystick);
		IR_out = HTIRS2readACDir(IRSeeker);
		Sonar_out = USreadDist(sonar);
		LightRight_out = LSvalRaw(lightRight);
		LightLeft_out = LSvalRaw(lightLeft);
		motorEncoder_out = nMotorEncoder[leftMotor];
		motorEncoder_inches = B2I(motorEncoder_out);

		// Start: Right side on wall with front of robot facing flag.
		if(joy1Btn(1) == 1) // X //
		{
			StopTask(Drive);
			OnWallFacingFlag();
			StartTask(Drive);
		}

		// Start: right wheels aligned with flag line. Back right wheel touching wall.
		if(joy1Btn(2) == 1) // A //
		{
			StopTask(Drive);
			OnFlagLineRightCorner_Basket();
			StartTask(Drive);
		}
		if(joy1Btn(3) == 1) // B //
		{
			StopTask(Drive);
			OnFlagLineRightCorner_Ramp();
			StartTask(Drive);
		}
		if(joy1Btn(9) == 1)
			nMotorEncoder[leftMotor] = 0;

		if(joy1Btn(10) == 1) // Start Button // Reinitialize Robot //
			initializeRobot();
	}
  //lined up and ready to find IR sensor
  //	goToBasket(SensorValue[IRSeeker]);
}
