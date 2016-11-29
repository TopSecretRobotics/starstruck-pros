#ifndef POT_H_

#define POT_H_

#include <API.h>
#include "sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pot_s {
	sensor_type_t type;
	unsigned char channel;
	bool          reversed;
} pot_t;

extern bool pot_init(pot_t *pot, unsigned char channel, bool reversed);
extern int16_t pot_read(pot_t *pot);

#ifdef __cplusplus
}
#endif

#endif
