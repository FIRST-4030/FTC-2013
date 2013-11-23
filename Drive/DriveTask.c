//////////////////////
///// DRIVE TASK /////
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

		//Each of these passes a value to set the motors to under certain circumstances
		//Left Wheels
		if(abs(joystick.joy1_y1) > threshold){
			int power = joystick.joy1_y1;
			if(joy1Btn(7) == 1)
				power = (float)power * 0.25;
			DriveLeftSide(power);
		} else {
			DriveLeftSide(0);
		}
		//Right Wheels
		if(abs(joystick.joy1_y2) > threshold) {
			int power = joystick.joy1_y1;
			if(joy1Btn(7) == 1)
				power = (float)power * 0.25;
			DriveRightSide(joystick.joy1_y2);
		}	else {
			DriveRightSide(0);
		}
	}
}
