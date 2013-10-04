/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Palm Island with XBox Controller
- This progam is designed to work with the Palm Island RVW using an XBox controller.

Robot Model(s):  Mammal on Palm Island Virtual World

[I/O Port]          [Name]              [Type]                [Description]
Motor Port A 				motorA							NXT Motor             Gripper Motor
Motor Port B        motorB    			    NXT Motor             Right side Motor
Motor Port C        motorC		          NXT Motor             Left side motor
----------------------------------------------------------------------------------------------------*/

#pragma debuggerWindows("joystickSimple");
#include "JoystickDriver.c"
// Test GitAuth

task main()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 20;

	// If tankMode is true, then robot uses Tank Drive
	// If tankMode is false, then robot uses Arcade Drive
	bool tankMode = false;

	//Loop Forever
	while(1 == 1)
	{
		//Get the Latest joystick values
		getJoystickSettings(joystick);
		//Driving Control

		// Choose Control Mode //
		if(joy1Btn(6) == 1)  // XBox R1
			tankMode = true;
		if(joy1Btn(5) == 1)  // XBox L1
			tankMode = false;

		// XBox Left Analog Stick //
		float x1 = joystick.joy1_x1;
		float y1 = joystick.joy1_y1;

		// XBox Right Analog Stick //
		float x2 = joystick.joy1_x2;
		float y2 = joystick.joy1_y2;
		if(tankMode == false)
		{
			// Arcade Drive Uses Only Left Analog Stick //
			if(abs(x1) > threshold || abs(y1) > threshold)
			{
				x1 = x1*0.5;
				motor[motorC] = x1 + y1;
				motor[motorB] = -x1 + y1;
			}
			else
			{
				motor[motorC] = 0;
				motor[motorB] = 0;
			}
		}
		else
		{
			// Tank Drive Uses Both Left and Right Analog Sticks //
			if(abs(y1) > threshold)
				motor[motorC] = y1;
			else
				motor[motorC] = 0;

			if(abs(y2) > threshold)
				motor[motorB] = y2;
			else
				motor[motorB] = 0;
		}

		// Open the Gripper //
		if(joy1Btn(1) == 1)   // XBox A
		{
			motor[motorA] = 100;
		}

		// Close the Gripper //
		if(joy1Btn(3) == 1)   // XBox X
		{
			motor[motorA] = -100;
		}
	}
}
