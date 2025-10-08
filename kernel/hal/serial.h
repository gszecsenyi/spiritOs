/**
 * SpiritOS Hardware Abstraction Layer - Serial Port Driver
 * 
 * Provides serial I/O for debugging and console
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

/* Serial ports */
#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

/* Initialize serial port */
void serial_init(void);

/* Write character to serial port */
void serial_putchar(char c);

/* Write string to serial port */
void serial_puts(const char *str);

/* Read character from serial port (blocking) */
char serial_getchar(void);

/* Check if data is available */
int serial_received(void);

#endif /* SERIAL_H */
