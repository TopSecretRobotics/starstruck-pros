#include "main.h"

static const motor_t armT = {8, false};
static const motor_t armC = {7, true};
static const motor_t armB = {3, true};

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
	// for Motors in Ports 8 & 7 & 3
	arm_set(joy->ch3.value * robot.reflected);
}

void arm_set(int speed) {
	motorReflect(&armT, speed);
	motorReflect(&armC, speed);
	motorReflect(&armB, speed);
}

void arm_maintain(int speed, unsigned long milliseconds) {
	unsigned long start_time = millis();
	unsigned long current_time = start_time;
	while ((current_time - start_time) < milliseconds) {
		arm_set(speed);
		current_time = millis();
		delay(20);
	}
}

// void arm_until(int speed, int target) {
// 	int current = analogRead(1);
// 	while (current < target) {
// 		arm_set(speed);
// 		current = analogRead(1);
// 		delay(20);
// 	}
// }
