/**
 * SpiritOS Hardware Abstraction Layer - Timer/Delay Implementation
 * 
 * Provides timing and delay functionality using PIT
 */

#include "timer.h"
#include "io.h"

/* PIT (Programmable Interval Timer) ports */
#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43

static volatile uint64_t system_ticks = 0;

void timer_init(void) {
    /* Initialize PIT to ~1000Hz (1ms resolution) */
    uint16_t divisor = 1193;  /* 1193182 Hz / 1193 ≈ 1000 Hz */
    
    outb(PIT_COMMAND, 0x36);  /* Channel 0, lobyte/hibyte, rate generator */
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);
    
    system_ticks = 0;
}

void timer_tick(void) {
    system_ticks++;
}

uint64_t timer_get_ticks(void) {
    return system_ticks;
}

void delay_ms(uint32_t ms) {
    /* Simple busy-wait delay */
    /* This is approximate and CPU-speed dependent */
    for (uint32_t i = 0; i < ms; i++) {
        for (volatile uint32_t j = 0; j < 100000; j++) {
            /* Busy wait */
        }
    }
}
