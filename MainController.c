#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     motors,         sensorNone)
#pragma config(Sensor, S2,     SMUX,           sensorI2CCustom9V)
#pragma config(Motor,  motorA,          gripperMotor,  tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightMotor,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftMotor,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     spinnerMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     liftLeftMotor, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     liftRightMotor, tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*///////////////////////////////
Ingraham High School Robotics
FTC Team #7462
Main Robot Code
/*///////////////////////////////
#pragma debuggerWindows("joystickSimple");
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/lego-touch.h"
#include "drivers/lego-light.h"
#include "JoystickDriver.c"

///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

/////////////////////
///// CONSTANTS /////
const int fullImpulse = 100;
const int halfImpulse = 50;
const int quarterImpulse = 25;
const int eighthImpulse = 12;
int IR_out = 0;
int Sonar_out = 0;
int LightRight_out = 0;
int LightLeft_out = 0;
int motorEncoder_out = 0;
int motorEncoder_inches = 0;

#define BLIPS_PER_INCH (1440.0 / 12.6)
#define INCH_PER_BLIPS (12.6 / 1440.0)

int B2I(int x)
{
	return x / BLIPS_PER_INCH;
}

int I2B(int x)
{
	return x * INCH_PER_BLIPS;
}

////////////////////////////////
///// ROBOT INITIALIZATION /////
void initializeRobot()
{
  // Reinitialize Constants //
	int IR_out = 0;
	int Sonar_out = 0;
	int LightRight_out = 0;
	int LightLeft_out = 0;
	int motorEncoder_out = 0;
	int motorEncoder_inches = 0;

	// Initialize Motor Encoders //
	nMotorEncoder[leftMotor] = 0;

	// Stop All Motors //
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
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
		// Tank Drive Uses Both Left and Right Analog Sticks //
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

void MoveFlagMotor(const int speed, const int time)
{
	motor[flagMotor] = speed;
	if(time > 0)
		wait1Msec(time);
}

void MoveLiftMotor(const int speed, const int time)
{
	motor[liftLeftMotor] = speed;
	motor[liftRightMotor] = speed;
	if(time > 0)
		wait1Msec(time);
}

/////////////////////
///// MAIN TASK /////
task main()
{
  initializeRobot();
  //waitForStart(); // Wait for the beginning of autonomous phase.

  StartTask(Drive);

	//Loop Forever
	while(true)
	{
		// Sensor Calibration //
		IR_out = HTIRS2readACDir(IRSeeker);
		Sonar_out = USreadDist(sonar);
		LightRight_out = LSvalRaw(lightRight);
		LightLeft_out = LSvalRaw(lightLeft);
		motorEncoder_out = nMotorEncoder[leftMotor];
		motorEncoder_inches = B2I(motorEncoder_out);

		//Get the Latest joystick values
		getJoystickSettings(joystick);

		//Flag Motor Control //
		if(joy1Btn(8) == 1)       // XBox A
		{
			MoveFlagMotor(-fullImpulse,-1); // raise the flag
		}
		else if(joy1Btn(7) == 1)  // XBox B
		{
			MoveFlagMotor(fullImpulse,-1);  // lower the flag
		}
		else
		{
			MoveFlagMotor(0,-1);    // stop the flag motor
		}

		// Lift Motor Control //
		if(joy1Btn(5) == 1 )
		{
			MoveLiftMotor(fullImpulse,-1);
		}
		else if(joy1Btn(6) == 1 )
		{
			MoveLiftMotor(-fullImpulse,-1);
		}
		else
		{
			MoveLiftMotor(0,-1);
		}

		if(joy1Btn(9) == 1)
		{
			nMotorEncoder[leftMotor] = 0;
		}
		if(joy1Btn(10) == 1)
			initializeRobot();
	}
}
