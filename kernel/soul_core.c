/**
 * Soul Core - Implementation
 * 
 * The kernel's heart that maintains all living processes
 * and their spiritual connections.
 */

#include "soul_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 256

static process_control_block_t pcb_table[MAX_PROCESSES];
static uint32_t next_pid = 1;
static uint64_t astral_tick_counter = 0;

/**
 * Initialize the Soul Core
 */
int soul_core_init(void) {
    memset(pcb_table, 0, sizeof(pcb_table));
    next_pid = 1;
    astral_tick_counter = 0;
    
    printf("[SOUL CORE] Awakening... The heart of SpiritOS begins to beat.\n");
    return 0;
}

/**
 * Create a new process with spiritual metadata
 */
int soul_core_create_process(const char *ritual_tag, const char *trigger_conditions) {
    if (next_pid >= MAX_PROCESSES) {
        fprintf(stderr, "[SOUL CORE] No more souls can be born. Maximum capacity reached.\n");
        return -1;
    }
    
    process_control_block_t *pcb = &pcb_table[next_pid];
    pcb->pid = next_pid;
    pcb->state = PROCESS_STATE_BIRTH;
    pcb->astral_birth_tick = astral_tick_counter;
    
    /* Initialize spiritual metadata */
    pcb->spirit.moon_affinity = 0.5; /* Default neutral affinity */
    pcb->spirit.astral_priority = 0;
    strncpy(pcb->spirit.ritual_tag, ritual_tag, sizeof(pcb->spirit.ritual_tag) - 1);
    strncpy(pcb->spirit.trigger_conditions, trigger_conditions, 
            sizeof(pcb->spirit.trigger_conditions) - 1);
    
    printf("[SOUL CORE] New soul born: PID=%u, Ritual='%s'\n", next_pid, ritual_tag);
    
    next_pid++;
    return pcb->pid;
}

/**
 * Destroy a process (death)
 */
int soul_core_destroy_process(uint32_t pid) {
    if (pid >= MAX_PROCESSES || pcb_table[pid].state == PROCESS_STATE_DEATH) {
        return -1;
    }
    
    pcb_table[pid].state = PROCESS_STATE_DEATH;
    printf("[SOUL CORE] Soul departed: PID=%u\n", pid);
    return 0;
}

/**
 * Get process control block
 */
process_control_block_t* soul_core_get_pcb(uint32_t pid) {
    if (pid >= MAX_PROCESSES) {
        return NULL;
    }
    return &pcb_table[pid];
}

/**
 * Advance the astral tick counter
 */
void soul_core_tick(void) {
    astral_tick_counter++;
}

/**
 * Get current astral tick
 */
uint64_t soul_core_get_astral_tick(void) {
    return astral_tick_counter;
}
