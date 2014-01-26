#ifndef FTC_COLORS
#define FTC_COLORS

#include "../drivers/lego-light.h"

// Which colors can we detect
typedef enum {
	BLACK,
	WHITE,
	GREY,
	BLUE,
	RED,
	UNKNOWN
} FloorColor;
const FloorColor NUM_COLORS = 5;

// Each color has a min and max value
typedef struct {
	int min;
	int max;
} ColorRange;

// Global storage for our configured color set
ColorRange COLORS[NUM_COLORS];

void setLightSensorHeight(float height) {
	// 0.5" calibration
	if (height == 0.5) {
		COLORS[BLACK].min = 320;
		COLORS[BLACK].max = 335;
		COLORS[BLUE].min  = 340;
		COLORS[BLUE].max  = 365;
		COLORS[GREY].min  = 410;
		COLORS[GREY].max  = 435;
		COLORS[RED].min   = 505;
		COLORS[RED].max   = 520;
		COLORS[WHITE].min = 550;
		COLORS[WHITE].max = 585;
	// 1.0" calibration
	} else if (height == 1.0) {
		COLORS[BLACK].min = 270;
		COLORS[BLACK].max = 350;
		COLORS[BLUE].min  = 322;
		COLORS[BLUE].max  = 350;
		COLORS[GREY].min  = 360;
		COLORS[GREY].max  = 395;
		COLORS[RED].min   = 420;
		COLORS[RED].max   = 465;
		COLORS[WHITE].min = 475;
		COLORS[WHITE].max = 515;
	// 1.5" calibration
	} else if (height == 1.5) {
		COLORS[BLACK].min = 250;
		COLORS[BLACK].max = 300;
		COLORS[BLUE].min  = 290;
		COLORS[BLUE].max  = 320;
		COLORS[GREY].min  = 340;
		COLORS[GREY].max  = 365;
		COLORS[RED].min   = 380;
		COLORS[RED].max   = 420;
		COLORS[WHITE].min = 430;
		COLORS[WHITE].max = 480;
	} else {
		COLORS[BLACK].min = 275;
		COLORS[BLACK].max = 320;
		COLORS[BLUE].min  = 300;
		COLORS[BLUE].max  = 355;
		COLORS[GREY].min  = 360;
		COLORS[GREY].max  = 390;
		COLORS[RED].min   = 420;
		COLORS[RED].max   = 525;
		COLORS[WHITE].min = 475;
		COLORS[WHITE].max = 600;
	}
}

// Determine if the floor matches the indicated color
bool onColor(FloorColor color, int sensorVal) {
	bool onColor = false;
	if (sensorVal >= COLORS[color].min && sensorVal <= COLORS[color].max) {
		onColor = true;
	}
	return onColor;
}

// Determine the color under the sensor
FloorColor floorColor(int sensorVal) {
	int color;
	for (color = 0; color < NUM_COLORS; color++) {
		if (onColor(color, sensorVal)) {
			return (FloorColor)color;
		}
	}
	return UNKNOWN;
}

bool onBlack(int sensorVal) {
	return onColor(BLACK, sensorVal);
}

bool onWhite(int sensorVal) {
	return onColor(WHITE, sensorVal);
}

bool onGrey(int sensorVal) {
	return onColor(GREY, sensorVal);
}

bool onBlue(int sensorVal) {
	return onColor(BLUE, sensorVal);
}

bool onRed(int sensorVal) {
	return onColor(RED, sensorVal);
}

void FlashLights(int times, int delay) {
	for(int i=0; i < times; i++) {
		LSsetInactive(lightRight);
	  LSsetInactive(lightLeft);
		wait1Msec(delay);
	  LSsetActive(lightRight);
  	LSsetActive(lightLeft);
		wait1Msec(delay);
	}
}

#endif
