#ifndef JOYSTICK_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define JOYSTICK_H_

#include <API.h>
#include <math.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

double joystickGetPolarRadians(unsigned char joystick, unsigned char xAxis, unsigned char yAxis);
double joystickGetPolarSpeed(unsigned char joystick, unsigned char xAxis, unsigned char yAxis);

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
