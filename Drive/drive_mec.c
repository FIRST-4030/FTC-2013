// NOTE - Only one FTC_DRIVETASKM can be defined at a time. //
// If you include more than one FTC_DRIVETASKM file, the first one included will be used //
#ifndef FTC_DRIVETASKM
#define FTC_DRIVETASKM

///// MECANUM DRIVE TASK /////
// Standard Mecanum Drive
// Travelling in a Direction: joystick.joy1 (y1 and x1)
// Spinning in a Circle: joystick.joy1_x2

task DriveMec()
{
	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 10;

	//Loop Forever
	while(true)
	{

		//Get the Latest joystick values
		getJoystickSettings(joystick);

		//Left joystick is used for driving, right for spinning
		//Y1, Forward and backward
		if(abs(joystick.joy1_y1) > threshold)
			Y1 = joystick.joy1_y1;
		else
			Y1 = 0;

		//X1, Left and right
		if(abs(joystick.joy1_x1) > threshold)
			X1 = joystick.joy1_x1;
		else
			X1 = 0;

		//X2, Spinning
		if(abs(joystick.joy1_x2) > threshold)
			X2 = joystick.joy1_x2;
		else
			X2 = 0;

		DriveMecWheels(Y1, X1, X2);
	}
}

#endif
