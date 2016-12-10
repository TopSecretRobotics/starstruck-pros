#include "main.h"

bool
lift_init(lift_t *lift, arm_t *arm, wrist_t *wrist, claw_t *claw, pot_t *tuner)
{
	lift->arm   = arm;
	lift->wrist = wrist;
	lift->claw  = claw;
	return true;
}

void
lift_control(lift_t *lift, control_t *control)
{
	int16_t tuner_value = sensor_get((sensor_t *) lift->tuner);
	float tuner_percentage = ((float) (tuner_value - 6)) / 4065.0;
	if (tuner_percentage < 0) {
		tuner_percentage = 0.0;
	} else if (tuner_percentage > 1) {
		tuner_percentage = 1.0;
	}
	//uint8_t buttons = lcdReadButtons(uart1);
	// /* Claw Tuning */
	// if (buttons & LCD_BTN_LEFT) {
	// 	// Kp
	// 	lift->claw->lock.Kp = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->claw->lock.Kp, lift->claw->lock.Ki, lift->claw->lock.Kd);
	// 	lcdPrint(uart1, 2, "Kp %0.2f", tuner_percentage);
	// } else if (buttons & LCD_BTN_CENTER) {
	// 	// Ki
	// 	lift->claw->lock.Ki = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->claw->lock.Kp, lift->claw->lock.Ki, lift->claw->lock.Kd);
	// 	lcdPrint(uart1, 2, "Ki %0.2f", tuner_percentage);
	// } else if (buttons & LCD_BTN_RIGHT) {
	// 	// Kd
	// 	lift->claw->lock.Kd = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->claw->lock.Kp, lift->claw->lock.Ki, lift->claw->lock.Kd);
	// 	lcdPrint(uart1, 2, "Kd %0.2f", tuner_percentage);
	// }
	/* Wrist Tuning */
	// if (buttons & LCD_BTN_LEFT) {
	// 	// Kp
	// 	lift->wrist->lock.Kp = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->wrist->lock.Kp, lift->wrist->lock.Ki, lift->wrist->lock.Kd);
	// 	lcdPrint(uart1, 2, "Kp %0.2f", tuner_percentage);
	// } else if (buttons & LCD_BTN_CENTER) {
	// 	// Ki
	// 	lift->wrist->lock.Ki = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->wrist->lock.Kp, lift->wrist->lock.Ki, lift->wrist->lock.Kd);
	// 	lcdPrint(uart1, 2, "Ki %0.2f", tuner_percentage);
	// } else if (buttons & LCD_BTN_RIGHT) {
	// 	// Kd
	// 	lift->wrist->lock.Kd = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->wrist->lock.Kp, lift->wrist->lock.Ki, lift->wrist->lock.Kd);
	// 	lcdPrint(uart1, 2, "Kd %0.2f", tuner_percentage);
	// }
	/* Arm */
	// if (buttons & LCD_BTN_LEFT) {
	// 	// Kp
	// 	lift->wrist->lock.Kp = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->wrist->lock.Kp, lift->wrist->lock.Ki, lift->wrist->lock.Kd);
	// 	lcdPrint(uart1, 2, "Kp %0.2f", tuner_percentage);
	// } else if (buttons & LCD_BTN_CENTER) {
	// 	// Ki
	// 	lift->wrist->lock.Ki = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->wrist->lock.Kp, lift->wrist->lock.Ki, lift->wrist->lock.Kd);
	// 	lcdPrint(uart1, 2, "Ki %0.2f", tuner_percentage);
	// } else if (buttons & LCD_BTN_RIGHT) {
	// 	// Kd
	// 	lift->wrist->lock.Kd = tuner_percentage;
	// 	lcdPrint(uart1, 1, "%0.2f %0.2f %0.2f", lift->wrist->lock.Kp, lift->wrist->lock.Ki, lift->wrist->lock.Kd);
	// 	lcdPrint(uart1, 2, "Kd %0.2f", tuner_percentage);
	// }


	// lcdPrint(uart1, 1, "tune %d", tuner_value);
	// lcdPrint(uart1, 2, "tune %0.2f", tuner_percentage);
	 arm_control(lift->arm, control);
	 wrist_control(lift->wrist, control);
	claw_control(lift->claw, control);
	return;
}
