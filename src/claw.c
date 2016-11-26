#include "main.h"

static const motor_t claw = {5, false};

#define CLAW_POWER 110

void claw_tick(joystick_t *joy) {
  if (joy->claw) {
    motorReflect(&claw, joy->ch2.value);
  } else if (joy->btn6u.pressed) {
    motorReflect(&claw, CLAW_POWER);
  } else if (joy->btn6d.pressed) {
    motorReflect(&claw, -CLAW_POWER);
  } else {
    motorReflect(&claw, 0);
  }
}