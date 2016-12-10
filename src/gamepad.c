#include "main.h"

static gamepad_analog_t *gamepad_analog_init(gamepad_analog_t *ch, unsigned char axis, uint8_t deadband);
static void gamepad_analog_update(gamepad_t *gp, gamepad_analog_t *ch, unsigned long now);

static gamepad_digital_t *gamepad_digital_init(gamepad_digital_t *btn, unsigned char group, unsigned char button);
static void gamepad_digital_update(gamepad_t *gp, gamepad_digital_t *btn, unsigned long now);
static void gamepad_digital_handle(gamepad_digital_t *btn, unsigned long now);

static void gamepad_listener_init(gamepad_listener_t *listener);
static void gamepad_listener_handle(gamepad_listener_t *listener, bool triggered, unsigned long now);

bool
gamepad_init(gamepad_t *gp, unsigned char joystick)
{
	gp->joystick = joystick;
	gp->ch1 = gamepad_analog_init(&(gp->analog[0]), 1, GAMEPAD_ANALOG_CH1_DEADBAND);
	gp->ch2 = gamepad_analog_init(&(gp->analog[1]), 2, GAMEPAD_ANALOG_CH2_DEADBAND);
	gp->ch3 = gamepad_analog_init(&(gp->analog[2]), 3, GAMEPAD_ANALOG_CH3_DEADBAND);
	gp->ch4 = gamepad_analog_init(&(gp->analog[3]), 4, GAMEPAD_ANALOG_CH4_DEADBAND);
	gp->btn5d = gamepad_digital_init(&(gp->digital[0]), 5, JOY_DOWN);
	gp->btn5u = gamepad_digital_init(&(gp->digital[1]), 5, JOY_UP);
	gp->btn6d = gamepad_digital_init(&(gp->digital[2]), 6, JOY_DOWN);
	gp->btn6u = gamepad_digital_init(&(gp->digital[3]), 6, JOY_UP);
	gp->btn7d = gamepad_digital_init(&(gp->digital[4]), 7, JOY_DOWN);
	gp->btn7l = gamepad_digital_init(&(gp->digital[5]), 7, JOY_LEFT);
	gp->btn7u = gamepad_digital_init(&(gp->digital[6]), 7, JOY_UP);
	gp->btn7r = gamepad_digital_init(&(gp->digital[7]), 7, JOY_RIGHT);
	gp->btn8d = gamepad_digital_init(&(gp->digital[8]), 8, JOY_DOWN);
	gp->btn8l = gamepad_digital_init(&(gp->digital[9]), 8, JOY_LEFT);
	gp->btn8u = gamepad_digital_init(&(gp->digital[10]), 8, JOY_UP);
	gp->btn8r = gamepad_digital_init(&(gp->digital[11]), 8, JOY_RIGHT);
	return true;
}

void
gamepad_update(gamepad_t *gp)
{
	unsigned long now = millis();
	int i;
	for (i = 0; i < GAMEPAD_ANALOG_SIZE; i++) {
		gamepad_analog_update(gp, &(gp->analog[i]), now);
	}
	for (i = 0; i < GAMEPAD_DIGITAL_SIZE; i++) {
		gamepad_digital_update(gp, &gp->digital[i], now);
	}
	for (i = 0; i < GAMEPAD_DIGITAL_SIZE; i++) {
		gamepad_digital_handle(&gp->digital[i], now);
	}
	return;
}

void
gamepad_listen(gamepad_listener_t *listener, void (*callback)(void *data), void *data, unsigned long debounce, unsigned long throttle)
{
	listener->callback = callback;
	listener->data = data;
	listener->debounce = debounce;
	listener->throttle = throttle;
	return;
}

void
gamepad_unlisten(gamepad_listener_t *listener)
{
	gamepad_listen(listener, NULL, NULL, 0, 0);
	return;
}

/* Gamepad Analog */

static gamepad_analog_t *
gamepad_analog_init(gamepad_analog_t *ch, unsigned char axis, uint8_t deadband)
{
	ch->axis       = axis;
	ch->deadband   = deadband;
	ch->value      = 0;
	ch->last_value = 0;
	ch->time       = 0;
	ch->last_time  = 0;
	return ch;
}

static void
gamepad_analog_update(gamepad_t *gp, gamepad_analog_t *ch, unsigned long now)
{
	int value = joystickGetAnalog(gp->joystick, ch->axis);
	ch->last_value = ch->value;
	ch->value = (abs(value) >= ch->deadband) ? value : 0;
	ch->last_time = ch->time;
	ch->time = now;
	return;
}

/* Gamepad Digital */

static gamepad_digital_t *
gamepad_digital_init(gamepad_digital_t *btn, unsigned char group, unsigned char button)
{
	btn->group               = group;
	btn->button              = button;
	btn->events              = GAMEPAD_BUTTON_EVENT_NONE;
	btn->last_events         = GAMEPAD_BUTTON_EVENT_NONE;
	btn->hold_timeout        = 0;
	btn->click_count         = 0;
	btn->doubleclick_timeout = 0;
	gamepad_listener_init(&btn->on_press);
	gamepad_listener_init(&btn->on_release);
	gamepad_listener_init(&btn->on_hold);
	gamepad_listener_init(&btn->on_click);
	gamepad_listener_init(&btn->on_doubleclick);
	return btn;
}

static void
gamepad_digital_update(gamepad_t *gp, gamepad_digital_t *btn, unsigned long now)
{
	bool pressed = (bool) joystickGetDigital(gp->joystick, btn->group, btn->button);
	uint8_t events = GAMEPAD_BUTTON_EVENT_NONE;
	// Phase 1: Press, Release, Hold, and Click
	if (pressed) {
		events |= GAMEPAD_BUTTON_EVENT_PRESS;                      // PRESS
		if (btn->events & GAMEPAD_BUTTON_EVENT_HOLD) {             // if we already fired hold, continue
			events |= GAMEPAD_BUTTON_EVENT_HOLD;                   // HOLD
		} else if (btn->hold_timeout == 0) {                       // otherwise, start a timer for hold to fire
			btn->hold_timeout = now + GAMEPAD_BUTTON_HOLD_TIMEOUT;
		} else if (now >= btn->hold_timeout) {                     // timer expired, fire hold
			events |= GAMEPAD_BUTTON_EVENT_HOLD;                   // HOLD
			btn->hold_timeout = 0;
		}
	} else if (btn->events & GAMEPAD_BUTTON_EVENT_PRESS) {         // if we pressed last tick, time to fire release
		events |= GAMEPAD_BUTTON_EVENT_RELEASE;                    // RELEASE
		btn->hold_timeout = 0;
		if (!(btn->events & GAMEPAD_BUTTON_EVENT_HOLD)) {          // if we didn't hold, fire click
			events |= GAMEPAD_BUTTON_EVENT_CLICK;                  // CLICK
			btn->click_count++;
		}
	}
	// Phase 2: Doubleclick
	if (events & GAMEPAD_BUTTON_EVENT_CLICK) {
		if (btn->click_count == 1) {
			btn->doubleclick_timeout = now + GAMEPAD_BUTTON_DOUBLECLICK_TIMEOUT;
		} else if (btn->click_count == 2 && abs(now - btn->doubleclick_timeout) < GAMEPAD_TIMEOUT_THRESHOLD) {
			events |= GAMEPAD_BUTTON_EVENT_DOUBLECLICK;
			btn->click_count = 0;
			btn->doubleclick_timeout = 0;
		} else if (btn->click_count > 2 || (btn->doubleclick_timeout && now > btn->doubleclick_timeout)) {
			btn->click_count = 0;
			btn->doubleclick_timeout = 0;
		}
	}
	btn->last_events = btn->events;
	btn->events = events;
	return;
}

static void
gamepad_digital_handle(gamepad_digital_t *btn, unsigned long now)
{
	gamepad_listener_handle(&btn->on_press,       (bool) (btn->events & GAMEPAD_BUTTON_EVENT_PRESS), now);
	gamepad_listener_handle(&btn->on_release,     (bool) (btn->events & GAMEPAD_BUTTON_EVENT_RELEASE), now);
	gamepad_listener_handle(&btn->on_hold,        (bool) (btn->events & GAMEPAD_BUTTON_EVENT_HOLD), now);
	gamepad_listener_handle(&btn->on_click,       (bool) (btn->events & GAMEPAD_BUTTON_EVENT_CLICK), now);
	gamepad_listener_handle(&btn->on_doubleclick, (bool) (btn->events & GAMEPAD_BUTTON_EVENT_DOUBLECLICK), now);
	return;
}

/* Gamepad Listener */

static void
gamepad_listener_init(gamepad_listener_t *listener)
{
	listener->callback         = NULL;
	listener->data             = NULL;
	listener->fire_time        = 0;
	listener->debounce         = 0;
	listener->debounce_timeout = 0;
	listener->throttle         = 0;
	listener->throttle_timeout = 0;
	return;
}

static void
gamepad_listener_handle(gamepad_listener_t *listener, bool triggered, unsigned long now)
{
	bool fired = false;
	if (triggered) {
		if (listener->throttle) {
			if (now >= listener->throttle_timeout) {
				fired = true;
				listener->throttle_timeout = now + listener->throttle;
			}
		} else if (listener->debounce) {
			listener->debounce_timeout = now + listener->debounce;
		} else {
			fired = true;
		}
	}
	if (listener->debounce_timeout && now >= listener->debounce_timeout) {
		fired = true;
		listener->debounce_timeout = 0;
	}
	if (fired) {
		listener->fire_time = now;
		if (listener->callback != NULL) {
			listener->callback(listener->data);
		}
	}
	return;
}
