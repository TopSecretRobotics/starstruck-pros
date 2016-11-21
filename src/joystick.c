#include "main.h"

/*
 * Public API
 */

double joystickGetPolarRadians(unsigned char joystick, unsigned char xAxis, unsigned char yAxis) {
  double xValue = (double) joystickGetAnalog(joystick, xAxis);
  double yValue = (double) joystickGetAnalog(joystick, yAxis);
  double radians = atan2(yValue, xValue);
  return radians;
}

double joystickGetPolarSpeed(unsigned char joystick, unsigned char xAxis, unsigned char yAxis) {
  double xValue = (double) joystickGetAnalog(joystick, xAxis);
  double yValue = (double) joystickGetAnalog(joystick, yAxis);
  double speed = sqrt((yValue * yValue) + (xValue * xValue));
  speed /= DRIVEMOTOR_MAX_SPEED;
  speed = (speed > 1) ? 1 : speed;
  return speed;
}
