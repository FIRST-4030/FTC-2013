#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRSeeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     light,          sensorLightActive)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          gripperMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightMotor,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftMotor,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     flagMotor,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     spinnerMotor,  tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an Tetrix robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma debuggerWindows("joystickSimple");
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

int IR_out = 0;
int Sonar_out = 0;
int Light_out = 0;

//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
//less than the threshold will be ignored.
int threshold = 10;

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}

void driveMotors(int powLeft, int powRight, const int nTime)
{
  motor[rightMotor] =  powRight;
  motor[leftMotor]  =  powLeft;
  if(nTime >=0)
  	wait1Msec(nTime);
}

//basket path
void goToBasket(int nBasket)
{
	if(nBasket == 3)          // LL
		{
			driveMotors(0,75,1500);
		}
		else if(nBasket == 4)     // Left
		{
			driveMotors(50,75,1000);
		}
		else if(nBasket == 5)     // Right
		{
			driveMotors(75,50,1000);
		}
		else if (nBasket == 6)		// RR
		{
			driveMotors(75,0,1500);
		}

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


int fullImpulse = 100;
int halfImpulse = 50;
int quarterImpulse = 25;
int eighthImpulse = 12;

task main()
{
  initializeRobot();
  //waitForStart(); // Wait for the beginning of autonomous phase.

		IR_out = SensorValue[IRSeeker];
		Sonar_out = SensorValue[sonar];
		Light_out = SensorValue[light];

	//while(true)
	//{
		//getJoystickSettings(joystick);

		// Start: Right side on wall with front of robot facing flag.
		//if(joy1Btn(1) == 1)
		//{
			int firstTurn = 80; // distance to wall of ~32"
			while(SensorValue[sonar] > firstTurn )
				driveMotors(halfImpulse, halfImpulse, -1);

			// Left Turn //
			int stopLeftTurn = 5;
			while(SensorValue[IRSeeker] != stopLeftTurn && SensorValue[IRSeeker] != 0)
				driveMotors(-halfImpulse, halfImpulse, -1);

			// Approach Basket //
			while(SensorValue[sonar] > 50)
				driveMotors(quarterImpulse, quarterImpulse, -1);
		//}

		// Start: right wheels aligned with flag line. Back right wheel touching wall.
		if(joy1Btn(2) == 1)
		{
		}

	//}

  //lined up and ready to find IR sensor
  //	goToBasket(SensorValue[IRSeeker]);

}


//direction functions

//not needed?
void goForward(const int nTime)
{
  motor[leftMotor]  = 75;
  motor[rightMotor] = 75;
  if(nTime >=0)
  	wait1Msec(nTime);
}

void turnRight(const int nTime)
{
  motor[leftMotor]  = 75;
  motor[rightMotor] =  0;
  if(nTime >=0)
  	wait1Msec(nTime);
}

void turnLeft(const int nTime)
{
  motor[leftMotor]  =  0;
  motor[rightMotor] = 75;
  if(nTime >=0)
  	wait1Msec(nTime);
}

void goBackwards(const int nTime)
{
  motor[leftMotor]  = -75;
  motor[rightMotor] = -75;
  if(nTime >=0)
  	wait1Msec(nTime);
}
