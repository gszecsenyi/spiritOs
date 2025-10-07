/**
 * libspiro - Userland Library
 * 
 * Provides abstraction for spiritual syscalls and ritual management
 */

#ifndef LIBSPIRO_H
#define LIBSPIRO_H

#include <time.h>
#include <stdbool.h>

/* Ritual Information */
typedef struct {
    char name[64];
    char trigger[256];
    char exec_path[256];
    bool active;
    int execution_count;
    time_t last_execution;
} ritual_info_t;

/* Location for astral calculations */
typedef struct {
    double latitude;
    double longitude;
} spiro_location_t;

/* Astral State */
typedef struct {
    time_t timestamp;
    double moon_phase;
    double moon_illumination;
    int numerology_day;
    char planets_json[512];
} spiro_astral_state_t;

/* Library initialization */
int spiro_init(void);
int spiro_shutdown(void);

/* Ritual Management */
int spiro_register_ritual(const char *name, const char *trigger, const char *exec_path);
int spiro_unregister_ritual(const char *name);
int spiro_query_ritual_status(const char *name, ritual_info_t *info);
int spiro_list_rituals(ritual_info_t *rituals, int max_count);

/* Simulation */
int spiro_simulate_ritual(const char *name, time_t timestamp, spiro_location_t location);
int spiro_get_astral_state(time_t timestamp, spiro_location_t location, 
                           spiro_astral_state_t *state);

/* Triggers */
int spiro_add_trigger(const char *name, const char *expression, const char *exec_path);
int spiro_remove_trigger(const char *name);

/* Profile Management */
int spiro_load_profile(const char *profile_name);
int spiro_save_profile(const char *profile_name);

#endif /* LIBSPIRO_H */
