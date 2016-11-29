#ifndef CONTROLLER_H_

#define CONTROLLER_H_

#include <API.h>
#include "fastmath.h"
#include "sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CONTROLLER_TYPE_P 0x01 // proportional
#define CONTROLLER_TYPE_I 0x02 // integral
#define CONTROLLER_TYPE_D 0x04 // derivative
#define CONTROLLER_TYPE_T 0x08 // time

#define CONTROLLER_TYPE_PI  (CONTROLLER_TYPE_P | CONTROLLER_TYPE_I)
#define CONTROLLER_TYPE_PD  (CONTROLLER_TYPE_P | CONTROLLER_TYPE_D)
#define CONTROLLER_TYPE_PID (CONTROLLER_TYPE_P | CONTROLLER_TYPE_I | CONTROLLER_TYPE_D)

#define CONTROLLER_INTEGRAL_DRIVE_MAX 0.25

#define CONTROLLER_POWER_TABLE_SIZE   128
#define CONTROLLER_POWER_TABLE_FACTOR 20.0
#define CONTROLLER_POWER_TABLE_OFFSET 10

typedef struct controller_s {
	/* PID constants, Kbias is used to compensate for gravity or similar */
	float Kp;    // proportional constant
	float Ki;    // integral constant
	float Kd;    // derivative constant
	float Kbias; // bias constant
	/* Working Variables */
	float error;           // error between actual position and target
	float last_error;      // error last time update was called
	float integral;        // integrated error
	float integral_limit;  // limit for integrated error
	float derivative;      // change in error from last time
	float error_threshold; // threshold below which error is ignored
	/* Time */
	unsigned long delta_t;   // change in time
	unsigned long last_time; // last time
	/* Output */
	float   drive;     // calculated motor drive in range +/- 1.0
	int16_t drive_raw; // motor drive in the range +/- 127
	int16_t drive_cmd; // linearized motor drive in the range +/- 127
	/* Input */
	sensor_t *sensor;      // digital or analog port with the position sensor
	int16_t  sensor_value; // current value of the position sensor
	int16_t  target_value; // the target value
	/* Loop */
	bool    active;
	uint8_t type;
} controller_t;

extern bool controller_power_table_init(void);
extern void controller_init(controller_t *c, uint8_t type, float Kp, float Ki, float Kd, float Kbias, sensor_t *sensor);
extern int16_t controller_update(controller_t *c);

#ifdef __cplusplus
}
#endif

#endif
