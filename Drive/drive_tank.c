// NOTE - Only one FTC_DRIVETASK can be defined at a time. //
// If you include more than one FTC_DRIVETASK file, the first one included will be used //
#ifndef FTC_DRIVETASK
#define FTC_DRIVETASK

///// TANK DRIVE TASK /////
// Standard Tank Drive
// Left Motors: joystick.joy1_y1
// Right Motors: joystick.joy1_y2
// Holding L2 while driving reduces power by 75%

task Drive()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
	//less than the threshold will be ignored.
	int threshold = 10;
	while(true)
	{
		//Get the Latest joystick values
		getJoystickSettings(joystick);

		// Reverse joysticks if 5 and 6 are held
		int joy_left = joystick.joy1_y1;
		int joy_right = joystick.joy1_y2;
		if(joy1Btn(5) == 1 && joy1Btn(6) == 1) {
			int temp = joy_left;
			joy_left = -1 * joy_right;
			joy_right = -1 * temp;
		}

		//Each of these passes a value to set the motors to under certain circumstances
		//Left Wheels
		if(abs(joy_left) > threshold){
			DriveLeftSide(joy_left);
		} else {
			DriveLeftSide(0);
		}
		//Right Wheels
		if(abs(joy_right) > threshold) {
			DriveRightSide(joy_right);
		}	else {
			DriveRightSide(0);
		}
	}
}

#endif
