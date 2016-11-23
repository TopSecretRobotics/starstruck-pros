#include "main.h"

void motorReflect(const motor_t *motor, int speed) {
  if (speed == 0) {
		motorStop(motor->channel);
		return;
	}
	if (motor->reflected) {
		speed *= -1;
	}
	motorSet(motor->channel, speed);
}
