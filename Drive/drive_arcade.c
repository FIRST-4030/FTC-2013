// NOTE - Only one FTC_DRIVETASK can be defined at a time. //
// If you include more than one FTC_DRIVETASK file, the first one included will be used //
#ifndef FTC_DRIVETASK
#define FTC_DRIVETASK
///// ARCADE DRIVE TASK /////
// Standard Tank Drive
// Left Motors: joystick.joy1_y1
// Right Motors: joystick.joy1_y2

task Drive()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	while(true)
	{
		//Get the Latest joystick values
		getJoystickSettings(joystick);

		// Left Analog Stick //
		float x1 = joystick.joy1_x1;
		float y1 = joystick.joy1_y1;

		// Right Analog Stick //
		float x2 = joystick.joy1_x2;
		float y2 = joystick.joy1_y2;
		// Arcade Drive Uses Only Left Analog Stick //
		if(abs(x1) > threshold || abs(y1) > threshold)
		{
			x1 = x1*0.5;
			DriveLeftSide(x1+y1);
			DriveRightSide(-x1+y1);
		}
		else
		{
			DriveLeftSide(0);
			DriveRightSide(0);
		}
	}
}
