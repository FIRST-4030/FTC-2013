#ifndef FTC_TELEOPINCLUDES
#define FTC_TELEOPINCLUDES

// Sensor Includes //
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"
///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;
// Light Sensor Functions //
#include "Sensors/lights.c"

// Teleop Includes
#include "JoystickDriver.c"
#include "sensors/colors.c"
#include "Motors/servos.c"
#include "Motors/motors.c"
#include "Drive/lines.c"
#include "Drive/drive.c"

#include "InitRobot.c";

#endif
