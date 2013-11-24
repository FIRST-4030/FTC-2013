#ifndef FTC_TELEOP_INCLUDES
#define FTC_TELEOP_INCLUDES

// Sensor Includes //
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"
///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;
// Light Sensor Functions //
#include "sensors/lights.c"

// Teleop Includes
#include "JoystickDriver.c"
#include "sensors/colors.c"
#include "motors/servos.c"
#include "motors/motors.c"
#include "drive/lines.c"
#include "drive/drive.c"

#include "init_robot.c";

#endif
