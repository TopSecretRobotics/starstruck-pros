#ifndef MOTOR_H_

#define MOTOR_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum motor_type {
	MOTOR_TYPE_269,
	MOTOR_TYPE_393,
	MOTOR_TYPE_3WIRE
} motor_type_t;

typedef enum motor_gearing {
	MOTOR_GEARING_SPEED  = 160,
	MOTOR_GEARING_TORQUE = 100
} motor_gearing_t;

#define MOTOR_FLAG_NORMAL    0x00 // empty flag
#define MOTOR_FLAG_READY     0x01 // motor is ready
#define MOTOR_FLAG_REFLECTED 0x02 // motor is reversed
#define MOTOR_FLAG_Y_CABLED  0x04 // motor is Y-cabled
#define MOTOR_FLAG_EXPANDED  0x08 // motor connected to power expander
#define MOTOR_FLAG_ENCODER   0x10 // motor has encoder

typedef struct motor_s {
	unsigned char   channel;
	uint8_t         flags;
	int16_t         __pad0__;
	motor_type_t    type;
	motor_gearing_t gearing;
} motor_t;

extern bool motor_init(motor_t *motor, unsigned char channel, uint8_t flags, motor_type_t type, motor_gearing_t gearing);

extern int motor_get(const motor_t *motor);
extern bool motor_has_encoder(const motor_t *motor);
extern bool motor_is_expanded(const motor_t *motor);
extern bool motor_is_ready(const motor_t *motor);
extern bool motor_is_reflected(const motor_t *motor);
extern bool motor_is_y_cabled(const motor_t *motor);
extern void motor_set(const motor_t *motor, int speed);
extern void motor_stop(const motor_t *motor);

#ifdef __cplusplus
}
#endif

#endif
