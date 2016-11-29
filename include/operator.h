#ifndef OPERATOR_H_

#define OPERATOR_H_

#include <API.h>
#include "gamepad.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OPERATOR_ROLE_DRIVER 0
#define OPERATOR_ROLE_GUNNER 1

#define OPERATOR_MODE_NONE      0x00
#define OPERATOR_MODE_CLAW_CTRL 0x01
#define OPERATOR_MODE_CLAW_GRAB 0x02
#define OPERATOR_MODE_CLAW_OPEN 0x04
#define OPERATOR_MODE_ROLE_SWAP 0x08

#define OPERATOR_ACTION_NONE       0x00
#define OPERATOR_ACTION_LIFT_DUMP  0x01
#define OPERATOR_ACTION_LIFT_REST  0x02
#define OPERATOR_ACTION_LIFT_TOSS  0x04
#define OPERATOR_ACTION_ROBOT_FLIP 0x08
#define OPERATOR_ACTION_WRIST_REST 0x10

typedef struct operator_s {
	uint8_t   role;
	uint8_t   mode;
	uint8_t   action;
	gamepad_t gamepad;
} operator_t;

extern operator_t *operator_init(operator_t *op, unsigned char joystick, uint8_t role);
extern void operator_update(operator_t *op);

#ifdef __cplusplus
}
#endif

#endif
