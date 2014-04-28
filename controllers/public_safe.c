#ifndef FTC_CONTROL_STANDARD
#define FTC_CONTROL_STANDARD

/// @todo: change this and standard.c to rely on the same code so we don't have redundancy
task PublicSafeControl()
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
		if(joy1Btn(7) == 1){	    // Pull Blocks In //
			DriveSpinnerMotor(-50);
		} else if(joy1Btn(5) == 1){
			DriveSpinnerMotor(50);	// Push Blocks Out //
	  } else {
	  	DriveSpinnerMotor(0);	  // Stop Spinning //
	  }

		//Flag
		if(joy1Btn(8) == 1) // R2 //
			DriveFlagMotor(100);
		else
			StopFlagMotor();

		//Hooks
		if(joy1Btn(4) == 1) {         // L1 //
			MoveHookServos(HOOK_INCR);  // UP //
		} else if(joy1Btn(3) == 1) {  // L2 //
			MoveHookServos(-HOOK_INCR); // DOWN //
		}

		//Hoppers
		if(joy1Btn(1) == 1) {             // X //
			MoveHopperServos(HOPPER_INCR);  // UP //
		}	else if(joy1Btn(2) == 1) {      // A //
			MoveHopperServos(-HOPPER_INCR); // DOWN //
		}
	}
}
#endif
