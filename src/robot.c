#include "main.h"

robot_t robot;

bool
robot_init(void)
{
	robot.reflected = 1;

	/* Drive */
	motor_init(&(robot.motor[0]), 9, MOTOR_FLAG_REFLECTED | MOTOR_FLAG_EXPANDED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	motor_init(&(robot.motor[1]), 2, MOTOR_FLAG_NORMAL | MOTOR_FLAG_EXPANDED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	motor_init(&(robot.motor[2]), 10, MOTOR_FLAG_NORMAL, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	motor_init(&(robot.motor[3]), 1, MOTOR_FLAG_NORMAL, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	drive_init(
		&(robot.drive),
		WHEEL_TYPE_OMNI_325,
		&(robot.motor[0]), // northeast or front-right
		&(robot.motor[1]), // northwest or front-left
		&(robot.motor[2]), // southeast or back-right
		&(robot.motor[3])  // southwest or back-left
	);

	/* Arm */
	motor_init(&robot.motor[4], 8, MOTOR_FLAG_NORMAL | MOTOR_FLAG_Y_CABLED | MOTOR_FLAG_EXPANDED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	motor_init(&robot.motor[5], 7, MOTOR_FLAG_REFLECTED | MOTOR_FLAG_Y_CABLED | MOTOR_FLAG_EXPANDED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	motor_init(&robot.motor[6], 3, MOTOR_FLAG_REFLECTED | MOTOR_FLAG_Y_CABLED | MOTOR_FLAG_EXPANDED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	pot_init(&robot.pot[0], 1, false);
	arm_init(
		&robot.arm,
		&robot.motor[4], // top
		&robot.motor[5], // middle
		&robot.motor[6], // bottom
		&robot.pot[0],
		4090,            // target value
		1940             // reflected target value
	);

	/* Wrist */
	motor_init(&robot.motor[7], 6, MOTOR_FLAG_REFLECTED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	pot_init(&robot.pot[1], 2, false);
	wrist_init(
		&robot.wrist,
		&robot.motor[7],
		&robot.pot[1],
		2930,           // target value
		660             // reflected target value
	);

	/* Claw */
	motor_init(&robot.motor[8], 5, MOTOR_FLAG_REFLECTED | MOTOR_FLAG_EXPANDED, MOTOR_TYPE_393, MOTOR_GEARING_TORQUE);
	pot_init(&robot.pot[2], 3, false);
	claw_init(
		&robot.claw,
		&robot.motor[8],
		&robot.pot[2],
		1135,           // grab value
		360             // open value
	);

	/* Lift */
	pot_init(&robot.pot[3], 5, false);
	lift_init(
		&robot.lift,
		&robot.arm,
		&robot.wrist,
		&robot.claw,
		&robot.pot[3] // tuner
	);

	/* Tuner */


	return true;
}
