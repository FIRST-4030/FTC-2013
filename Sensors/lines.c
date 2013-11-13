// Set this to select a configuration set
#define LIGHT_SENSOR_CONFIG_1

// Configuration data set 1
#ifdef LIGHT_SENSOR_CONFIG_1
#define BLACK_MIN 0
#define BLACK_MAX 100
#define WHITE_MIN 401
#define WHITE_MAX 10000
#define GREY_MIN 101
#define GREY_MAX 200
#define BLUE_MIN 201
#define BLUE_MAX 300
#define RED_MIN 301
#define RED_MAX 400
#endif

// Configuration data set 2
#ifdef LIGHT_SENSOR_CONFIG_2
#define BLACK_MIN 0
#define BLACK_MAX 100
#define WHITE_MIN 401
#define WHITE_MAX 10000
#define GREY_MIN 101
#define GREY_MAX 200
#define BLUE_MIN 201
#define BLUE_MAX 300
#define RED_MIN 301
#define RED_MAX 400
#endif

// Which colors can we detect
typedef enum {
	BLACK,
	WHITE,
	GREY,
	BLUE,
	RED,
	UNKNOWN
} FloorColor;

// Prototypes
FloorColor floorColor(int);
bool onBlack(int);
bool onWhite(int);
bool onGrey(int);
bool onBlue(int);
bool onRed(int);

// Determine the color under the sensor
FloorColor floorColor(int sensor) {
	FloorColor color = UNKNOWN;
	if (onBlack(sensor)) {
		color = BLACK;
	} else if (onWhite(sensor)) {
		color = WHITE;
	} else if (onGrey(sensor)) {
		color = GREY;
	} else if (onBlue(sensor)) {
		color = BLUE;
	} else if (onRed(sensor)) {
		color = RED;
	}
	return color;
}

bool onBlack(int sensor) {
	bool onColor = false;
	if (sensor >= BLACK_MIN && sensor <= BLACK_MAX) {
		onColor = true;
	}
	return onColor;
}

bool onWhite(int sensor) {
	bool onColor = false;
	if (sensor >= WHITE_MIN && sensor <= WHITE_MAX) {
		onColor = true;
	}
	return onColor;
}

bool onGrey(int sensor) {
	bool onColor = false;
	if (sensor >= GREY_MIN && sensor <= GREY_MAX) {
		onColor = true;
	}
	return onColor;
}

bool onBlue(int sensor) {
	bool onColor = false;
	if (sensor >= BLUE_MIN && sensor <= BLUE_MAX) {
		onColor = true;
	}
	return onColor;
}

bool onRed(int sensor) {
	bool onColor = false;
	if (sensor >= RED_MIN && sensor <= RED_MAX) {
		onColor = true;
	}
	return onColor;
}
