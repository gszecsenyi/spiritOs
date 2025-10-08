/**
 * libspiro - Implementation
 * 
 * Userland abstraction for SpiritOS
 */

#include "libspiro.h"
#include "../../kernel/soul_core.h"
#include "../../kernel/destiny_engine.h"
#include "../../kernel/ephemeris_provider.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_initialized = false;

/**
 * Initialize the library
 */
int spiro_init(void) {
    if (is_initialized) {
        return 0;
    }
    
    printf("[LIBSPIRO] Initializing spiritual userland library...\n");
    is_initialized = true;
    return 0;
}

/**
 * Shutdown the library
 */
int spiro_shutdown(void) {
    if (!is_initialized) {
        return 0;
    }
    
    printf("[LIBSPIRO] Shutting down...\n");
    is_initialized = false;
    return 0;
}

/**
 * Register a ritual
 */
int spiro_register_ritual(const char *name, const char *trigger, const char *exec_path) {
    if (!is_initialized) {
        fprintf(stderr, "[LIBSPIRO] Library not initialized\n");
        return -1;
    }
    
    printf("[LIBSPIRO] Registering ritual: %s\n", name);
    return destiny_engine_add_trigger(name, trigger, exec_path, EXEC_MODE_NATIVE);
}

/**
 * Unregister a ritual
 */
int spiro_unregister_ritual(const char *name) {
    if (!is_initialized) {
        return -1;
    }
    
    printf("[LIBSPIRO] Unregistering ritual: %s\n", name);
    return destiny_engine_remove_trigger(name);
}

/**
 * Query ritual status
 */
int spiro_query_ritual_status(const char *name, ritual_info_t *info) {
    if (!is_initialized || !info) {
        return -1;
    }
    
    trigger_t *trigger = destiny_engine_get_trigger(name);
    if (!trigger) {
        return -1;
    }
    
    strncpy(info->name, trigger->name, sizeof(info->name) - 1);
    strncpy(info->trigger, trigger->expression, sizeof(info->trigger) - 1);
    strncpy(info->exec_path, trigger->exec_path, sizeof(info->exec_path) - 1);
    info->active = trigger->active;
    info->execution_count = 0; /* Would track this in real implementation */
    info->last_execution = 0;
    
    return 0;
}

/**
 * List all rituals
 */
int spiro_list_rituals(ritual_info_t *rituals, int max_count) {
    if (!is_initialized) {
        return -1;
    }
    
    trigger_t triggers[128];
    int count = destiny_engine_list_triggers(triggers, 128);
    
    if (count > max_count) count = max_count;
    
    for (int i = 0; i < count; i++) {
        strncpy(rituals[i].name, triggers[i].name, sizeof(rituals[i].name) - 1);
        strncpy(rituals[i].trigger, triggers[i].expression, sizeof(rituals[i].trigger) - 1);
        strncpy(rituals[i].exec_path, triggers[i].exec_path, sizeof(rituals[i].exec_path) - 1);
        rituals[i].active = triggers[i].active;
        rituals[i].execution_count = 0;
        rituals[i].last_execution = 0;
    }
    
    return count;
}

/**
 * Simulate a ritual at a specific time
 */
int spiro_simulate_ritual(const char *name, time_t timestamp, spiro_location_t location) {
    if (!is_initialized) {
        return -1;
    }
    
    (void)location; /* Unused for now */
    
    printf("[LIBSPIRO] Simulating ritual '%s' at timestamp %ld\n", name, timestamp);
    
    celestial_data_t data;
    if (ephemeris_get_data_at_time(timestamp, &data) != 0) {
        return -1;
    }
    
    trigger_t *trigger = destiny_engine_get_trigger(name);
    if (!trigger) {
        fprintf(stderr, "[LIBSPIRO] Ritual not found: %s\n", name);
        return -1;
    }
    
    bool would_trigger = destiny_engine_evaluate_trigger(trigger->expression, &data);
    
    printf("[LIBSPIRO] Simulation result: %s\n", would_trigger ? "WOULD TRIGGER" : "would not trigger");
    return would_trigger ? 1 : 0;
}

/**
 * Get astral state
 */
int spiro_get_astral_state(time_t timestamp, spiro_location_t location, 
                           spiro_astral_state_t *state) {
    if (!is_initialized || !state) {
        return -1;
    }
    
    (void)location; /* Unused for now */
    
    celestial_data_t data;
    if (ephemeris_get_data_at_time(timestamp, &data) != 0) {
        return -1;
    }
    
    state->timestamp = data.timestamp;
    state->moon_phase = (double)data.moon_phase / 8.0;
    state->moon_illumination = data.moon_illumination;
    state->numerology_day = data.numerology_day;
    
    /* Format planets as JSON */
    int offset = 0;
    offset += snprintf(state->planets_json + offset, 
                      sizeof(state->planets_json) - offset, "[");
    
    for (int i = 0; i < data.planet_count && i < 5; i++) {
        offset += snprintf(state->planets_json + offset,
                          sizeof(state->planets_json) - offset,
                          "{\"name\":\"%s\",\"sign\":\"%s\"}%s",
                          data.planets[i].name,
                          data.planets[i].sign,
                          (i < data.planet_count - 1 && i < 4) ? "," : "");
    }
    
    snprintf(state->planets_json + offset,
             sizeof(state->planets_json) - offset, "]");
    
    return 0;
}

/**
 * Add a trigger (delegates to destiny_engine)
 */
int spiro_add_trigger(const char *name, const char *expression, const char *exec_path) {
    return destiny_engine_add_trigger(name, expression, exec_path, EXEC_MODE_NATIVE);
}

/**
 * Remove a trigger (delegates to destiny_engine)
 */
int spiro_remove_trigger(const char *name) {
    return destiny_engine_remove_trigger(name);
}

/**
 * Load a profile
 */
int spiro_load_profile(const char *profile_name) {
    return destiny_engine_load_profile(profile_name);
}

/**
 * Save a profile
 */
int spiro_save_profile(const char *profile_name) {
    return destiny_engine_save_profile(profile_name);
}
