#ifndef UTIL_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define UTIL_H_

#include <API.h>
#include <math.h>
#include <stdarg.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

double fabsmax(int argc, ...);
double fabsmin(int argc, ...);

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
