/**
 * Destiny Engine - Implementation
 * 
 * Orchestrates the awakening of rituals based on cosmic conditions
 */

#include "destiny_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIGGERS 128

static trigger_t trigger_registry[MAX_TRIGGERS];
static int trigger_count = 0;
static ritual_profile_t current_profile;

/**
 * Initialize the Destiny Engine
 */
int destiny_engine_init(void) {
    memset(trigger_registry, 0, sizeof(trigger_registry));
    trigger_count = 0;
    memset(&current_profile, 0, sizeof(current_profile));
    
    printf("[DESTINY ENGINE] Awakening... Cosmic orchestration begins.\n");
    return 0;
}

/**
 * Shutdown the engine
 */
int destiny_engine_shutdown(void) {
    printf("[DESTINY ENGINE] The wheel of destiny stops turning...\n");
    return 0;
}

/**
 * Add a trigger to the registry
 */
int destiny_engine_add_trigger(const char *name, const char *expr, 
                               const char *exec_path, execution_mode_t mode) {
    if (trigger_count >= MAX_TRIGGERS) {
        fprintf(stderr, "[DESTINY ENGINE] Trigger registry full\n");
        return -1;
    }
    
    trigger_t *trigger = &trigger_registry[trigger_count];
    strncpy(trigger->name, name, sizeof(trigger->name) - 1);
    strncpy(trigger->expression, expr, sizeof(trigger->expression) - 1);
    strncpy(trigger->exec_path, exec_path, sizeof(trigger->exec_path) - 1);
    trigger->mode = mode;
    trigger->active = true;
    
    trigger_count++;
    printf("[DESTINY ENGINE] Trigger registered: '%s'\n", name);
    return 0;
}

/**
 * Remove a trigger
 */
int destiny_engine_remove_trigger(const char *name) {
    for (int i = 0; i < trigger_count; i++) {
        if (strcmp(trigger_registry[i].name, name) == 0) {
            /* Shift remaining triggers */
            for (int j = i; j < trigger_count - 1; j++) {
                trigger_registry[j] = trigger_registry[j + 1];
            }
            trigger_count--;
            printf("[DESTINY ENGINE] Trigger removed: '%s'\n", name);
            return 0;
        }
    }
    return -1;
}

/**
 * Get a trigger by name
 */
trigger_t* destiny_engine_get_trigger(const char *name) {
    for (int i = 0; i < trigger_count; i++) {
        if (strcmp(trigger_registry[i].name, name) == 0) {
            return &trigger_registry[i];
        }
    }
    return NULL;
}

/**
 * List all triggers
 */
int destiny_engine_list_triggers(trigger_t *triggers, int max_count) {
    int count = trigger_count < max_count ? trigger_count : max_count;
    memcpy(triggers, trigger_registry, count * sizeof(trigger_t));
    return count;
}

/**
 * Simple trigger expression evaluator
 * Supports basic conditions like: moon == "Full", numerology_day == 7
 */
bool destiny_engine_evaluate_trigger(const char *expression, celestial_data_t *data) {
    /* Simplified evaluation - in real implementation, use proper parser */
    
    /* Check for Full Moon */
    if (strstr(expression, "moon == \"Full\"") != NULL) {
        if (data->moon_phase != MOON_FULL) {
            return false;
        }
    }
    
    /* Check for New Moon */
    if (strstr(expression, "moon == \"New\"") != NULL) {
        if (data->moon_phase != MOON_NEW) {
            return false;
        }
    }
    
    /* Check numerology day */
    char day_check[32];
    for (int day = 1; day <= 31; day++) {
        snprintf(day_check, sizeof(day_check), "numerology_day == %d", day);
        if (strstr(expression, day_check) != NULL) {
            if (data->numerology_day != day) {
                return false;
            }
        }
    }
    
    /* Check Mars in Scorpio (simplified) */
    if (strstr(expression, "planet[\"Mars\"].sign == \"Scorpio\"") != NULL) {
        bool mars_in_scorpio = false;
        for (int i = 0; i < data->planet_count; i++) {
            if (strcmp(data->planets[i].name, "Mars") == 0 &&
                strcmp(data->planets[i].sign, "Scorpio") == 0) {
                mars_in_scorpio = true;
                break;
            }
        }
        if (!mars_in_scorpio) {
            return false;
        }
    }
    
    /* If we got here, all conditions passed */
    return true;
}

/**
 * Calculate astral priority
 * Priority = base_priority + moon_influence + planet_influence
 */
int destiny_engine_calculate_astral_priority(int base_priority, celestial_data_t *data) {
    int priority = base_priority;
    
    /* Moon phase influence */
    switch (data->moon_phase) {
        case MOON_FULL:
            priority += 10;
            break;
        case MOON_NEW:
            priority += 5;
            break;
        case MOON_FIRST_QUARTER:
        case MOON_LAST_QUARTER:
            priority += 3;
            break;
        default:
            priority += 1;
            break;
    }
    
    /* Moon illumination influence */
    priority += (int)(data->moon_illumination * 5.0);
    
    /* Numerology influence (7 is powerful) */
    if (data->numerology_day == 7 || data->numerology_day == 14 || 
        data->numerology_day == 21 || data->numerology_day == 28) {
        priority += 3;
    }
    
    return priority;
}

/**
 * Execute the destiny tick - evaluate triggers and awaken rituals
 */
int destiny_engine_tick(void) {
    celestial_data_t data;
    
    /* Get current celestial state */
    if (ephemeris_get_current_data(&data) != 0) {
        fprintf(stderr, "[DESTINY ENGINE] Failed to get celestial data\n");
        return -1;
    }
    
    printf("[DESTINY ENGINE] Cosmic tick - Moon: %s (%.1f%% illuminated), Day: %d\n",
           ephemeris_moon_phase_name(data.moon_phase),
           data.moon_illumination * 100.0,
           data.numerology_day);
    
    /* Evaluate all active triggers */
    int awakened = 0;
    for (int i = 0; i < trigger_count; i++) {
        if (!trigger_registry[i].active) continue;
        
        if (destiny_engine_evaluate_trigger(trigger_registry[i].expression, &data)) {
            printf("[DESTINY ENGINE] Trigger awakened: '%s' -> %s\n",
                   trigger_registry[i].name,
                   trigger_registry[i].exec_path);
            awakened++;
            
            /* In real implementation, spawn ritual handler here */
        }
    }
    
    if (awakened > 0) {
        printf("[DESTINY ENGINE] %d ritual(s) awakened this cosmic tick\n", awakened);
    }
    
    return awakened;
}

/**
 * Load a profile (stub)
 */
int destiny_engine_load_profile(const char *profile_name) {
    printf("[DESTINY ENGINE] Loading profile: %s\n", profile_name);
    strncpy(current_profile.name, profile_name, sizeof(current_profile.name) - 1);
    return 0;
}

/**
 * Save a profile (stub)
 */
int destiny_engine_save_profile(const char *profile_name) {
    printf("[DESTINY ENGINE] Saving profile: %s\n", profile_name);
    return 0;
}
