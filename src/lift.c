#include "main.h"

void lift_tick(joystick_t *joy) {
  if (joy == NULL) {
    // maybe stop arm?
    return;
  }
  arm_tick(joy);
  wrist_tick(joy);
  claw_tick(joy);
  return;
}
