#ifndef LIFT_H_

#define LIFT_H_

#include <API.h>
#include "motor.h"
#include "robot.h"
#include "control.h"
#include "arm.h"
#include "wrist.h"
#include "claw.h"
#include "pot.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lift_s {
	arm_t   *arm;
	wrist_t *wrist;
	claw_t  *claw;
	pot_t   *tuner;
} lift_t;

extern bool lift_init(lift_t *lift, arm_t *arm, wrist_t *wrist, claw_t *claw, pot_t *tuner);
extern void lift_control(lift_t *lift, control_t *control);

#ifdef __cplusplus
}
#endif

#endif
