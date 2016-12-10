#include "main.h"

static void op_action_lift_dump(void *data);
static void op_action_lift_rest(void *data);
static void op_action_lift_toss(void *data);
static void op_action_robot_flip(void *data);
static void op_action_wrist_rest(void *data);

static void op_mode_claw_ctrl_off(void *data);
static void op_mode_claw_ctrl_on(void *data);
static void op_mode_claw_grab_off(void *data);
static void op_mode_claw_grab_on(void *data);
static void op_mode_claw_open_off(void *data);
static void op_mode_claw_open_on(void *data);
static void op_mode_role_swap_off(void *data);
static void op_mode_role_swap_on(void *data);

/* Public Functions */

#define BIND(OP, BUTTON, EVENT, CB, DEBOUNCE, THROTTLE) gamepad_listen(&((OP)->gamepad.BUTTON->on_ ## EVENT), (CB), (void *) (OP), (DEBOUNCE), (THROTTLE))

operator_t *
operator_init(operator_t *op, unsigned char joystick, uint8_t role)
{
	gamepad_init(&op->gamepad, joystick);

	op->role   = (role == OPERATOR_ROLE_DRIVER) ? role : OPERATOR_ROLE_GUNNER;
	op->mode   = OPERATOR_MODE_NONE;
	op->action = OPERATOR_ACTION_NONE;

	BIND(op, btn7r, click,   op_action_lift_dump,   0, 1000);
	BIND(op, btn7u, click,   op_action_lift_rest,   0, 1000);
	BIND(op, btn7l, click,   op_action_lift_toss,   0, 1000);
	BIND(op, btn8u, click,   op_action_robot_flip,  0, 1000);
	BIND(op, btn7d, click,   op_action_wrist_rest,  0, 1000);

	BIND(op, btn5u, release, op_mode_claw_ctrl_off, 0, 0);
	BIND(op, btn5u, press,   op_mode_claw_ctrl_on,  0, 0);
	BIND(op, btn6u, release, op_mode_claw_grab_off, 0, 0);
	BIND(op, btn6u, press,   op_mode_claw_grab_on,  0, 0);
	BIND(op, btn6d, release, op_mode_claw_open_off, 0, 0);
	BIND(op, btn6d, press,   op_mode_claw_open_on,  0, 0);
	BIND(op, btn5d, release, op_mode_role_swap_off, 0, 0);
	BIND(op, btn5d, press,   op_mode_role_swap_on,  0, 0);

	return op;
}

#undef BIND

void
operator_update(operator_t *op)
{
	gamepad_update(&(op->gamepad));
	return;
}

/* Callback Functions */

static void
op_action_lift_dump(void *data)
{
	operator_t *op = (operator_t *) data;
	op->action |= OPERATOR_ACTION_LIFT_DUMP;
	return;
}

static void
op_action_lift_rest(void *data)
{
	operator_t *op = (operator_t *) data;
	op->action |= OPERATOR_ACTION_LIFT_REST | OPERATOR_ACTION_WRIST_REST;
	return;
}

static void
op_action_lift_toss(void *data)
{
	operator_t *op = (operator_t *) data;
	op->action |= OPERATOR_ACTION_LIFT_TOSS;
	return;
}

static void
op_action_robot_flip(void *data)
{
	operator_t *op = (operator_t *) data;
	op->action |= OPERATOR_ACTION_ROBOT_FLIP;
	return;
}

static void
op_action_wrist_rest(void *data)
{
	operator_t *op = (operator_t *) data;
	op->action |= OPERATOR_ACTION_WRIST_REST;
	return;
}

static void
op_mode_claw_ctrl_off(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode &= ~OPERATOR_MODE_CLAW_CTRL;
	return;
}

static void
op_mode_claw_ctrl_on(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode |= OPERATOR_MODE_CLAW_CTRL;
	return;
}

static void
op_mode_claw_grab_off(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode &= ~OPERATOR_MODE_CLAW_GRAB;
	return;
}

static void
op_mode_claw_grab_on(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode |= OPERATOR_MODE_CLAW_GRAB;
	return;
}

static void
op_mode_claw_open_off(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode &= ~OPERATOR_MODE_CLAW_OPEN;
	return;
}

static void
op_mode_claw_open_on(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode |= OPERATOR_MODE_CLAW_OPEN;
	return;
}

static void
op_mode_role_swap_off(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode &= ~OPERATOR_MODE_ROLE_SWAP;
	return;
}

static void
op_mode_role_swap_on(void *data)
{
	operator_t *op = (operator_t *) data;
	op->mode |= OPERATOR_MODE_ROLE_SWAP;
	return;
}
