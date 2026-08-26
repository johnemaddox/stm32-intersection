#include "intersection.h"
#include "leds.h"
#ifdef NATIVE
    #include "HAL_stubs.h"
#else
    #include "stm32g0xx_hal.h"
#endif

static const uint32_t state_durations[NUM_SIG_STATES] = {
    [NSgEWr]  = DURATION_NSgEWr,
    [NSgrEWr] = DURATION_NSgrEWr,
    [NSrEWg]  = DURATION_NSrEWg,
    [NSrEWgr] = DURATION_NSrEWgr,
    [NSrEWr]  = DURATION_NSrEWr
};

static sm_state_t on_NSgEWr(sm_handle_t *self, void *context) {
    (void)self; (void)context;
    leds_write(PATTERN_NSgEWr);
    return NSgEWr;
}

static sm_state_t on_NSgrEWr(sm_handle_t *self, void *context) {
    (void)self; (void)context;
    leds_write(PATTERN_NSgrEWr);
    return NSgrEWr;
}

static sm_state_t on_NSrEWg(sm_handle_t *self, void *context) {
    (void)self; (void)context;
    leds_write(PATTERN_NSrEWg);
    return NSrEWg;
}

static sm_state_t on_NSrEWgr(sm_handle_t *self, void *context) {
    (void)self; (void)context;
    leds_write(PATTERN_NSrEWgr);
    return NSrEWgr;
}

static sm_state_t on_NSrEWr(sm_handle_t *self, void *context) {
    (void)self; (void)context;
    leds_write(PATTERN_NSrEWr);
    return NSrEWr;
}

static const sm_state_config_t state_table[NUM_SIG_STATES] = {
    [NSgEWr]  = { on_NSgEWr,  NSgrEWr },
    [NSgrEWr] = { on_NSgrEWr, NSrEWg },
    [NSrEWg]  = { on_NSrEWg,  NSrEWgr },
    [NSrEWgr] = { on_NSrEWgr, NSgEWr },
    [NSrEWr]  = { on_NSrEWr,  NSgEWr }
};

static sm_handle_t sm;
static volatile uint32_t last_tick = 0;
static volatile uint32_t state_duration = 0;

static void set_state_timer(uint32_t duration_ms) {
    last_tick = HAL_GetTick();
    state_duration = duration_ms;
}

static int is_state_timer_expired(void) {
    return (HAL_GetTick() - last_tick) >= state_duration;
}

void intersection_init(void) {
    sm.cur_state = NSgEWr;
    sm.state_table = state_table;
    sm.num_states = NUM_SIG_STATES;
    sm.context = NULL;

    sm_state_t executed = sm_run(&sm);
    set_state_timer(state_durations[executed]);
}

void intersection_step(void) {
    if (is_state_timer_expired()) {
#ifndef NATIVE
        __disable_irq();
#endif
        sm_state_t executed = sm_run(&sm);
        set_state_timer(state_durations[executed]);
#ifndef NATIVE
        __enable_irq();
#endif
    }
}

void intersection_trigger_emergency(void) {
    leds_write(PATTERN_NSrEWr);
    sm.cur_state = NSrEWr;
    set_state_timer(0); // Trigger transition on next step check
}

uint32_t intersection_get_state_duration(sm_state_t state) {
    if (state < NUM_SIG_STATES) {
        return state_durations[state];
    }
    return 0;
}
