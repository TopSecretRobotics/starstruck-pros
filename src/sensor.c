#include "main.h"

int16_t
sensor_get(sensor_t *sensor)
{
	switch (sensor->type) {
		case SENSOR_TYPE_POT:
			return pot_read((pot_t *) sensor);
		default:
			return (0);
	}
}
