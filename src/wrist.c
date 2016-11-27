#include "main.h"

static const motor_t wrist = {6, false};

void wrist_tick(joystick_t *joy) {
  // for Motors in Port 7
  if (!joy->claw) {
    motorReflect(&wrist, joy->ch2.value * robot.reflected);
  }else {
    motorReflect(&wrist, 0);
  }
  // if(joystickGetDigital(1, 5, JOY_UP) == 1){
  //   motorReflect(&wrist, 127);
  // }
  //
  // if(joystickGetDigital(1, 5, JOY_DOWN) == 1){
  //   motorReflect(&wrist, -127);
  // }
  //
  // if((joystickGetDigital(1, 5, JOY_UP) == 0) && (joystickGetDigital(1, 5, JOY_DOWN) == 0)){
  //   motorReflect(&wrist, 0);
  // }
}
