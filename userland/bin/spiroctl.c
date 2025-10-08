/**
 * spiroctl - SpiritOS Control Utility
 * 
 * Administrative CLI for managing triggers, profiles, and cosmic events
 */

#include "../lib/libspiro.h"
#include "../../kernel/ephemeris_provider.h"
#include "../../kernel/astral_fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_usage(const char *prog_name) {
    printf("SpiritOS Control Utility\n");
    printf("\nUsage: %s <command> [options]\n", prog_name);
    printf("\nCommands:\n");
    printf("  ephemeris sync              - Synchronize with cosmic sources\n");
    printf("  ephemeris show              - Display current celestial state\n");
    printf("  trigger add <name> <expr> <path> - Add a trigger\n");
    printf("  trigger list                - List all triggers\n");
    printf("  trigger remove <name>       - Remove a trigger\n");
    printf("  simulate <name> <timestamp> - Simulate ritual at given time\n");
    printf("  astral read <file>          - Read from /astral virtual FS\n");
    printf("  profile load <name>         - Load a profile\n");
    printf("  profile save <name>         - Save current profile\n");
    printf("  help                        - Show this help\n");
}

int cmd_ephemeris_sync(void) {
    printf("Synchronizing ephemeris data...\n");
    return ephemeris_sync_online();
}

int cmd_ephemeris_show(void) {
    celestial_data_t data;
    
    if (ephemeris_get_current_data(&data) != 0) {
        fprintf(stderr, "Failed to get celestial data\n");
        return -1;
    }
    
    printf("\n=== Current Celestial State ===\n");
    printf("Timestamp: %s", ctime(&data.timestamp));
    printf("Moon Phase: %s\n", ephemeris_moon_phase_name(data.moon_phase));
    printf("Moon Illumination: %.1f%%\n", data.moon_illumination * 100.0);
    printf("Numerology Day: %d\n", data.numerology_day);
    printf("\nPlanetary Positions:\n");
    
    for (int i = 0; i < data.planet_count; i++) {
        printf("  %-10s: %s (%.1f°)\n", 
               data.planets[i].name,
               data.planets[i].sign,
               data.planets[i].degree);
    }
    
    printf("\n");
    return 0;
}

int cmd_trigger_add(const char *name, const char *expr, const char *path) {
    printf("Adding trigger: %s\n", name);
    printf("  Expression: %s\n", expr);
    printf("  Path: %s\n", path);
    
    int result = spiro_add_trigger(name, expr, path);
    if (result == 0) {
        printf("Trigger added successfully\n");
    } else {
        fprintf(stderr, "Failed to add trigger\n");
    }
    
    return result;
}

int cmd_trigger_list(void) {
    ritual_info_t rituals[128];
    int count = spiro_list_rituals(rituals, 128);
    
    if (count < 0) {
        fprintf(stderr, "Failed to list triggers\n");
        return -1;
    }
    
    printf("\n=== Registered Triggers ===\n");
    if (count == 0) {
        printf("No triggers registered\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("\n[%d] %s\n", i + 1, rituals[i].name);
            printf("    Expression: %s\n", rituals[i].trigger);
            printf("    Path: %s\n", rituals[i].exec_path);
            printf("    Status: %s\n", rituals[i].active ? "Active" : "Inactive");
        }
    }
    printf("\n");
    
    return 0;
}

int cmd_trigger_remove(const char *name) {
    printf("Removing trigger: %s\n", name);
    
    int result = spiro_remove_trigger(name);
    if (result == 0) {
        printf("Trigger removed successfully\n");
    } else {
        fprintf(stderr, "Failed to remove trigger\n");
    }
    
    return result;
}

int cmd_simulate(const char *name, const char *timestamp_str) {
    time_t timestamp = atol(timestamp_str);
    spiro_location_t location = {0.0, 0.0}; /* Default location */
    
    printf("Simulating ritual '%s' at timestamp %ld\n", name, timestamp);
    
    int result = spiro_simulate_ritual(name, timestamp, location);
    return result;
}

int cmd_astral_read(const char *file) {
    char buffer[4096];
    char path[256];
    
    snprintf(path, sizeof(path), "/astral/%s", file);
    
    int bytes = astral_fs_read(path, buffer, sizeof(buffer));
    if (bytes > 0) {
        printf("%s", buffer);
        return 0;
    } else {
        fprintf(stderr, "Failed to read: %s\n", path);
        return -1;
    }
}

int cmd_profile_load(const char *name) {
    printf("Loading profile: %s\n", name);
    return spiro_load_profile(name);
}

int cmd_profile_save(const char *name) {
    printf("Saving profile: %s\n", name);
    return spiro_save_profile(name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    /* Initialize library */
    spiro_init();
    
    const char *cmd = argv[1];
    int result = 0;
    
    if (strcmp(cmd, "ephemeris") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s ephemeris <sync|show>\n", argv[0]);
            result = 1;
        } else if (strcmp(argv[2], "sync") == 0) {
            result = cmd_ephemeris_sync();
        } else if (strcmp(argv[2], "show") == 0) {
            result = cmd_ephemeris_show();
        } else {
            fprintf(stderr, "Unknown ephemeris command: %s\n", argv[2]);
            result = 1;
        }
    } else if (strcmp(cmd, "trigger") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s trigger <add|list|remove>\n", argv[0]);
            result = 1;
        } else if (strcmp(argv[2], "add") == 0) {
            if (argc < 6) {
                fprintf(stderr, "Usage: %s trigger add <name> <expr> <path>\n", argv[0]);
                result = 1;
            } else {
                result = cmd_trigger_add(argv[3], argv[4], argv[5]);
            }
        } else if (strcmp(argv[2], "list") == 0) {
            result = cmd_trigger_list();
        } else if (strcmp(argv[2], "remove") == 0) {
            if (argc < 4) {
                fprintf(stderr, "Usage: %s trigger remove <name>\n", argv[0]);
                result = 1;
            } else {
                result = cmd_trigger_remove(argv[3]);
            }
        } else {
            fprintf(stderr, "Unknown trigger command: %s\n", argv[2]);
            result = 1;
        }
    } else if (strcmp(cmd, "simulate") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s simulate <name> <timestamp>\n", argv[0]);
            result = 1;
        } else {
            result = cmd_simulate(argv[2], argv[3]);
        }
    } else if (strcmp(cmd, "astral") == 0) {
        if (argc < 4 || strcmp(argv[2], "read") != 0) {
            fprintf(stderr, "Usage: %s astral read <file>\n", argv[0]);
            result = 1;
        } else {
            result = cmd_astral_read(argv[3]);
        }
    } else if (strcmp(cmd, "profile") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s profile <load|save> <name>\n", argv[0]);
            result = 1;
        } else if (strcmp(argv[2], "load") == 0) {
            result = cmd_profile_load(argv[3]);
        } else if (strcmp(argv[2], "save") == 0) {
            result = cmd_profile_save(argv[3]);
        } else {
            fprintf(stderr, "Unknown profile command: %s\n", argv[2]);
            result = 1;
        }
    } else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "--help") == 0 || strcmp(cmd, "-h") == 0) {
        print_usage(argv[0]);
    } else {
        fprintf(stderr, "Unknown command: %s\n", cmd);
        print_usage(argv[0]);
        result = 1;
    }
    
    spiro_shutdown();
    return result;
}
