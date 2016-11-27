#include "main.h"

static const motor_t frontRDrive = {9, true};
static const motor_t frontLDrive = {2, false};
static const motor_t backRDrive  = {10, false};
static const motor_t backLDrive  = {1, false};

void drive_tick(joystick_t *joy) {
  if (joy == NULL) {
    motorReflect(&frontRDrive, 0);
    motorReflect(&frontLDrive, 0);
    motorReflect(&backRDrive, 0);
    motorReflect(&backLDrive, 0);
    return;
  }
  int xValue = joy->ch4.value;
  int yValue = joy->ch3.value;
  // int rValue = ((joy->claw) ? 0 : joy->ch1.value) * robot.reflected;
  int rValue = joy->ch1.value * robot.reflected;
  motorReflect(&frontRDrive, (yValue - xValue - rValue) * robot.reflected);
  motorReflect(&frontLDrive, (yValue + xValue + rValue) * robot.reflected);
  motorReflect(&backRDrive,  (yValue + xValue - rValue) * robot.reflected);
  motorReflect(&backLDrive,  (yValue - xValue + rValue) * robot.reflected);
}
