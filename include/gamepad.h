#ifndef GAMEPAD_H_

#define GAMEPAD_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GAMEPAD_BUTTON_HOLD_TIMEOUT        500
#define GAMEPAD_BUTTON_DOUBLECLICK_TIMEOUT 300

#define GAMEPAD_TIMEOUT_THRESHOLD 20

#define GAMEPAD_BUTTON_EVENT_NONE        0x00
#define GAMEPAD_BUTTON_EVENT_PRESS       0x01
#define GAMEPAD_BUTTON_EVENT_HOLD        0x02
#define GAMEPAD_BUTTON_EVENT_RELEASE     0x04
#define GAMEPAD_BUTTON_EVENT_CLICK       0x08
#define GAMEPAD_BUTTON_EVENT_DOUBLECLICK 0x10

typedef struct gamepad_listener_s {
	void          (*callback)(void *data);
	void          *data;
	unsigned long fire_time;
	unsigned long debounce;
	unsigned long debounce_timeout;
	unsigned long throttle;
	unsigned long throttle_timeout;
} gamepad_listener_t;

#define GAMEPAD_ANALOG_DEADBAND     20
#define GAMEPAD_ANALOG_CH1_DEADBAND GAMEPAD_ANALOG_DEADBAND
#define GAMEPAD_ANALOG_CH2_DEADBAND GAMEPAD_ANALOG_DEADBAND
#define GAMEPAD_ANALOG_CH3_DEADBAND GAMEPAD_ANALOG_DEADBAND
#define GAMEPAD_ANALOG_CH4_DEADBAND GAMEPAD_ANALOG_DEADBAND

typedef struct gamepad_analog_s {
	unsigned char axis;
	uint8_t       deadband;
	int8_t        value;
	int8_t        last_value;
	unsigned long time;
	unsigned long last_time;
} gamepad_analog_t;

typedef struct gamepad_digital_s {
	unsigned char      group;
	unsigned char      button;
	uint8_t            events;
	uint8_t            last_events;
	unsigned long      hold_timeout;
	uint8_t            click_count;
	unsigned long      doubleclick_timeout;
	gamepad_listener_t on_press;
	gamepad_listener_t on_release;
	gamepad_listener_t on_hold;
	gamepad_listener_t on_click;
	gamepad_listener_t on_doubleclick;
} gamepad_digital_t;

#define GAMEPAD_ANALOG_SIZE  4
#define GAMEPAD_DIGITAL_SIZE 12

typedef struct gamepad_s {
	unsigned char joystick;
	gamepad_analog_t  analog[GAMEPAD_ANALOG_SIZE];
	gamepad_analog_t  *ch1;
	gamepad_analog_t  *ch2;
	gamepad_analog_t  *ch3;
	gamepad_analog_t  *ch4;
	gamepad_digital_t digital[GAMEPAD_DIGITAL_SIZE];
	gamepad_digital_t *btn5d;
	gamepad_digital_t *btn5u;
	gamepad_digital_t *btn6d;
	gamepad_digital_t *btn6u;
	gamepad_digital_t *btn7d;
	gamepad_digital_t *btn7l;
	gamepad_digital_t *btn7u;
	gamepad_digital_t *btn7r;
	gamepad_digital_t *btn8d;
	gamepad_digital_t *btn8l;
	gamepad_digital_t *btn8u;
	gamepad_digital_t *btn8r;
} gamepad_t;

extern bool gamepad_init(gamepad_t *gp, unsigned char joystick);
extern void gamepad_update(gamepad_t *gp);
extern void gamepad_listen(gamepad_listener_t *listener, void (*callback)(void *data), void *data, unsigned long debounce, unsigned long throttle);
extern void gamepad_unlisten(gamepad_listener_t *listener);

#ifdef __cplusplus
}
#endif

#endif
