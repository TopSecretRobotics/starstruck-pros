#ifndef ROBOT_H_

#define ROBOT_H_

#include <API.h>
#include "motor.h"
#include "pot.h"
#include "drive.h"
#include "arm.h"
#include "wrist.h"
#include "claw.h"
#include "lift.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct robot_s {
	motor_t motor[10];
	pot_t   pot[4];
	drive_t drive;
	arm_t   arm;
	wrist_t wrist;
	claw_t  claw;
	lift_t  lift;
	int8_t  reflected;
} robot_t;

extern robot_t robot;

extern bool robot_init(void);

#ifdef __cplusplus
}
#endif

#endif
