#ifndef FTC_CONTROL_STANDARD
#define FTC_CONTROL_STANDARD

		getJoystickSettings(joystick);
		//Spinner // Left Joystick //
		if(abs(joystick.joy2_y1) > threshold) {
			DriveSpinnerMotor(joystick.joy2_y1);
	  } else {
			DriveSpinnerMotor(0);
		}
		//Flag // Right Joystick //
		if(joystick.joy2_y2 > threshold) {
			DriveFlagMotor(joystick.joy2_y2);
		}	else {
			DriveFlagMotor(0);
		}

		//Winches
		if(joy2Btn(6) == 1) { // R1 //
			DriveWinchMotors(WINCH_SPEED);
		}
		else if(joy2Btn(8) == 1) { // R2 //
			DriveWinchMotors(-WINCH_SPEED);
		}	else {
			DriveWinchMotors(0);
		}

		//Hooks
		if(joy2Btn(5) == 1) {         // L1 //
			MoveHookServos(HOOK_INCR);  // UP //
		} else if(joy2Btn(7) == 1) {  // L2 //
			MoveHookServos(-HOOK_INCR); // DOWN //
		}

		//Hoppers
		if(joy2Btn(1) == 1) {             // X //
			MoveHopperServos(HOPPER_INCR);  // UP //
		}	else if(joy2Btn(2) == 1) {      // A //
			MoveHopperServos(-HOPPER_INCR); // DOWN //
		}

		//Lift
		if(joy2Btn(4) == 1) {          // Y //
			DriveLiftMotor(-LIFT_SPEED); // UP //
		}	else if(joy2Btn(3) == 1) {   // B //
			DriveLiftMotor(LIFT_SPEED);  // DOWN //
		} else {
			DriveLiftMotor(0);
		}
#endif
