#ifndef FTC_CONTROL_STANDARD
#define FTC_CONTROL_STANDARD

/// @todo: change this and standard.c to rely on the same code so we don't have redundancy
task AutoTestControl()
{
	// Slow Down Servos //
	servoChangeRate[leftHook] = 2;
	servoChangeRate[rightHook] = 2;
	servoChangeRate[leftHopper] = 1;
	servoChangeRate[rightHopper] = 1;

	int threshold = 10;
	while(true){
		getJoystickSettings(joystick);
		//Spinner // Left Joystick //
		if(joy1Btn(11) == 1 || motor[spinnerMotor] < 0){	// Left Analog Button //
			DriveSpinnerMotor(-50);													// Pull Blocks In //
			if(joy1Btn(12) == 1)
				DriveSpinnerMotor(50);
		} else if(joy1Btn(12) == 1){											// Left Analog Button //
			DriveSpinnerMotor(50);													// Push Blocks Out //
		} else {
			DriveSpinnerMotor(0);														// Stop Spinning //
		}

		//Winches
		if(joy1Btn(6) == 1) { // R1 //
			DriveWinchMotors(WINCH_SPEED);
		} else if(joy1Btn(10) == 1) { // START //
			DriveWinchMotors(-0.5*WINCH_SPEED);
		}	else {
			DriveWinchMotors(0);
		}

		//Flag
		if(joy1Btn(8) == 1) // R2 //
			DriveFlagMotor(100);
		else
			StopFlagMotor();



		//Hooks
		if(joy1Btn(5) == 1) {         // L1 //
			MoveHookServos(HOOK_INCR);  // UP //
		} else if(joy1Btn(7) == 1) {  // L2 //
			MoveHookServos(-HOOK_INCR); // DOWN //
		}

		//Hoppers
		if(joy1Btn(1) == 1) {             // X //
			MoveHopperServos(HOPPER_INCR);  // UP //
		}	else if(joy1Btn(2) == 1) {      // A //
			MoveHopperServos(-HOPPER_INCR); // DOWN //
		}

		//Lift
		if(joy1Btn(4) == 1) {          // Y //
			DriveLiftMotor(-LIFT_SPEED); // UP //
		}	else if(joy1Btn(3) == 1) {   // B //
			DriveLiftMotor(LIFT_SPEED);  // DOWN //
		} else {
			DriveLiftMotor(0);
		}
	}
}
#endif
