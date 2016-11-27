#include "lift.h"

#ifndef ARM_H_

#define ARM_H_

#ifdef __cplusplus
extern "C" {
#endif

// header stuff here

void arm_tick(joystick_t *joy);
void arm_set(int speed);
void arm_maintain(int speed, unsigned long milliseconds);

#ifdef __cplusplus
}
#endif

#endif
