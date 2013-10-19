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

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
MODIFICATION:
This program has been modified in the following manner:
1. It works with an XBox Controller.
2. Arcade Drive is the default drive mode.
3. TopHat 0 puts it in Arcade Drive
4. TopHat 4 puts it in Tank Drive
5. Tank Drive and Spinner Control overlap so you must put it in Arcade Drive to move the spinner without moving.
6. The code will likely need many changes to work with the USB Controller.
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Gripperbot - Remote Control
- NOTE: Gripperbot can be used to pick up game objects from the floor and to raise the flag.
- This program allows you to remotely control your robot using the XBox.
- This program also ignores low values that would cause your robot to move when the joysticks fail to
return back to exact center.  You may need to adjust the 'threshold' value to get it just right.

Robot Model(s): TETRIX Gripperbot (IR) (Virtual Worlds)

[I/O Port]          [Name]              [Type]                [Description]
Motor Port A        gripperMotor        NXT Motor             Gripper motor
Motor Port D        rightMotor          TETRIX Motor          Right side motor
Motor Port E				leftMotor						TETRIX Motor					Left side motor
Motor Port F 				armMotor						TETRIX Motor					Arm motor
Motor Port G 				spinnerMotor				TETRIX Motor 					Spinner motor

Sensor Port 2				IRSeeker						IRSeeker 1200					HiTechnic IRSeeker 1200
Sensor Port 3				light   						Light Sensor					NXT Light Sensor (Active)
Sensor Port 4				sonar 							Sonar Sensor					NXT Sonar Sensor
----------------------------------------------------------------------------------------------------*/

#pragma debuggerWindows("joystickSimple");
#include "JoystickDriver.c"

int IR_out = 0;
int Sonar_out = 0;
int Light_out = 0;

task main()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;

	// Sensor Calibration //
	IR_out = SensorValue[IRSeeker];
	Sonar_out = SensorValue[sonar];
	Light_out = SensorValue[light];

	// If tankMode is true, then robot uses Tank Drive
	// If tankMode is false, then robot uses Arcade Drive
	bool tankMode = true;

	//Loop Forever
	while(1 == 1)
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

		//Arm Motor Control
		if(joy1Btn(8) == 1)          // XBox A
		{
			motor[flagMotor] = -100;      // raise the flag
		}
		else if(joy1Btn(7) == 1)     // XBox B
		{
			motor[flagMotor] = 100;     // lower the flag
		}
		else
		{
			motor[flagMotor] = 0;       // stop the flag motor
		}
	}
}
