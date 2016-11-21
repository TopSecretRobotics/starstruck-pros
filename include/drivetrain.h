#ifndef DRIVETRAIN_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define DRIVETRAIN_H_

#include <API.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

#define DRIVETRAIN_TYPE_BASIC_XDRIVE 0
#define DRIVETRAIN_TYPE_HOLONOMIC_XDRIVE 1

typedef struct drivetrain_s {
  uint8_t type;
  void (*tick)(void *data);
  void *data;
} drivetrain_t;

drivetrain_t *drivetrainGet(void);
bool drivetrainSet(uint8_t type);
void drivetrainTick(void);

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
