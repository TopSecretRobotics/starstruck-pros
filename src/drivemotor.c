#include "main.h"

/*
 * Public API
 */

int drivemotorGet(drivemotor_t *drivemotor) {
  int speed = motorGet(drivemotor->channel);
  if (drivemotor->reflected) {
    speed *= -1;
  }
  return speed;
}

void drivemotorSet(drivemotor_t *drivemotor, int speed) {
  if (drivemotor->reflected) {
    speed *= -1;
  }
  motorSet(drivemotor->channel, speed);
}

void drivemotorStop(drivemotor_t *drivemotor) {
  motorStop(drivemotor->channel);
}
