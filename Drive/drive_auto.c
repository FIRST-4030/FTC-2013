#ifndef FTC_DRIVE_AUTO
#define FTC_DRIVE_AUTO

// Drive functions which the Main Controller Does not need //
#define BLIPS_PER_INCH (1440.0 / 12.6)
#define INCH_PER_BLIPS (12.6 / 1440.0)
#define FULL_IMPULSE (100)
#define HALF_IMPULSE (50)
#define QUARTER_IMPULSE (25)
#define EIGHTH_IMPULSE (12)
#define WALL_TO_MID (3000)

bool STARTED_ON_LEFT = true;
int B2I(int x)
{
	return x / BLIPS_PER_INCH;
}
int I2B(int x)
{
	return x * INCH_PER_BLIPS;
}

void EarlyBasketTurnLeft(bool reverse)
{
	if(reverse == false)
		driveMotors(-FULL_IMPULSE,FULL_IMPULSE,-1);
	else
		driveMotors(FULL_IMPULSE,-FULL_IMPULSE,-1);
}
void LateBasketTurnLeft(bool reverse)
{
	if(reverse == false)
		driveMotors(-FULL_IMPULSE,FULL_IMPULSE,-1);
	else
		driveMotors(FULL_IMPULSE,-FULL_IMPULSE,-1);
}
void EarlyBasketTurnRight(bool reverse)
{
	if(reverse == false)
		driveMotors(FULL_IMPULSE,-FULL_IMPULSE,-1);
	else
		driveMotors(-FULL_IMPULSE,FULL_IMPULSE,-1);
}
void LateBasketTurnRight(bool reverse)
{
	if(reverse == false)
		driveMotors(FULL_IMPULSE,-FULL_IMPULSE,-1);
	else
		driveMotors(-FULL_IMPULSE,FULL_IMPULSE,-1);
}

void InsideTurn(bool reverse)
{
	if(STARTED_ON_LEFT){
		if(reverse == false)
			driveMotors(-FULL_IMPULSE,0,-1);
		else
			driveMotors(FULL_IMPULSE,0,-1);
	} else {
		if(reverse == false)
			driveMotors(0,-FULL_IMPULSE,-1);
		else
			driveMotors(0,FULL_IMPULSE,-1);
	}
}
void OutsideTurn(bool reverse)
{
	if(STARTED_ON_LEFT){
		if(reverse == false)
			driveMotors(0,FULL_IMPULSE,-1);
		else
			driveMotors(0,-FULL_IMPULSE,-1);
	} else {
		if(reverse == false)
			driveMotors(FULL_IMPULSE,0,-1);
		else
			driveMotors(-FULL_IMPULSE,0,-1);
	}
}

void FollowLine(int lineColor)
{
	if(LSvalRaw(lightLeft) > lineColor)
		driveMotors(0,QUARTER_IMPULSE,-1);
	else if(LSvalRaw(lightRight) > lineColor)
		driveMotors(QUARTER_IMPULSE,0,-1);
	else
		driveMotors(QUARTER_IMPULSE,QUARTER_IMPULSE,-1);
}

#endif
