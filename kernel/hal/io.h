/**
 * SpiritOS Hardware Abstraction Layer - I/O Port Operations
 * 
 * Provides low-level I/O port access for x86_64
 */

#ifndef IO_H
#define IO_H

#include <stdint.h>

/* Output byte to I/O port */
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

/* Input byte from I/O port */
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Output word to I/O port */
static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

/* Input word from I/O port */
static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* I/O wait (for slow devices) */
static inline void io_wait(void) {
    outb(0x80, 0);
}

#endif /* IO_H */
