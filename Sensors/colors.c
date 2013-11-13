// Set this to select a configuration set
#define LIGHT_SENSOR_CONFIG_1

// Which colors can we detect
typedef enum {
	BLACK,
	WHITE,
	GREY,
	BLUE,
	RED,
	UNKNOWN
} FloorColor;
const int NUM_COLORS = 5;

// Each color has a min and max value
typedef struct {
	int min;
	int max;
} ColorRange;

// Global storage for our configured color set
ColorRange COLORS[NUM_COLORS];

// Configuration data set 1
#ifdef LIGHT_SENSOR_CONFIG_1
colors[BLACK].min = 0;
colors[BLACK].max = 100;
colors[WHITE].min = 401;
colors[WHITE].max = 10000;
colors[GREY].min  = 101;
colors[GREY].max  = 200;
colors[BLUE].min  = 201;
colors[BLUE].max  = 300;
colors[RED].min   = 301;
colors[RED].max   = 400;
#endif

// Configuration data set 2
#ifdef LIGHT_SENSOR_CONFIG_2
colors[BLACK].min = 0;
colors[BLACK].max = 100;
colors[WHITE].min = 401;
colors[WHITE].max = 10000;
colors[GREY].min  = 101;
colors[GREY].max  = 200;
colors[BLUE].min  = 201;
colors[BLUE].max  = 300;
colors[RED].min   = 301;
colors[RED].max   = 400;
#endif

// Prototypes
FloorColor floorColor(int);
bool onColor(FloorColor, int);
bool onBlack(int);
bool onWhite(int);
bool onGrey(int);
bool onBlue(int);
bool onRed(int);

// Determine the color under the sensor
FloorColor floorColor(int sensorVal) {
	int i = 0;
	for (i = 0; i < NUM_COLORS; i++) {
		if (onColor(i, sensorVal)) {
			return i;
		}
	}
	return UNKNOWN;
}

// Determine if the floor matches the indicated color
bool onColor(FloorColor color, int sensorVal) {
	bool onColor = false;
	if (sensorVal >= COLORS[color].min && sensorVal <= COLORS[color].max) {
		onColor = true;
	}
	return onColor;
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
