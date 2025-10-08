/**
 * SpiritOS Freestanding snprintf Implementation
 * 
 * Simple snprintf for kernel
 */

#include "freestanding.h"

int snprintf(char *str, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    if (size == 0 || str == NULL) {
        va_end(args);
        return 0;
    }
    
    size_t pos = 0;
    
    for (size_t i = 0; format[i] != '\0' && pos < size - 1; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            
            /* Helper to append string */
            char temp[32];
            const char *s = NULL;
            int num_len = 0;
            
            switch (format[i]) {
                case 'd':
                case 'i': {
                    int val = va_arg(args, int);
                    int is_neg = val < 0;
                    if (is_neg) val = -val;
                    
                    int tmp = val;
                    do {
                        temp[num_len++] = '0' + (tmp % 10);
                        tmp /= 10;
                    } while (tmp > 0);
                    
                    if (is_neg && pos < size - 1) {
                        str[pos++] = '-';
                    }
                    
                    for (int j = num_len - 1; j >= 0 && pos < size - 1; j--) {
                        str[pos++] = temp[j];
                    }
                    break;
                }
                case 'u': {
                    unsigned int val = va_arg(args, unsigned int);
                    unsigned int tmp = val;
                    
                    do {
                        temp[num_len++] = '0' + (tmp % 10);
                        tmp /= 10;
                    } while (tmp > 0);
                    
                    for (int j = num_len - 1; j >= 0 && pos < size - 1; j--) {
                        str[pos++] = temp[j];
                    }
                    break;
                }
                case 'l': {
                    if (format[i + 1] == 'd') {
                        i++;
                        long val = va_arg(args, long);
                        int is_neg = val < 0;
                        if (is_neg) val = -val;
                        
                        long tmp = val;
                        do {
                            temp[num_len++] = '0' + (tmp % 10);
                            tmp /= 10;
                        } while (tmp > 0);
                        
                        if (is_neg && pos < size - 1) {
                            str[pos++] = '-';
                        }
                        
                        for (int j = num_len - 1; j >= 0 && pos < size - 1; j--) {
                            str[pos++] = temp[j];
                        }
                    }
                    break;
                }
                case 's': {
                    s = va_arg(args, const char *);
                    if (s) {
                        while (*s && pos < size - 1) {
                            str[pos++] = *s++;
                        }
                    }
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    if (pos < size - 1) {
                        str[pos++] = c;
                    }
                    break;
                }
                case '.': {
                    /* Simple %.Xf handling - just skip precision for now */
                    while (format[i + 1] >= '0' && format[i + 1] <= '9') {
                        i++;
                    }
                    if (format[i + 1] == 'f') {
                        i++;
                        double val = va_arg(args, double);
                        int int_part = (int)val;
                        int frac_part = (int)((val - int_part) * 100);
                        
                        /* Print integer part */
                        int tmp = int_part;
                        do {
                            temp[num_len++] = '0' + (tmp % 10);
                            tmp /= 10;
                        } while (tmp > 0);
                        
                        for (int j = num_len - 1; j >= 0 && pos < size - 1; j--) {
                            str[pos++] = temp[j];
                        }
                        
                        if (pos < size - 1) str[pos++] = '.';
                        
                        /* Print fractional part (2 digits) */
                        if (pos < size - 1) str[pos++] = '0' + (frac_part / 10);
                        if (pos < size - 1) str[pos++] = '0' + (frac_part % 10);
                    }
                    break;
                }
                case '%':
                    if (pos < size - 1) {
                        str[pos++] = '%';
                    }
                    break;
                default:
                    if (pos < size - 1) {
                        str[pos++] = format[i];
                    }
                    break;
            }
        } else {
            str[pos++] = format[i];
        }
    }
    
    str[pos] = '\0';
    va_end(args);
    return pos;
}
