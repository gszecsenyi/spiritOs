/**
 * SpiritOS Freestanding C Library - Printf Implementation
 * 
 * Simple printf for kernel console output
 */

#include "kprintf.h"
#include "vga.h"
#include "serial.h"
#include "kstring.h"
#include <stdarg.h>
#include <stdbool.h>

static void putchar_console(char c) {
    vga_putchar(c);
    serial_putchar(c);
}

static void puts_console(const char *str) {
    while (*str) {
        putchar_console(*str++);
    }
}

static void print_num(unsigned long long num, int base, bool is_signed) {
    const char *digits = "0123456789abcdef";
    char buf[32];
    int i = 0;
    bool negative = false;
    
    if (is_signed && (long long)num < 0) {
        negative = true;
        num = -(long long)num;
    }
    
    if (num == 0) {
        buf[i++] = '0';
    } else {
        while (num > 0) {
            buf[i++] = digits[num % base];
            num /= base;
        }
    }
    
    if (negative) {
        buf[i++] = '-';
    }
    
    /* Print in reverse */
    while (i > 0) {
        putchar_console(buf[--i]);
    }
}

void console_init(void) {
    vga_init();
    serial_init();
}

int kprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int count = 0;
    
    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            switch (format[i]) {
                case 'd':
                case 'i': {
                    int val = va_arg(args, int);
                    print_num(val, 10, true);
                    break;
                }
                case 'u': {
                    unsigned int val = va_arg(args, unsigned int);
                    print_num(val, 10, false);
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned int val = va_arg(args, unsigned int);
                    print_num(val, 16, false);
                    break;
                }
                case 'p': {
                    void *ptr = va_arg(args, void *);
                    puts_console("0x");
                    print_num((unsigned long long)ptr, 16, false);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    if (str) {
                        puts_console(str);
                    } else {
                        puts_console("(null)");
                    }
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar_console(c);
                    break;
                }
                case 'l': {
                    if (format[i + 1] == 'u') {
                        i++;
                        unsigned long val = va_arg(args, unsigned long);
                        print_num(val, 10, false);
                    } else if (format[i + 1] == 'd') {
                        i++;
                        long val = va_arg(args, long);
                        print_num(val, 10, true);
                    }
                    break;
                }
                case '%':
                    putchar_console('%');
                    break;
                default:
                    putchar_console('%');
                    putchar_console(format[i]);
                    break;
            }
            count++;
        } else {
            putchar_console(format[i]);
            count++;
        }
    }
    
    va_end(args);
    return count;
}
