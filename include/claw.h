#ifndef CLAW_H_

#define CLAW_H_

#include <API.h>
#include "motor.h"
#include "pot.h"
#include "control.h"
#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLAW_AUTOLOCK_TIMEOUT 500

typedef struct claw_s {
	motor_t       *motor;
	int16_t       grab_position;
	int16_t       open_position;
	bool          autolock;
	unsigned long autolock_timeout;
	controller_t  lock;
} claw_t;

extern bool claw_init(claw_t *claw, motor_t *motor, pot_t *pot, int16_t grab_position, int16_t open_position);
extern void claw_control(claw_t *claw, control_t *control);
extern void claw_set(claw_t *claw, int speed);
extern void claw_lock(claw_t *claw, int16_t position);
extern void claw_unlock(claw_t *claw);

#ifdef __cplusplus
}
#endif

#endif
