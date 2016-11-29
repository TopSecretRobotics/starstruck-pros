#include "main.h"

bool
claw_init(claw_t *claw, motor_t *motor, pot_t *pot, int16_t grab_position, int16_t open_position)
{
	claw->motor = motor;
	claw->grab_position = grab_position;
	claw->open_position = open_position;
	claw->autolock = true;
	claw->autolock_timeout = 0;
	controller_init(&claw->lock, CONTROLLER_TYPE_PID, 1, 1, 1, 0, (sensor_t *) pot);
	claw->lock.active = false;
	return true;
}

void
claw_control(claw_t *claw, control_t *control)
{
	int speed = control->claw;
	if (speed != 0) {
		claw_unlock(claw);
		claw_set(claw, speed);
		return;
	}
	if ((control->mode & OPERATOR_MODE_CLAW_GRAB) && (control->mode & OPERATOR_MODE_CLAW_OPEN)) {
		// both grab and open are set, just ignore them since they cancel each other out
		control->mode &= ~OPERATOR_MODE_CLAW_GRAB;
		control->mode &= ~OPERATOR_MODE_CLAW_OPEN;
	}
	if (control->mode & OPERATOR_MODE_CLAW_GRAB) {
		claw_lock(claw, claw->grab_position);
	} else if (control->mode & OPERATOR_MODE_CLAW_OPEN) {
		claw_lock(claw, claw->open_position);
	} else if (control->last_mode & (OPERATOR_MODE_CLAW_GRAB | OPERATOR_MODE_CLAW_OPEN)) {
		// grab or open was just released, so immediately lock the claw in position
		claw_lock(claw, sensor_get(claw->lock.sensor));
	}
	if (!claw->lock.active && claw->autolock) {
		unsigned long now = millis();
		if (claw->autolock_timeout == 0) {
			claw->lock.target_value = sensor_get(claw->lock.sensor);
			claw->autolock_timeout = now + CLAW_AUTOLOCK_TIMEOUT;
		} else if (now >= claw->autolock_timeout) {
			claw->lock.active = true;
			claw->autolock_timeout = 0;
		}
	}
	speed = controller_update(&claw->lock);
	claw_set(claw, speed);
	return;
}

void
claw_set(claw_t *claw, int speed)
{
	motor_set(claw->motor, speed);
	return;
}

void
claw_lock(claw_t *claw, int16_t position)
{
	claw->lock.target_value = position;
	claw->lock.active = true;
	claw->autolock_timeout = 0;
	return;
}

void
claw_unlock(claw_t *claw)
{
	claw->lock.active = false;
	claw->autolock_timeout = 0;
	return;
}
