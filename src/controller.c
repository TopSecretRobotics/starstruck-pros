#include "main.h"

static int16_t controller_power_table[CONTROLLER_POWER_TABLE_SIZE];

// There is no sgn function in the standard library
static inline float
sgn(float x)
{
	if (x == 0) {
		return (0);
	} else if (x > 0) {
		return (1);
	} else {
		return (-1);
	}
}

bool
controller_power_table_init(void)
{
	int16_t i;
	float   x;

	for (i = 0; i < CONTROLLER_POWER_TABLE_SIZE; i++) {
		if (CONTROLLER_POWER_TABLE_FACTOR > 1) { // check for valid power base
			x = fastpow(CONTROLLER_POWER_TABLE_FACTOR, ((float) i) / ((float) (CONTROLLER_POWER_TABLE_SIZE - 1)));
			if (i >= (CONTROLLER_POWER_TABLE_OFFSET / 2)) {
				controller_power_table[i] = (((x - 1.0) / (CONTROLLER_POWER_TABLE_FACTOR - 1.0)) * (CONTROLLER_POWER_TABLE_SIZE - 1 - CONTROLLER_POWER_TABLE_OFFSET)) + CONTROLLER_POWER_TABLE_OFFSET;
			} else {
				controller_power_table[i] = i * 2;
			}
		} else { // linear
			controller_power_table[i] = i;
		}
	}

	return true;
}

int16_t
controller_power_table_get(int index)
{
	return controller_power_table[index];
}

void
controller_init(controller_t *c, uint8_t type, float Kp, float Ki, float Kd, float Kbias, sensor_t *sensor)
{
	// pid constants
	c->Kp    = Kp;
	c->Ki    = Ki;
	c->Kd    = Kd;
	c->Kbias = Kbias;

	// zero out working variables
	c->error           = 0;
	c->last_error      = 0;
	c->integral        = 0;
	c->integral_limit  = (Ki != 0) ? (CONTROLLER_INTEGRAL_DRIVE_MAX / Ki) : 0;
	c->derivative      = 0;
	c->error_threshold = 10;

	// time
	c->delta_t   = 0;
	c->last_time = 0;

	// output
	c->drive     = 0;
	c->drive_raw = 0;
	c->drive_cmd = 0;

	// input
	c->sensor       = sensor;
	c->sensor_value = 0;
	c->target_value = 0;

	// loop
	c->active = true;
	c->type   = type;

	return;
}

int16_t
controller_update(controller_t *c)
{
	if (c == NULL) {
		return (0);
	}

	if (c->active) {
		// proportional
		if ((c->type & CONTROLLER_TYPE_P)) {
			// check for sensor port
			// otherwise externally calculated error
			if (c->sensor != NULL) {
				// get raw position value, may be potentiometer
				// TODO: support other sensor types
				c->sensor_value = sensor_get(c->sensor);
				c->error = c->target_value - c->sensor_value;
			}

			// force error to 0 if below threshold
			if (fabs(c->error) < c->error_threshold) {
				c->error = 0;
			}
		}

		// integral accumulation
		if ((c->type & CONTROLLER_TYPE_I)) {
			if (c->Ki != 0) {
				c->integral += c->error;
				// limit to avoid windup
				if (fabs(c->integral) > c->integral_limit) {
					c->integral = sgn(c->integral) * c->integral_limit;
				}
			} else {
				c->integral = 0;
			}
		}

		// derivative
		if ((c->type & CONTROLLER_TYPE_D)) {
			c->derivative = c->error - c->last_error;
			c->last_error = c->error;
		}

		// delta time (T)
		if ((c->type & CONTROLLER_TYPE_T)) {
			unsigned long now = millis();
			c->delta_t = now - c->last_time;
			c->last_time = now;
		}

		{
			float p = (c->type & CONTROLLER_TYPE_P) ? (c->Kp * c->error) : 0;
			float i = (c->type & CONTROLLER_TYPE_I) ? (c->Ki * c->integral) : 0;
			float d = (c->type & CONTROLLER_TYPE_D) ? (c->Kd * c->derivative) : 0;
			if ((c->type & CONTROLLER_TYPE_T) && c->delta_t != 0) {
				d /= c->delta_t;
			}
			// calculate drive
			c->drive = p + i + d + c->Kbias;
		}

		// drive should be in the range +/- 1.0
		if (fabs(c->drive) > 1.0) {
			c->drive = sgn(c->drive);
		}

		// final motor output
		c->drive_raw = c->drive * 127.0;
	} else {
		// disabled, all zeroes
		c->error      = 0;
		c->last_error = 0;
		c->integral   = 0;
		c->derivative = 0;
		c->delta_t    = 0;
		c->drive      = 0;
		c->drive_raw  = 0;
	}

	// linearize power
	c->drive_cmd = controller_power_table[abs(c->drive_raw)] * sgn(c->drive_raw);

	// return the linearized drive power
	return (c->drive_cmd);
}
