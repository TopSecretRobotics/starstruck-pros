#include "main.h"

bool
drive_init(drive_t *drive, wheel_type_t wheel_type, motor_t *ne, motor_t *nw, motor_t *se, motor_t *sw)
{
	drive->ne.motor = ne;
	drive->nw.motor = nw;
	drive->se.motor = se;
	drive->sw.motor = sw;
	drive->ne.type = wheel_type;
	drive->nw.type = wheel_type;
	drive->se.type = wheel_type;
	drive->sw.type = wheel_type;
	return true;
}

void
drive_control(drive_t *drive, control_t *control)
{
	int x = control->drive_x;
	int y = control->drive_y;
	int r = control->drive_r;
	motor_set(drive->ne.motor, (y - x - r) * robot.reflected);
	motor_set(drive->nw.motor, (y + x + r) * robot.reflected);
	motor_set(drive->se.motor, (y + x - r) * robot.reflected);
	motor_set(drive->sw.motor, (y - x + r) * robot.reflected);
	return;
}
