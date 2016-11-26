#include "main.h"

static const motor_t armT = {8, false};
static const motor_t armC = {7, true};
static const motor_t armB = {6, true};

// #define ARM_POWER 90

// static void motorCap(const motor_t *motor, int speed) {
// 	if (speed > 100) {
// 		speed = 100;
// 	} else if (speed < -100) {
// 		speed = -100;
// 	}
// 	motorReflect(motor, speed);
// }

void arm_tick(joystick_t *joy) {
	// for Motors in Ports 8 & 7 & 6
	motorReflect(&armT, joy->ch3.value * robot.reflected);
	motorReflect(&armC, joy->ch3.value * robot.reflected);
	motorReflect(&armB, joy->ch3.value * robot.reflected);
}
