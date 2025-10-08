/**
 * Ephemeris Provider - Oracle of Time
 * 
 * Provides celestial data to guide kernel and scheduler decisions.
 * Supports both online (real-time) and offline (deterministic) modes.
 */

#ifndef EPHEMERIS_PROVIDER_H
#define EPHEMERIS_PROVIDER_H

#include <time.h>
#include <stdbool.h>

/* Lunar Phases */
typedef enum {
    MOON_NEW = 0,
    MOON_WAXING_CRESCENT,
    MOON_FIRST_QUARTER,
    MOON_WAXING_GIBBOUS,
    MOON_FULL,
    MOON_WANING_GIBBOUS,
    MOON_LAST_QUARTER,
    MOON_WANING_CRESCENT
} moon_phase_t;

/* Planet Position */
typedef struct {
    char name[16];
    char sign[16];      /* Zodiac sign */
    double degree;      /* 0-360 degrees */
} planet_position_t;

/* Celestial Data */
typedef struct {
    time_t timestamp;
    moon_phase_t moon_phase;
    double moon_illumination; /* 0.0 - 1.0 */
    int numerology_day;       /* 1-31 */
    planet_position_t planets[10]; /* Sun, Moon, Mercury, Venus, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto */
    int planet_count;
} celestial_data_t;

/* Ephemeris Provider Interface */
int ephemeris_init(bool online_mode);
int ephemeris_shutdown(void);
int ephemeris_get_current_data(celestial_data_t *data);
int ephemeris_get_data_at_time(time_t timestamp, celestial_data_t *data);
int ephemeris_sync_online(void);

/* Helper functions */
const char* ephemeris_moon_phase_name(moon_phase_t phase);
double ephemeris_calculate_moon_phase(time_t timestamp);
int ephemeris_calculate_numerology_day(time_t timestamp);

#endif /* EPHEMERIS_PROVIDER_H */
