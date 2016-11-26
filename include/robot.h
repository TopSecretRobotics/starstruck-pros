#ifndef ROBOT_H_

#define ROBOT_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

// header stuff here
typedef struct robot_s {
  int8_t reflected;
} robot_t;

extern robot_t robot;

#ifdef __cplusplus
}
#endif

#endif
