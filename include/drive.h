#ifndef DRIVE_H_

#define DRIVE_H_

#include <API.h>
#include "motor.h"
#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum wheel_type {
	WHEEL_TYPE_OMNI_275,
	WHEEL_TYPE_OMNI_325,
	WHEEL_TYPE_OMNI_4
} wheel_type_t;

typedef struct wheel_s {
	motor_t      *motor;
	wheel_type_t type;
} wheel_t;

typedef struct drive_s {
	wheel_t ne; // northeast or front-right
	wheel_t nw; // northwest or front-left
	wheel_t se; // southeast or back-right
	wheel_t sw; // southwest or back-left
} drive_t;

extern bool drive_init(drive_t *drive, wheel_type_t wheel_type, motor_t *ne, motor_t *nw, motor_t *se, motor_t *sw);
extern void drive_control(drive_t *drive, control_t *control);

#ifdef __cplusplus
}
#endif

#endif
