#include "main.h"

bool
wrist_init(wrist_t *wrist, motor_t *motor, pot_t *pot, int16_t rest_position, int16_t reflected_rest_position)
{
	wrist->motor = motor;
	wrist->rest_position = rest_position;
	wrist->reflected_rest_position = reflected_rest_position;
	wrist->autolock = false;
	wrist->autolock_timeout = 0;
	controller_init(&wrist->lock, CONTROLLER_TYPE_PID, 1, 1, 1, 0, (sensor_t *) pot);
	wrist->lock.active = false;
	return true;
}

void
wrist_control(wrist_t *wrist, control_t *control)
{
	int speed = control->wrist * robot.reflected;
	if (speed != 0) {
		wrist_unlock(wrist);
		wrist_set(wrist, speed);
		return;
	}
	if (control->action & OPERATOR_ACTION_WRIST_REST) {
		wrist_lock(wrist, (robot.reflected == 1) ? wrist->rest_position : wrist->reflected_rest_position);
		control->driver->action &= ~OPERATOR_ACTION_WRIST_REST;
		control->gunner->action &= ~OPERATOR_ACTION_WRIST_REST;
	}
	if (!wrist->lock.active && wrist->autolock) {
		unsigned long now = millis();
		if (wrist->autolock_timeout == 0) {
			wrist->lock.target_value = sensor_get(wrist->lock.sensor);
			wrist->autolock_timeout = now + WRIST_AUTOLOCK_TIMEOUT;
		} else if (now >= wrist->autolock_timeout) {
			wrist->lock.active = true;
			wrist->autolock_timeout = 0;
		}
	}
	speed = controller_update(&wrist->lock);
	wrist_set(wrist, speed);
	return;
}

void
wrist_set(wrist_t *wrist, int speed)
{
	motor_set(wrist->motor, speed);
	return;
}

void
wrist_lock(wrist_t *wrist, int16_t position)
{
	wrist->lock.target_value = position;
	wrist->lock.active = true;
	wrist->autolock_timeout = 0;
	return;
}

void
wrist_unlock(wrist_t *wrist)
{
	wrist->lock.active = false;
	wrist->autolock_timeout = 0;
	return;
}
