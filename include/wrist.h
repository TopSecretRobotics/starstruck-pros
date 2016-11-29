#ifndef WRIST_H_

#define WRIST_H_

#include <API.h>
#include "motor.h"
#include "pot.h"
#include "control.h"
#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WRIST_AUTOLOCK_TIMEOUT 500

typedef struct wrist_s {
	motor_t       *motor;
	int16_t       rest_position;
	int16_t       reflected_rest_position;
	bool          autolock;
	unsigned long autolock_timeout;
	controller_t  lock;
} wrist_t;

extern bool wrist_init(wrist_t *wrist, motor_t *motor, pot_t *pot, int16_t rest_position, int16_t reflected_rest_position);
extern void wrist_control(wrist_t *wrist, control_t *control);
extern void wrist_set(wrist_t *wrist, int speed);
extern void wrist_lock(wrist_t *wrist, int16_t position);
extern void wrist_unlock(wrist_t *wrist);

#ifdef __cplusplus
}
#endif

#endif
