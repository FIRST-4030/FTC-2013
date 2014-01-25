#ifndef FTC_COLORS
#define FTC_COLORS

#include "../drivers/lego-light.h"

// Switch this when using the light sensors on the smux vs directly
#define LIGHT_SENSOR_PORT_TYPE tMUXSensor
//#define LIGHT_SENSOR_PORT_TYPE tSensors

// Store the light sensor ports for use in light functions
LIGHT_SENSOR_PORT_TYPE lineLeft;
LIGHT_SENSOR_PORT_TYPE lineRight;
void setLineSensors(LIGHT_SENSOR_PORT_TYPE left, LIGHT_SENSOR_PORT_TYPE right) {
	lineLeft  = left;
	lineRight = right;
}

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
typedef int ColorBitmap;
#define COLOR_TO_BITMAP(x) (1 << x)

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
		COLORS[BLUE].max  = 330;
		COLORS[GREY].min  = 360;
		COLORS[GREY].max  = 390;
		COLORS[RED].min   = 420;
		COLORS[RED].max   = 450;
		COLORS[WHITE].min = 475;
		COLORS[WHITE].max = 505;
	}
}

// Return a bitmap of all colors matching the provided sensorVal
ColorBitmap matchColors(int sensorVal) {
	ColorBitmap bitmap = 0;
	int color = 0;
	for (color = 0; color < NUM_COLORS; color++) {
		if (COLOR_TO_BITMAP(color) & bitmap) {
			if (sensorVal >= COLORS[color].min && sensorVal <= COLORS[color].max) {
				bitmap |= COLOR_TO_BITMAP(color);
			}
		}
	}

	return bitmap;
}

// Return true if the provided sensorVal matches any of the colors marked in the provided bitmap
bool onColors(ColorBitmap bitmap, int sensorVal) {
	ColorBitmap colors = matchColors(sensorVal);
	if (colors & bitmap != 0) {
		return true;
	}
	return false;
}

// Return true if the provided sensorVal matches the provided color
bool onColor(FloorColor color, int sensorVal) {
	return onColors(COLOR_TO_BITMAP(color), sensorVal);
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

int readLight(bool left = true) {
	if (left) {
		return LSvalRaw(lineLeft);
	} else {
		return LSvalRaw(lineRight);
	}
}

#endif
