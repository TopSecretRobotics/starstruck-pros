#ifndef MOTOR_H_

#define MOTOR_H_

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

// header stuff here

typedef struct motor_s {
	unsigned char channel;
	bool reflected;
} motor_t;

void motorReflect(const motor_t *motor, int speed);

#ifdef __cplusplus
}
#endif

#endif
