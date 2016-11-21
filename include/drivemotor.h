#ifndef DRIVEMOTOR_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define DRIVEMOTOR_H_

#include <API.h>

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

#define DRIVEMOTOR_MAX_SPEED 127

#define DRIVEMOTOR_SIDE_NONE 0
#define DRIVEMOTOR_SIDE_LEFT 1
#define DRIVEMOTOR_SIDE_RIGHT 2

typedef struct drivemotor_s {
  unsigned char channel;
	uint8_t side;
	bool reflected;
} drivemotor_t;

int drivemotorGet(drivemotor_t *drivemotor);
void drivemotorSet(drivemotor_t *drivemotor, int speed);
void drivemotorStop(drivemotor_t *drivemotor);

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
