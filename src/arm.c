#include "main.h"

static const motor_t middleRArm  = {8};
static const motor_t middleLArm  = {9};

void arm_tick(void) {
// for Motors in Ports 8 & 9
// 		if (joystickGetDigital(1, 6, JOY_UP ) == 1){
// 			motorReflect(&middleRArm, 127);
// 			motorReflect(&middleLArm, 127);
// 		}
//
// 		if(joystickGetDigital(1, 6, JOY_UP) == 0){
// 			motorReflect(&middleRArm, 0);
// 			motorReflect(&middleLArm, 0);
// 		}
//
// 		if (joystickGetDigital(1, 6, JOY_DOWN ) == 1){
// 			motorReflect(&middleRArm, -127);
// 			motorReflect(&middleLArm, -127);
// 		}
//
// 		if(joystickGetDigital(1, 6, JOY_DOWN) == 0){
// 			motorReflect(&middleRArm, 0);
// 			motorReflect(&middleLArm, 0);
// 		}
}
