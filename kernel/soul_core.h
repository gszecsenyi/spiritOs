/**
 * Soul Core - The Kernel Heart of SpiritOS
 * 
 * This module represents the "Soul" of the system, maintaining
 * process life cycles and spiritual metadata for all entities.
 */

#ifndef SOUL_CORE_H
#define SOUL_CORE_H

#include <stdint.h>
#include <stdbool.h>

/* Spiritual Metadata for Process Control Blocks */
typedef struct {
    float moon_affinity;        /* 0.0 - 1.0 affinity to lunar cycles */
    char ritual_tag[64];        /* Tag identifying the ritual type */
    int astral_priority;        /* Priority influenced by cosmic forces */
    char trigger_conditions[256]; /* DSL expression for awakening */
} spiritual_metadata_t;

/* Process Control Block (Extended) */
typedef struct {
    uint32_t pid;
    uint32_t state;             /* BIRTH, EXECUTING, DEATH */
    spiritual_metadata_t spirit;
    void *context;              /* CPU context */
    uint64_t astral_birth_tick; /* Cosmic tick at process creation */
} process_control_block_t;

/* Process States */
#define PROCESS_STATE_BIRTH     0x01
#define PROCESS_STATE_EXECUTING 0x02
#define PROCESS_STATE_DEATH     0x03
#define PROCESS_STATE_DORMANT   0x04

/* Spiritual Syscalls */
typedef struct {
    double timestamp;
    double latitude;
    double longitude;
} location_t;

typedef struct {
    double moon_phase;          /* 0.0 - 1.0 */
    double moon_illumination;   /* 0.0 - 1.0 */
    char planet_positions[512]; /* JSON string */
    int numerology_day;
} astral_snapshot_t;

/* Kernel API Functions */
int spiro_query_astral_state(double timestamp, location_t location, astral_snapshot_t *snapshot);
int spiro_set_trigger(const char *name, const char *trigger_expr, const char *exec_path);
int spiro_remove_trigger(const char *name);
int spiro_subscribe_events(int event_fd, const char *filter_expr);

/* Soul Core Management */
int soul_core_init(void);
int soul_core_create_process(const char *ritual_tag, const char *trigger_conditions);
int soul_core_destroy_process(uint32_t pid);
process_control_block_t* soul_core_get_pcb(uint32_t pid);

/* Astral tick management */
void soul_core_tick(void);
uint64_t soul_core_get_astral_tick(void);

#endif /* SOUL_CORE_H */
