#ifndef SENSOR_H_

#define SENSOR_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum sensor_type {
	SENSOR_TYPE_POT
} sensor_type_t;

typedef struct sensor_s {
	sensor_type_t type;
	unsigned char port;
	bool          reversed; // flag indicating the sensor values should be reversed
} sensor_t;

extern int16_t sensor_get(sensor_t *sensor);

#ifdef __cplusplus
}
#endif

#endif
