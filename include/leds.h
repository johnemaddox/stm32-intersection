/*H************************************************************
 *
 * LED controller (using shift register)
 *
 *  This LED controller is to control the TI SN74HC595N Shift
 *  Register using the NUCLEO-G071RB board. This is a wrapper
 *  for HAL for initialization and writes to the pins which
 *  can be seen in the schematic diagram included in this repo.
 *
 * Shift register bits are configured for each LED condition in 
 * intersetion.h and sent to the register in leds_write().
 * 
 * @author John E Maddox
 *
 * @version 1.0.0
 *
 *************************************************************H*/

#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

#define SR_GPIO_PORT     GPIOA
#define SR_RCLK_PIN      GPIO_PIN_4
#define SR_SRCLK_PIN     GPIO_PIN_5
#define SR_SER_PIN       GPIO_PIN_7

void leds_init(void);
void leds_write(uint8_t value);

#endif // LEDS_H
