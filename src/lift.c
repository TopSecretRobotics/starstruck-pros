#include "main.h"

bool
lift_init(lift_t *lift, arm_t *arm, wrist_t *wrist, claw_t *claw)
{
	lift->arm   = arm;
	lift->wrist = wrist;
	lift->claw  = claw;
	return true;
}

void
lift_control(lift_t *lift, control_t *control)
{
	// arm_control(lift->arm, control);
	// wrist_control(lift->wrist, control);
	// claw_control(lift->claw, control);
	return;
}
