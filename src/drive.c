#include "main.h"

static const motor_t frontRDrive = {3, true};
static const motor_t frontLDrive = {5};
static const motor_t backRDrive  = {2, true};
static const motor_t backLDrive  = {4};

void drive_tick(void) {
  int forwardsBackwardsValue = joystickGetAnalog(1, 3);
  int rotationValue = joystickGetAnalog(1, 4);
  int driftValue = joystickGetAnalog(1, 1);
  if (joystickGetDigital(1, 7, JOY_RIGHT) == 1) {
    driftValue = 0;
  }
  motorReflect(&frontRDrive, forwardsBackwardsValue - driftValue - rotationValue);
  motorReflect(&frontLDrive, forwardsBackwardsValue + driftValue + rotationValue);
  motorReflect(&backRDrive,  forwardsBackwardsValue + driftValue - rotationValue);
  motorReflect(&backLDrive,  forwardsBackwardsValue - driftValue + rotationValue);
}
