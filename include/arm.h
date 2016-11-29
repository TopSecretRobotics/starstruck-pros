#ifndef ARM_H_

#define ARM_H_

#include <API.h>
#include "motor.h"
#include "pot.h"
#include "control.h"
#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ARM_AUTOLOCK_TIMEOUT 500

typedef struct arm_s {
	motor_t       *top; // top
	motor_t       *mid; // middle
	motor_t       *bot; // bottom
	int16_t       rest_position;
	int16_t       reflected_rest_position;
	bool          autolock;
	unsigned long autolock_timeout;
	controller_t  lock;
} arm_t;

extern bool arm_init(arm_t *arm, motor_t *top, motor_t *mid, motor_t *bot, pot_t *pot, int16_t rest_position, int16_t reflected_rest_position);
extern void arm_control(arm_t *arm, control_t *control);
extern void arm_set(arm_t *arm, int speed);
extern void arm_lock(arm_t *arm, int16_t position);
extern void arm_unlock(arm_t *arm);

#ifdef __cplusplus
}
#endif

#endif
