#ifndef FTC_SERVOS
#define FTC_SERVOS

// Hopper Defines //
#define HOPPER_MIN (60) // Put Down To Load //
#define HOPPER_MAX (HOPPER_MIN + 80) // Put Away //
#define HOPPER_INCR (5)

// Hook Defines //
#define HOOK_MIN (0) // Put Away //
#define HOOK_MID (150)
#define HOOK_MAX (255) // Put Out //
#define HOOK_INCR (10)

void SetHookServos(int loc)
{
	servo[leftHook] = loc;
	servo[rightHook] = 255-loc;
}

void MoveHookServos(int quan)
{
	int l = ServoValue[leftHook]+quan;
	if(l<HOOK_MIN)
		l=HOOK_MIN;
	else if(l>HOOK_MAX)
		l=HOOK_MAX;
	SetHookServos(l);
}

void SetHopperServos(int loc)
{
	servo[leftHopper] = loc;
	servo[rightHopper] = loc;
}

void MoveHopperServos(int quan)
{
	int l = ServoValue[leftHopper]+quan;
	if(l<HOPPER_MIN)
		l = HOPPER_MIN;
	else if(l>HOPPER_MAX)
		l = HOPPER_MAX;
	SetHopperServos(l);
}

#endif
