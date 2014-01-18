#ifndef FTC_AUTO_INCLUDES
#define FTC_AUTO_INCLUDES

///// Sensor Multiplexer Interface /////
#include "../drivers/hitechnic-sensormux.h"
const tMUXSensor sonarSensor = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;

// Other Includes //
#include "../Sensors/light.c"
#include "../Sensors/ir.c"
#include "../Sensors/sonar.c"
#include "../Motors/motors.c"
#include "../Motors/servos.c"
#include "../Drive/lines.c"
#include "../Drive/drive.c"
#include "../Drive/drive_auto.c"
#include "JoystickDriver.c"

#include "auto_init.c"
#include "auto_functions.c"

#endif
