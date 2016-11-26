#include "main.h"

static void joystickButtonInit(button_t *btn, unsigned char buttonGroup, unsigned char button);
static void joystickButtonTick(joystick_t *joy, button_t *btn);
static void joystickButtonFire(button_t *btn, unsigned long now);
static void joystickStickInit(stick_t *ch, unsigned char axis, uint8_t deadband);
static void joystickStickTick(joystick_t *joy, stick_t *ch);

void joystickInit(joystick_t *joy, unsigned char joystick, uint8_t mode) {
  joy->joystick = joystick;
  joy->mode = mode;
  joy->claw = false;
  joystickButtonInit(&joy->btn5d, 5, JOY_DOWN);
  joystickButtonInit(&joy->btn5u, 5, JOY_UP);
  joystickButtonInit(&joy->btn6d, 6, JOY_DOWN);
  joystickButtonInit(&joy->btn6u, 6, JOY_UP);
  joystickButtonInit(&joy->btn7d, 7, JOY_DOWN);
  joystickButtonInit(&joy->btn7u, 7, JOY_UP);
  joystickButtonInit(&joy->btn7l, 7, JOY_LEFT);
  joystickButtonInit(&joy->btn7r, 7, JOY_RIGHT);
  joystickButtonInit(&joy->btn8d, 8, JOY_DOWN);
  joystickButtonInit(&joy->btn8u, 8, JOY_UP);
  joystickButtonInit(&joy->btn8l, 8, JOY_LEFT);
  joystickButtonInit(&joy->btn8r, 8, JOY_RIGHT);
  joystickStickInit(&joy->ch1, 1, 10);
  joystickStickInit(&joy->ch2, 2, 10);
  joystickStickInit(&joy->ch3, 3, 10);
  joystickStickInit(&joy->ch4, 4, 10);
}

void joystickTick(joystick_t *joy) {
  unsigned long now = millis();
  joystickButtonTick(joy, &joy->btn5d);
  joystickButtonTick(joy, &joy->btn5u);
  joystickButtonTick(joy, &joy->btn6d);
  joystickButtonTick(joy, &joy->btn6u);
  joystickButtonTick(joy, &joy->btn7d);
  joystickButtonTick(joy, &joy->btn7u);
  joystickButtonTick(joy, &joy->btn7l);
  joystickButtonTick(joy, &joy->btn7r);
  joystickButtonTick(joy, &joy->btn8d);
  joystickButtonTick(joy, &joy->btn8u);
  joystickButtonTick(joy, &joy->btn8l);
  joystickButtonTick(joy, &joy->btn8r);
  joystickStickTick(joy, &joy->ch1);
  joystickStickTick(joy, &joy->ch2);
  joystickStickTick(joy, &joy->ch3);
  joystickStickTick(joy, &joy->ch4);
  if (joy->btn5d.pressed && (now - joy->btn5d.fire_time) >= JOY_TIMEOUT_MODE) {
    if (joy->mode == JOY_MODE_ARM) {
      joy->mode = JOY_MODE_DRV;
    } else {
      joy->mode = JOY_MODE_ARM;
    }
    joystickButtonFire(&joy->btn5d, now);
  }
  if (joy->btn5u.pressed && !joy->claw) {
    joy->claw = true;
  } else if (!joy->btn5u.pressed && joy->claw) {
    joy->claw = false;
  }
  if (joy->btn8u.pressed && (now - joy->btn8u.fire_time) >= JOY_TIMEOUT_INVERT) {
    robot.reflected *= -1;
    joystickButtonFire(&joy->btn8u, now);
  }
  // if (joy->mode == JOY_MODE_ARM) {
  //
  // } else {
  //
  // }
}

/* Internal Functions */

static void joystickButtonInit(button_t *btn, unsigned char buttonGroup, unsigned char button) {
  btn->group = buttonGroup;
  btn->button = button;
  btn->pressed = false;
  btn->fire_time = 0;
  btn->last_fire_time = 0;
}

static void joystickButtonTick(joystick_t *joy, button_t *btn) {
  if (btn->pressed != joystickGetDigital(joy->joystick, btn->group, btn->button)) {
    if (btn->pressed == false) {
      btn->pressed = true;
    } else {
      btn->pressed = false;
    }
  }
}

static void joystickButtonFire(button_t *btn, unsigned long now) {
  btn->last_fire_time = btn->fire_time;
  btn->fire_time = now;
}

static void joystickStickInit(stick_t *ch, unsigned char axis, uint8_t deadband) {
  ch->axis = axis;
  ch->deadband = deadband;
  ch->value = 0;
}

static void joystickStickTick(joystick_t *joy, stick_t *ch) {
  int value = joystickGetAnalog(joy->joystick, ch->axis);
  if (abs(value) >= ch->deadband) {
    ch->value = value;
  } else {
    ch->value = 0;
  }
}
