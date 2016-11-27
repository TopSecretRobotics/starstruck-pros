#include "main.h"

static void back_throw(void);
static void return_to_start(void);

void lift_tick(joystick_t *joy) {
  if (joy->btn7l.pressed) {
    back_throw();
    return;
  }
  if (joy->btn7u.pressed) {
    return_to_start();
    return;
  }
  if (joy == NULL) {
    // maybe stop arm?
    return;
  }
  arm_tick(joy);
  wrist_tick(joy);
  claw_tick(joy);
  return;
}

/* Internal Functions */

static void back_throw(void) {
  arm_maintain(127 * robot.reflected, 100);
  arm_maintain(110 * robot.reflected, 500);
  arm_set(0);
  // return_to_start();
  return;
}

static void return_to_start(void) {
  return;
}
