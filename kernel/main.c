/**
 * SpiritOS Kernel - Freestanding Main Entry Point
 * 
 * The Soul Core awakens here - Standalone x86_64 Kernel
 */

#include "hal/kprintf.h"
#include "hal/timer.h"
#include "hal/vga.h"
#include "soul_core.h"
#include "ephemeris_provider.h"
#include "destiny_engine.h"
#include "astral_fs.h"
#include <stdint.h>
#include <stdbool.h>

static volatile bool keep_running = true;

void kernel_main(uint32_t multiboot_magic, uint32_t multiboot_addr) {
    /* Initialize console first */
    console_init();
    
    kprintf("\n");
    kprintf("╔═══════════════════════════════════════════════════════╗\n");
    kprintf("║            SpiritOS - Spiritual Operating System      ║\n");
    kprintf("║                  Soul Core Awakening                  ║\n");
    kprintf("║                 Standalone x86_64 Kernel              ║\n");
    kprintf("╚═══════════════════════════════════════════════════════╝\n");
    kprintf("\n");
    
    kprintf("[KERNEL] Multiboot magic: 0x%x\n", multiboot_magic);
    kprintf("[KERNEL] Multiboot info:  0x%x\n", multiboot_addr);
    kprintf("\n");
    
    /* Initialize timer */
    kprintf("[KERNEL] Initializing timer...\n");
    timer_init();
    
    /* Initialize kernel components */
    kprintf("[KERNEL] Initializing kernel components...\n");
    
    if (soul_core_init() != 0) {
        kprintf("[KERNEL] FATAL: Failed to initialize Soul Core\n");
        goto halt;
    }
    
    if (ephemeris_init(false) != 0) {
        kprintf("[KERNEL] FATAL: Failed to initialize Ephemeris Provider\n");
        goto halt;
    }
    
    if (destiny_engine_init() != 0) {
        kprintf("[KERNEL] FATAL: Failed to initialize Destiny Engine\n");
        goto halt;
    }
    
    if (astral_fs_init() != 0) {
        kprintf("[KERNEL] FATAL: Failed to initialize Astral FS\n");
        goto halt;
    }
    
    /* Mount the astral file system */
    if (astral_fs_mount("/astral") != 0) {
        kprintf("[KERNEL] FATAL: Failed to mount Astral FS\n");
        goto halt;
    }
    
    kprintf("\n[KERNEL] ✨ SpiritOS is now alive ✨\n\n");
    
    /* Add some example triggers */
    kprintf("[KERNEL] Registering example triggers...\n");
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
    
    kprintf("\n");
    
    /* Main cosmic tick loop */
    kprintf("[KERNEL] Entering cosmic tick loop...\n");
    kprintf("[KERNEL] Running for demonstration (60 ticks)...\n\n");
    
    int tick_count = 0;
    const int max_ticks = 60;  /* Run for 60 ticks in standalone mode */
    
    while (keep_running && tick_count < max_ticks) {
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
        
        /* Delay for a cosmic moment (5 seconds for demo) */
        delay_ms(5000);
        
        /* Show periodic status */
        if (tick_count % 12 == 0) {
            kprintf("\n[KERNEL] Cosmic heartbeat: %d ticks, Astral Tick: %lu\n",
                   tick_count, soul_core_get_astral_tick());
        }
    }
    
    /* Shutdown */
    kprintf("\n[KERNEL] Beginning shutdown sequence...\n");
    
    astral_fs_unmount();
    astral_fs_shutdown();
    destiny_engine_shutdown();
    ephemeris_shutdown();
    soul_core_init(); /* Reset state */
    
    kprintf("[KERNEL] SpiritOS has returned to the cosmic void.\n");
    kprintf("         Until we meet again... ✨\n\n");

halt:
    /* Infinite loop - kernel has finished */
    kprintf("[KERNEL] System halted.\n");
    while (1) {
        __asm__ volatile ("hlt");
    }
}
