/**
 * Ephemeris Provider - Implementation
 * 
 * Oracle of Time that provides celestial guidance
 */

#include "ephemeris_provider.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static bool is_online_mode = false;
static const char* MOON_PHASE_NAMES[] = {
    "New Moon",
    "Waxing Crescent",
    "First Quarter",
    "Waxing Gibbous",
    "Full Moon",
    "Waning Gibbous",
    "Last Quarter",
    "Waning Crescent"
};

static const char* ZODIAC_SIGNS[] = {
    "Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo",
    "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces"
};

/**
 * Initialize the Ephemeris Provider
 */
int ephemeris_init(bool online_mode) {
    is_online_mode = online_mode;
    
    if (online_mode) {
        printf("[ORACLE] Awakening in ONLINE mode - connecting to cosmic sources...\n");
        printf("[ORACLE] Note: Online mode requires external API (not implemented yet)\n");
    } else {
        printf("[ORACLE] Awakening in OFFLINE mode - using deterministic simulation\n");
    }
    
    return 0;
}

/**
 * Shutdown the provider
 */
int ephemeris_shutdown(void) {
    printf("[ORACLE] The Oracle sleeps...\n");
    return 0;
}

/**
 * Calculate moon phase based on simplified lunation cycle
 * Using a 29.53-day synodic month
 */
double ephemeris_calculate_moon_phase(time_t timestamp) {
    /* Known new moon: January 6, 2000, 18:14 UTC */
    const time_t known_new_moon = 947182440;
    const double synodic_month = 29.530588853; /* days */
    
    double days_since = difftime(timestamp, known_new_moon) / 86400.0;
    double phase = fmod(days_since, synodic_month) / synodic_month;
    
    return phase; /* 0.0 = new, 0.5 = full */
}

/**
 * Get moon phase enum from phase value
 */
moon_phase_t ephemeris_get_moon_phase_enum(double phase) {
    if (phase < 0.0625) return MOON_NEW;
    if (phase < 0.1875) return MOON_WAXING_CRESCENT;
    if (phase < 0.3125) return MOON_FIRST_QUARTER;
    if (phase < 0.4375) return MOON_WAXING_GIBBOUS;
    if (phase < 0.5625) return MOON_FULL;
    if (phase < 0.6875) return MOON_WANING_GIBBOUS;
    if (phase < 0.8125) return MOON_LAST_QUARTER;
    if (phase < 0.9375) return MOON_WANING_CRESCENT;
    return MOON_NEW;
}

/**
 * Calculate numerology day
 */
int ephemeris_calculate_numerology_day(time_t timestamp) {
    struct tm *tm_info = localtime(&timestamp);
    return tm_info->tm_mday;
}

/**
 * Simulate planet positions (deterministic)
 */
void ephemeris_simulate_planets(time_t timestamp, celestial_data_t *data) {
    /* Simplified planetary motion simulation */
    const char* planet_names[] = {"Sun", "Moon", "Mercury", "Venus", "Mars", 
                                   "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
    const double orbital_periods[] = {365.25, 27.32, 87.97, 224.70, 686.98, 
                                      4332.59, 10759.22, 30688.5, 60182, 90560};
    
    data->planet_count = 10;
    for (int i = 0; i < 10; i++) {
        strncpy(data->planets[i].name, planet_names[i], sizeof(data->planets[i].name) - 1);
        
        /* Calculate position based on orbital period */
        double days_since_epoch = difftime(timestamp, 0) / 86400.0;
        double position = fmod(days_since_epoch / orbital_periods[i], 1.0) * 360.0;
        data->planets[i].degree = position;
        
        /* Determine zodiac sign (12 signs, 30 degrees each) */
        int sign_index = ((int)position / 30) % 12;
        strncpy(data->planets[i].sign, ZODIAC_SIGNS[sign_index], 
                sizeof(data->planets[i].sign) - 1);
    }
}

/**
 * Get current celestial data
 */
int ephemeris_get_current_data(celestial_data_t *data) {
    time_t now = time(NULL);
    return ephemeris_get_data_at_time(now, data);
}

/**
 * Get celestial data at specific time
 */
int ephemeris_get_data_at_time(time_t timestamp, celestial_data_t *data) {
    if (!data) return -1;
    
    data->timestamp = timestamp;
    
    /* Calculate moon phase */
    double phase = ephemeris_calculate_moon_phase(timestamp);
    data->moon_phase = ephemeris_get_moon_phase_enum(phase);
    
    /* Moon illumination (simplified: full at 0.5, new at 0.0/1.0) */
    data->moon_illumination = 1.0 - fabs(phase - 0.5) * 2.0;
    
    /* Numerology */
    data->numerology_day = ephemeris_calculate_numerology_day(timestamp);
    
    /* Planet positions */
    ephemeris_simulate_planets(timestamp, data);
    
    return 0;
}

/**
 * Sync with online source (stub)
 */
int ephemeris_sync_online(void) {
    if (!is_online_mode) {
        fprintf(stderr, "[ORACLE] Cannot sync: not in online mode\n");
        return -1;
    }
    
    printf("[ORACLE] Synchronizing with cosmic sources...\n");
    printf("[ORACLE] (Online sync not yet implemented - using offline simulation)\n");
    return 0;
}

/**
 * Get moon phase name
 */
const char* ephemeris_moon_phase_name(moon_phase_t phase) {
    if (phase >= 0 && phase < 8) {
        return MOON_PHASE_NAMES[phase];
    }
    return "Unknown";
}
