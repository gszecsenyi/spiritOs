/**
 * SpiritOS Kernel - Main Entry Point
 * 
 * The Soul Core awakens here
 */

#include "soul_core.h"
#include "ephemeris_provider.h"
#include "destiny_engine.h"
#include "astral_fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

static volatile bool keep_running = true;

void signal_handler(int signum) {
    printf("\n[KERNEL] Shutdown signal received...\n");
    keep_running = false;
}

int main(int argc, char *argv[]) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║            SpiritOS - Spiritual Operating System      ║\n");
    printf("║                  Soul Core Awakening                  ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* Register signal handlers */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    /* Initialize kernel components */
    printf("[KERNEL] Initializing kernel components...\n");
    
    if (soul_core_init() != 0) {
        fprintf(stderr, "[KERNEL] Failed to initialize Soul Core\n");
        return 1;
    }
    
    if (ephemeris_init(false) != 0) {
        fprintf(stderr, "[KERNEL] Failed to initialize Ephemeris Provider\n");
        return 1;
    }
    
    if (destiny_engine_init() != 0) {
        fprintf(stderr, "[KERNEL] Failed to initialize Destiny Engine\n");
        return 1;
    }
    
    if (astral_fs_init() != 0) {
        fprintf(stderr, "[KERNEL] Failed to initialize Astral FS\n");
        return 1;
    }
    
    /* Mount the astral file system */
    if (astral_fs_mount("/astral") != 0) {
        fprintf(stderr, "[KERNEL] Failed to mount Astral FS\n");
        return 1;
    }
    
    printf("\n[KERNEL] ✨ SpiritOS is now alive ✨\n\n");
    
    /* Add some example triggers */
    printf("[KERNEL] Registering example triggers...\n");
    destiny_engine_add_trigger("full_moon_ritual", 
                               "moon == \"Full\"",
                               "/usr/bin/full_moon_handler",
                               EXEC_MODE_NATIVE);
    
    destiny_engine_add_trigger("new_moon_ritual",
                               "moon == \"New\"",
                               "/usr/bin/new_moon_handler",
                               EXEC_MODE_NATIVE);
    
    destiny_engine_add_trigger("lucky_seven",
                               "numerology_day == 7",
                               "/usr/bin/lucky_day_handler",
                               EXEC_MODE_NATIVE);
    
    printf("\n");
    
    /* Main cosmic tick loop */
    printf("[KERNEL] Entering cosmic tick loop...\n");
    printf("[KERNEL] Press Ctrl+C to shutdown\n\n");
    
    int tick_count = 0;
    while (keep_running) {
        /* Update astral state */
        celestial_data_t data;
        if (ephemeris_get_current_data(&data) == 0) {
            astral_fs_update_state(&data);
        }
        
        /* Execute destiny tick */
        destiny_engine_tick();
        
        /* Increment astral tick */
        soul_core_tick();
        
        tick_count++;
        
        /* Sleep for a cosmic moment (5 seconds for demo) */
        sleep(5);
        
        /* Show periodic status */
        if (tick_count % 12 == 0) {
            printf("\n[KERNEL] Cosmic heartbeat: %d ticks, Astral Tick: %lu\n",
                   tick_count, soul_core_get_astral_tick());
        }
    }
    
    /* Shutdown */
    printf("\n[KERNEL] Beginning shutdown sequence...\n");
    
    astral_fs_unmount();
    astral_fs_shutdown();
    destiny_engine_shutdown();
    ephemeris_shutdown();
    soul_core_init(); /* Reset state */
    
    printf("[KERNEL] SpiritOS has returned to the cosmic void.\n");
    printf("         Until we meet again... ✨\n\n");
    
    return 0;
}
