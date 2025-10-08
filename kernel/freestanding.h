/**
 * SpiritOS Freestanding Compatibility Header
 * 
 * Maps standard library functions to freestanding implementations
 * Include this instead of standard headers in freestanding kernel code
 */

#ifndef FREESTANDING_H
#define FREESTANDING_H

/* When building for userland tools, use standard headers */
#ifdef USERLAND_BUILD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#else
/* Freestanding kernel build - use custom implementations */

/* Standard types */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

/* String functions */
#include "hal/kstring.h"

/* Console I/O */
#include "hal/kprintf.h"
#include "hal/timer.h"

/* Redefine standard I/O functions to kernel equivalents */
#define printf kprintf
#define fprintf(stream, ...) kprintf(__VA_ARGS__)
#define stderr ((void*)0)

/* snprintf implementation for freestanding */
int snprintf(char *str, size_t size, const char *format, ...);

/* Time functions - stub implementations */
typedef long time_t;

/* Math functions - simple implementations for freestanding */
static inline double fmod(double x, double y) {
    /* Simple fmod implementation */
    if (y == 0.0) return 0.0;
    double quot = x / y;
    quot = (double)((int)quot);  /* Truncate to integer */
    return x - quot * y;
}

static inline double fabs(double x) {
    return (x < 0.0) ? -x : x;
}

/* Basic tm structure */
struct tm {
    int tm_sec;    /* seconds */
    int tm_min;    /* minutes */
    int tm_hour;   /* hours */
    int tm_mday;   /* day of the month */
    int tm_mon;    /* month */
    int tm_year;   /* year */
    int tm_wday;   /* day of the week */
    int tm_yday;   /* day in the year */
    int tm_isdst;  /* daylight saving time */
};

static inline time_t time(time_t *t) {
    time_t now = 1704067200; /* Fixed time: 2024-01-01 00:00:00 UTC */
    if (t) *t = now;
    return now;
}

static inline double difftime(time_t time1, time_t time0) {
    return (double)(time1 - time0);
}

static inline struct tm *localtime(const time_t *timep) {
    static struct tm tm_result;
    /* Simple stub - returns a fixed date */
    tm_result.tm_sec = 0;
    tm_result.tm_min = 0;
    tm_result.tm_hour = 0;
    tm_result.tm_mday = 1;   /* Day of month */
    tm_result.tm_mon = 0;    /* January */
    tm_result.tm_year = 124; /* 2024 - 1900 */
    tm_result.tm_wday = 1;   /* Monday */
    tm_result.tm_yday = 0;
    tm_result.tm_isdst = 0;
    (void)timep; /* Unused for now */
    return &tm_result;
}

/* No-op stubs for functions not needed in freestanding */
#define sleep(x) delay_ms((x) * 1000)
#define malloc(x) ((void*)0)
#define free(x) ((void)0)
#define exit(x) while(1) { __asm__ volatile ("hlt"); }

#endif /* USERLAND_BUILD */

#endif /* FREESTANDING_H */
