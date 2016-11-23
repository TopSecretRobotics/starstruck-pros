#include "main.h"

static const motor_t claw = {6};

void claw_tick(void) {
  if (joystickGetDigital(1, 7, JOY_RIGHT) == 1) {
    motorReflect(&claw, joystickGetAnalog(1, 2));
  }
  // if(joystickGetDigital(1, 8, JOY_RIGHT) == 1){
  // 	motorReflect(&claw, 127);
  // }
  //
  // if(joystickGetDigital(1, 8, JOY_DOWN) == 1){
  // 	motorReflect(&claw, -127);
  // }
  //
  // if((joystickGetDigital(1, 8, JOY_RIGHT) == 0) && (joystickGetDigital(1, 8, JOY_DOWN) == 0)){
  // 	motorReflect(&claw, 0);
  // }
}
