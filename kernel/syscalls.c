/**
 * Spiritual Syscalls Implementation
 * 
 * System call interface for userland to interact with the Soul Core
 */

#include "soul_core.h"
#include "ephemeris_provider.h"
#include "destiny_engine.h"
#include <stdio.h>
#include <string.h>

/**
 * Query the astral state at a given time and location
 */
int spiro_query_astral_state(double timestamp, location_t location, astral_snapshot_t *snapshot) {
    if (!snapshot) return -1;
    
    celestial_data_t data;
    time_t time = (time_t)timestamp;
    
    if (ephemeris_get_data_at_time(time, &data) != 0) {
        return -1;
    }
    
    /* Convert to snapshot format */
    snapshot->moon_phase = (double)data.moon_phase / 8.0;
    snapshot->moon_illumination = data.moon_illumination;
    snapshot->numerology_day = data.numerology_day;
    
    /* Format planet positions as JSON string */
    int offset = 0;
    offset += snprintf(snapshot->planet_positions + offset, 
                      sizeof(snapshot->planet_positions) - offset, "[");
    
    for (int i = 0; i < data.planet_count && i < 5; i++) {
        offset += snprintf(snapshot->planet_positions + offset,
                          sizeof(snapshot->planet_positions) - offset,
                          "{\"name\":\"%s\",\"sign\":\"%s\",\"degree\":%.1f}%s",
                          data.planets[i].name,
                          data.planets[i].sign,
                          data.planets[i].degree,
                          (i < data.planet_count - 1 && i < 4) ? "," : "");
    }
    
    snprintf(snapshot->planet_positions + offset,
             sizeof(snapshot->planet_positions) - offset, "]");
    
    return 0;
}

/**
 * Set a trigger
 */
int spiro_set_trigger(const char *name, const char *trigger_expr, const char *exec_path) {
    return destiny_engine_add_trigger(name, trigger_expr, exec_path, EXEC_MODE_NATIVE);
}

/**
 * Remove a trigger
 */
int spiro_remove_trigger(const char *name) {
    return destiny_engine_remove_trigger(name);
}

/**
 * Subscribe to events (stub)
 */
int spiro_subscribe_events(int event_fd, const char *filter_expr) {
    printf("[SYSCALL] Event subscription registered: fd=%d, filter='%s'\n", 
           event_fd, filter_expr);
    return 0;
}
