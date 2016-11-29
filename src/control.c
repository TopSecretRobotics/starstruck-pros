#include "main.h"

static inline void
control_reset(control_t *control)
{
	control->action  = OPERATOR_ACTION_NONE;
	control->mode    = OPERATOR_MODE_NONE;
	control->arm     = 0;
	control->claw    = 0;
	control->drive_x = 0;
	control->drive_y = 0;
	control->drive_r = 0;
	control->wrist   = 0;
	return;
}

static void control_update_driver(control_t *control, operator_t *op);
static void control_update_gunner(control_t *control, operator_t *op);

bool
control_init(control_t *control)
{
	control->last_mode = OPERATOR_MODE_NONE;
	control_reset(control);
	control->driver = operator_init(&control->op[0], 1, OPERATOR_ROLE_DRIVER);
	control->gunner = operator_init(&control->op[1], 2, OPERATOR_ROLE_GUNNER);
	return true;
}

void
control_update(control_t *control)
{
	control->last_mode = control->mode;
	control_reset(control);

	operator_update(control->driver);
	operator_update(control->gunner);

	if (control->driver->mode & OPERATOR_MODE_ROLE_SWAP) {
		control_update_gunner(control, control->driver);
	} else {
		control_update_driver(control, control->driver);
	}

	if (control->gunner->mode & OPERATOR_MODE_ROLE_SWAP) {
		control_update_driver(control, control->gunner);
	} else {
		control_update_gunner(control, control->gunner);
	}

	control->action |= (control->driver->action | control->gunner->action);
	control->mode   |= (control->driver->mode | control->gunner->mode);
	control->mode   &= ~OPERATOR_MODE_CLAW_CTRL;
	control->mode   &= ~OPERATOR_MODE_ROLE_SWAP;

	return;
}

static void
control_update_driver(control_t *control, operator_t *op)
{
	control->drive_x += op->gamepad.ch4->value;
	control->drive_y += op->gamepad.ch3->value;
	if (op->mode & OPERATOR_MODE_CLAW_CTRL) {
		control->claw += op->gamepad.ch2->value;
	} else {
		control->drive_r += op->gamepad.ch1->value;
	}
}

static void
control_update_gunner(control_t *control, operator_t *op)
{
	control->arm += op->gamepad.ch3->value;
	if (op->mode & OPERATOR_MODE_CLAW_CTRL) {
		control->claw += op->gamepad.ch2->value;
	} else {
		control->wrist += op->gamepad.ch2->value;
	}
}
