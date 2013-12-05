#ifndef FTC_AUTO_INCLUDES
#define FTC_AUTO_INCLUDES
// Sensor Includes //
#include "../drivers/hitechnic-sensormux.h"
#include "../drivers/hitechnic-irseeker-v2.h"
#include "../drivers/lego-ultrasound.h"
#include "../drivers/lego-touch.h"
#include "../drivers/lego-light.h"
///// Sensor Multiplexer Interface /////
const tMUXSensor sonar = msensor_S2_1;
const tMUXSensor IRSeeker = msensor_S2_2;
const tMUXSensor lightRight = msensor_S2_3;
const tMUXSensor lightLeft = msensor_S2_4;
// Light Sensor Functions //
#include "../sensors/lights.c"

// Other Includes //
#include "../sensors/colors.c"
#include "../Motors/motors.c"
#include "../Motors/servos.c"
#include "../Drive/lines.c"
#include "../Drive/drive.c"
#include "../Drive/drive_auto.c"
#include "JoystickDriver.c"

#include "auto_init.c"
#include "auto_functions.c"

#endif