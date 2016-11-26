#ifndef JOYSTICK_H_

#define JOYSTICK_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

// header stuff here
#define JOY_MODE_DRV 0
#define JOY_MODE_ARM 1

#define JOY_TIMEOUT_MODE 1000
#define JOY_TIMEOUT_INVERT 1000

typedef struct button_s {
  unsigned char group;
  unsigned char button;
  bool pressed;
  unsigned long fire_time;
  unsigned long last_fire_time;
} button_t;

typedef struct stick_s {
  unsigned char axis;
  uint8_t deadband;
  int8_t value;
} stick_t;

typedef struct joystick_s {
  unsigned char joystick;
  uint8_t mode;
  bool claw;
  button_t btn5d;
  button_t btn5u;
  button_t btn6d;
  button_t btn6u;
  button_t btn7d;
  button_t btn7u;
  button_t btn7l;
  button_t btn7r;
  button_t btn8d;
  button_t btn8u;
  button_t btn8l;
  button_t btn8r;
  stick_t ch1;
  stick_t ch2;
  stick_t ch3;
  stick_t ch4;
} joystick_t;

void joystickInit(joystick_t *joy, unsigned char joystick, uint8_t mode);
void joystickTick(joystick_t *joy);

#ifdef __cplusplus
}
#endif

#endif
