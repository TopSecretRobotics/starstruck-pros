#ifndef DRIVE_H_

#define DRIVE_H_

#include <API.h>
#include "motor.h"
#include "robot.h"
#include "joystick.h"

#ifdef __cplusplus
extern "C" {
#endif

// header stuff here

void drive_tick(joystick_t *joy);

#ifdef __cplusplus
}
#endif

#endif
