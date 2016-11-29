#include "main.h"

bool
arm_init(arm_t *arm, motor_t *top, motor_t *mid, motor_t *bot, pot_t *pot, int16_t rest_position, int16_t reflected_rest_position)
{
	arm->top = top;
	arm->mid = mid;
	arm->bot = bot;
	arm->rest_position = rest_position;
	arm->reflected_rest_position = reflected_rest_position;
	arm->autolock = true;
	arm->autolock_timeout = 0;
	controller_init(&arm->lock, CONTROLLER_TYPE_PID, 1, 1, 1, 0, (sensor_t *) pot);
	arm->lock.active = false;
	return true;
}

void
arm_control(arm_t *arm, control_t *control)
{
	int speed = control->arm * robot.reflected;
	if (speed != 0) {
		arm_unlock(arm);
		arm_set(arm, speed);
		return;
	}
	if (control->action & OPERATOR_ACTION_LIFT_REST) {
		arm_lock(arm, (robot.reflected == 1) ? arm->rest_position : arm->reflected_rest_position);
		control->driver->action &= ~OPERATOR_ACTION_LIFT_REST;
		control->gunner->action &= ~OPERATOR_ACTION_LIFT_REST;
	}
	if (!arm->lock.active && arm->autolock) {
		unsigned long now = millis();
		if (arm->autolock_timeout == 0) {
			arm->lock.target_value = sensor_get(arm->lock.sensor);
			arm->autolock_timeout = now + ARM_AUTOLOCK_TIMEOUT;
		} else if (now >= arm->autolock_timeout) {
			arm->lock.active = true;
			arm->autolock_timeout = 0;
		}
	}
	speed = controller_update(&arm->lock);
	arm_set(arm, speed);
	return;
}

void
arm_set(arm_t *arm, int speed)
{
	motor_set(arm->top, speed);
	motor_set(arm->mid, speed);
	motor_set(arm->bot, speed);
	return;
}

void
arm_lock(arm_t *arm, int16_t position)
{
	arm->lock.target_value = position;
	arm->lock.active = true;
	arm->autolock_timeout = 0;
	return;
}

void
arm_unlock(arm_t *arm)
{
	arm->lock.active = false;
	arm->autolock_timeout = 0;
	return;
}
