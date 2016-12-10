/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

// static void debugJoystick(joystick_t *joy) {
// 	lcdPrint(uart1, joy->joystick, "J%d %s%s%s%s%s%s%s",
// 		joy->joystick,
// 		(joy->mode == JOY_MODE_ARM) ? "A" : "D",
// 		(joy->claw) ? " C" : "",
// 		(joy->btn7l.pressed) ? " BT" : "",
// 		(joy->btn8r.pressed) ? " FT" : "",
// 		(joy->btn7d.pressed) ? " DU" : "",
// 		(robot.reflected == -1) ? " I" : "",
// 		(joy->btn8d.pressed) ? " WI" : ""
// 	);
// }

// void
// not_control_init(control_t *control) {
// 	control->action    = OPERATOR_ACTION_NONE;
// 	control->mode      = OPERATOR_MODE_NONE;
// 	control->last_mode = OPERATOR_MODE_NONE;
// 	control->arm       = 0;
// 	control->claw      = 0;
// 	control->drive_x   = 0;
// 	// control->drive_y   = 0;
// 	// control->drive_r   = 0;
// 	// control->wrist     = 0;
// 	// // control->op[0] = NULL;
// 	// // control->op[1] = NULL;
// 	// control->driver = &(control->op[0]);
// 	// control->gunner = &(control->op[1]);
// 	return;
// }

static control_t global_control;

void operatorControl() {
	control_init(&global_control);
	// int i = 0;
	while (1) {
		control_update(&global_control);
		// lcdPrint(uart1, 1, "J1 CH1 = %d", joystickGetAnalog(1, 1));
		// lcdPrint(uart1, 2, "J2 CH1 = %d", joystickGetAnalog(2, 1));
		if (global_control.action & OPERATOR_ACTION_ROBOT_FLIP) {
			robot.reflected *= (-1);
			global_control.driver->action &= ~OPERATOR_ACTION_ROBOT_FLIP;
			global_control.gunner->action &= ~OPERATOR_ACTION_ROBOT_FLIP;
		}
		// printf("millis() = %lu\n", millis());
		// lcdPrint(uart1, 1, "%lu", millis());
		// lcdPrint(uart1, 1, "X %d Y %d R %d", global_control.drive_x, global_control.drive_y, global_control.drive_r);
		// if (i > 128) {
		// 	i = 0;
		// }
		// lcdPrint(uart1, 2, "%d", controller_power_table_get(i++));
		// global_control.driver->gamepad.ch1->value = 9;
		// lcdPrint(uart1, 2, "%d %d %d %d",
		// 	global_control.driver->gamepad.ch1->value,
		// 	global_control.driver->gamepad.ch2->value,
		// 	global_control.driver->gamepad.ch3->value,
		// 	global_control.driver->gamepad.ch4->value
		// );
		drive_control(&(robot.drive), &global_control);
		lift_control(&(robot.lift), &global_control);
		// debugJoystick(&joy1);
		// debugJoystick(&joy2);
		// drive_tick();
		// arm_tick();
		// wrist_tick();
		// claw_tick();
		// lcdPrint(uart1, 1,"T %d", analogRead(top_pot));
		// lcdPrint(uart1, 2,"B %d", analogRead(bot_pot));
		delay(20);
	}
}
