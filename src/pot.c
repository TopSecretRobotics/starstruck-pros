#include "main.h"

bool
pot_init(pot_t *pot, unsigned char channel, bool reversed)
{
	pot->type = SENSOR_TYPE_POT;
	pot->channel = channel;
	pot->reversed = reversed;
	return true;
}

int16_t
pot_read(pot_t *pot)
{
	int16_t value = analogRead(pot->channel);
	if (pot->reversed) {
		value = 4095 - value;
	}
	return value;
}
