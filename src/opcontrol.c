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

static const unsigned char top_pot = 1;
static const unsigned char bot_pot = 2;
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

static void debugJoystick(joystick_t *joy) {
	lcdPrint(uart1, joy->joystick, "J%d %s%s%s%s%s%s%s",
		joy->joystick,
		(joy->mode == JOY_MODE_ARM) ? "A" : "D",
		(joy->claw) ? " C" : "",
		(joy->btn7l.pressed) ? " BT" : "",
		(joy->btn8r.pressed) ? " FT" : "",
		(joy->btn7d.pressed) ? " DU" : "",
		(robot.reflected == -1) ? " I" : "",
		(joy->btn8d.pressed) ? " WI" : ""
	);
}

void operatorControl() {
	joystick_t joy1;
	joystick_t joy2;

	joystickInit(&joy1, 1, JOY_MODE_DRV);
	joystickInit(&joy2, 2, JOY_MODE_ARM);

	while (1) {
		joystickTick(&joy1);
		joystickTick(&joy2);

		debugJoystick(&joy1);
		debugJoystick(&joy2);

		if (joy1.mode == JOY_MODE_DRV) {
			drive_tick(&joy1);
		} else if (joy2.mode == JOY_MODE_DRV) {
			drive_tick(&joy2);
		} else {
			drive_tick(NULL);
		}

		if (joy2.mode == JOY_MODE_ARM) {
			lift_tick(&joy2);
		} else if (joy1.mode == JOY_MODE_ARM) {
			lift_tick(&joy1);
		} else {
			lift_tick(NULL);
		}

		// drive_tick();
		// arm_tick();
		// wrist_tick();
		// claw_tick();
		//
		// lcdPrint(uart1, 1,"T %d", analogRead(top_pot));
	  // lcdPrint(uart1, 2,"B %d", analogRead(bot_pot));

		delay(20);
	}
}
