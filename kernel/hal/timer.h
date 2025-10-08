/**
 * SpiritOS Hardware Abstraction Layer - Timer/Delay Functions
 * 
 * Provides timing and delay functionality
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/* Initialize timer */
void timer_init(void);

/* Simple delay loop (approximate) */
void delay_ms(uint32_t ms);

/* Get tick count */
uint64_t timer_get_ticks(void);

#endif /* TIMER_H */
