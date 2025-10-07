/**
 * Destiny Engine - Lunar Scheduler
 * 
 * The scheduler that orchestrates when processes (rituals) awaken
 * based on cosmic and astral influences.
 */

#ifndef DESTINY_ENGINE_H
#define DESTINY_ENGINE_H

#include "soul_core.h"
#include "ephemeris_provider.h"
#include <stdbool.h>

/* Ritual Execution Mode */
typedef enum {
    EXEC_MODE_NATIVE,
    EXEC_MODE_SANDBOX,
    EXEC_MODE_OBSERVER
} execution_mode_t;

/* Trigger Definition */
typedef struct {
    char name[64];
    char expression[256];    /* DSL trigger expression */
    char exec_path[256];
    execution_mode_t mode;
    bool active;
} trigger_t;

/* Ritual Profile */
typedef struct {
    char name[64];
    char tradition[32];      /* e.g., "Wicca", "Astrology", "Numerology" */
    int trigger_count;
    trigger_t triggers[32];
} ritual_profile_t;

/* Destiny Engine Interface */
int destiny_engine_init(void);
int destiny_engine_shutdown(void);
int destiny_engine_tick(void);

/* Trigger Management */
int destiny_engine_add_trigger(const char *name, const char *expr, 
                               const char *exec_path, execution_mode_t mode);
int destiny_engine_remove_trigger(const char *name);
trigger_t* destiny_engine_get_trigger(const char *name);
int destiny_engine_list_triggers(trigger_t *triggers, int max_count);

/* Profile Management */
int destiny_engine_load_profile(const char *profile_name);
int destiny_engine_save_profile(const char *profile_name);

/* Evaluation */
bool destiny_engine_evaluate_trigger(const char *expression, celestial_data_t *data);
int destiny_engine_calculate_astral_priority(int base_priority, celestial_data_t *data);

#endif /* DESTINY_ENGINE_H */
