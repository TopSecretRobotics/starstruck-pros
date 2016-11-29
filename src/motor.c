#include "main.h"

bool
motor_init(motor_t *motor, unsigned char channel, uint8_t flags, motor_type_t type, motor_gearing_t gearing)
{
	if (channel > 10) {
		return false;
	}
	motor->channel = channel;
	motor->flags = flags | MOTOR_FLAG_READY;
	motor->__pad0__ = 0;
	motor->type = type;
	motor->gearing = gearing;
	return true;
}

int
motor_get(const motor_t *motor)
{
	int speed = motorGet(motor->channel);
	if (motor->flags & MOTOR_FLAG_REFLECTED) {
		return -speed;
	} else {
		return speed;
	}
}

bool
motor_has_encoder(const motor_t *motor)
{
	return (motor->flags & MOTOR_FLAG_ENCODER);
}

bool
motor_is_expanded(const motor_t *motor)
{
	return (motor->flags & MOTOR_FLAG_EXPANDED);
}

bool
motor_is_ready(const motor_t *motor)
{
	return (motor->flags & MOTOR_FLAG_READY);
}

bool
motor_is_reflected(const motor_t *motor)
{
	return (motor->flags & MOTOR_FLAG_REFLECTED);
}

bool
motor_is_y_cabled(const motor_t *motor)
{
	return (motor->flags & MOTOR_FLAG_Y_CABLED);
}

void
motor_set(const motor_t *motor, int speed)
{
	if (speed == 0) {
		motor_stop(motor);
		return;
	}
	if (motor->flags & MOTOR_FLAG_REFLECTED) {
		speed = -speed;
	}
	if (speed > 127) {
		speed = 127;
	} else if (speed < -127) {
		speed = -127;
	}
	motorSet(motor->channel, speed);
	return;
}

void
motor_stop(const motor_t *motor)
{
	motorStop(motor->channel);
	return;
}
