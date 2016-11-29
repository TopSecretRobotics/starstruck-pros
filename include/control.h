#ifndef CONTROL_H_

#define CONTROL_H_

#include <API.h>
#include "operator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct control_s {
	uint8_t    action;
	uint8_t    mode;
	uint8_t    last_mode;
	int8_t     arm;
	int8_t     claw;
	int8_t     drive_x;
	int8_t     drive_y;
	int8_t     drive_r;
	int8_t     wrist;
	operator_t op[2];
	operator_t *driver;
	operator_t *gunner;
} control_t;

extern bool control_init(control_t *control);
extern void control_update(control_t *control);

#ifdef __cplusplus
}
#endif

#endif
