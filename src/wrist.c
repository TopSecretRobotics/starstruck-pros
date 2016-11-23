#include "main.h"

static const motor_t wrist = {7};

void wrist_tick(void) {
  // for Motors in Port 7
  if(joystickGetDigital(1, 5, JOY_UP) == 1){
    motorReflect(&wrist, 127);
  }

  if(joystickGetDigital(1, 5, JOY_DOWN) == 1){
    motorReflect(&wrist, -127);
  }

  if((joystickGetDigital(1, 5, JOY_UP) == 0) && (joystickGetDigital(1, 5, JOY_DOWN) == 0)){
    motorReflect(&wrist, 0);
  }
}
