/*H************************************************************
 *
 * Traffic Signal Intersection
 *
 *  Utilizes the state machine from c-design-patterns to manage
 *  the intersection patterhs as outlined below. The patterns all
 *  cycle by the specified durations defined as DURATION_* to keep
 *  the states timed independently.
 *
 *      - North-South Green             , East-West Red
 *      - North-South Yellow (Green+Red), East-West Red
 *      - North-South Red               , East-West Green
 *      - North-South Red               , East-West Yellow (Green+Red)
 *      - Emergency All Red
 *
 * @author John E Maddox
 *
 * @version 1.0.0
 *
 *************************************************************H*/

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "state_machine.h"
#include <stdint.h>

typedef enum
{
    NSgEWr,     // North-South Green             , East-West Red
    NSgrEWr,    // North-South Yellow (Green+Red), East-West Red
    NSrEWg,     // North-South Red               , East-West Green
    NSrEWgr,    // North-South Red               , East-West Yellow (Green+Red)
    NSrEWr,     // Emergency All Red
    NUM_SIG_STATES
} sig_states_t;

// LED state bit patterns for the shift register based on schematic pinout.
#define PATTERN_NSgEWr  0x99 // 0b10011001
#define PATTERN_NSgrEWr 0xBB // 0b10111011
#define PATTERN_NSrEWg  0x66 // 0b01100110
#define PATTERN_NSrEWgr 0xEE // 0b11101110
#define PATTERN_NSrEWr  0xAA // 0b10101010

#define DURATION_NSgEWr  1500
#define DURATION_NSgrEWr 500
#define DURATION_NSrEWg  1500
#define DURATION_NSrEWgr 500
#define DURATION_NSrEWr  1500

void intersection_init(void);
void intersection_step(void);
void intersection_trigger_emergency(void);
uint32_t intersection_get_state_duration(sm_state_t state);

#endif // INTERSECTION_H
