/**
 * SpiritOS Freestanding C Library - Printf Implementation
 * 
 * Simple printf for kernel console output
 */

#ifndef KPRINTF_H
#define KPRINTF_H

/* Kernel printf - outputs to VGA and serial */
int kprintf(const char *format, ...);

/* Initialize console subsystem */
void console_init(void);

#endif /* KPRINTF_H */
