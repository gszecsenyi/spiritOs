/**
 * SpiritOS Hardware Abstraction Layer - Serial Port Driver Implementation
 * 
 * Provides serial I/O for debugging and console
 */

#include <stddef.h>
#include "serial.h"
#include "io.h"

static inline int is_transmit_empty(void) {
    return inb(COM1 + 5) & 0x20;
}

void serial_init(void) {
    outb(COM1 + 1, 0x00);    /* Disable all interrupts */
    outb(COM1 + 3, 0x80);    /* Enable DLAB (set baud rate divisor) */
    outb(COM1 + 0, 0x03);    /* Set divisor to 3 (lo byte) 38400 baud */
    outb(COM1 + 1, 0x00);    /*                  (hi byte) */
    outb(COM1 + 3, 0x03);    /* 8 bits, no parity, one stop bit */
    outb(COM1 + 2, 0xC7);    /* Enable FIFO, clear them, with 14-byte threshold */
    outb(COM1 + 4, 0x0B);    /* IRQs enabled, RTS/DSR set */
}

void serial_putchar(char c) {
    while (!is_transmit_empty())
        ;
    outb(COM1, c);
}

void serial_puts(const char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            serial_putchar('\r');
        }
        serial_putchar(str[i]);
    }
}

int serial_received(void) {
    return inb(COM1 + 5) & 1;
}

char serial_getchar(void) {
    while (!serial_received())
        ;
    return inb(COM1);
}
