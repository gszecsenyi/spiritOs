/**
 * Virtual Astral File System - Implementation
 * 
 * A living map of cosmic influence
 */

#include "astral_fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static celestial_data_t current_state;
static bool is_mounted = false;
static char mount_point[256] = ASTRAL_ROOT;

/**
 * Initialize the Astral FS
 */
int astral_fs_init(void) {
    memset(&current_state, 0, sizeof(current_state));
    printf("[ASTRAL FS] Initializing the living map...\n");
    return 0;
}

/**
 * Shutdown the Astral FS
 */
int astral_fs_shutdown(void) {
    is_mounted = false;
    printf("[ASTRAL FS] The living map fades...\n");
    return 0;
}

/**
 * Mount the virtual file system
 */
int astral_fs_mount(const char *mount_pt) {
    if (is_mounted) {
        fprintf(stderr, "[ASTRAL FS] Already mounted\n");
        return -1;
    }
    
    strncpy(mount_point, mount_pt, sizeof(mount_point) - 1);
    is_mounted = true;
    
    printf("[ASTRAL FS] Mounted at: %s\n", mount_point);
    printf("[ASTRAL FS] Virtual files available:\n");
    printf("  %s/moon_phase\n", mount_point);
    printf("  %s/moon_illumination\n", mount_point);
    printf("  %s/planet_positions.json\n", mount_point);
    printf("  %s/numerology_day\n", mount_point);
    printf("  %s/triggers/\n", mount_point);
    printf("  %s/profiles/\n", mount_point);
    
    return 0;
}

/**
 * Unmount the file system
 */
int astral_fs_unmount(void) {
    if (!is_mounted) {
        return -1;
    }
    
    is_mounted = false;
    printf("[ASTRAL FS] Unmounted from: %s\n", mount_point);
    return 0;
}

/**
 * Update the current state
 */
int astral_fs_update_state(celestial_data_t *data) {
    if (!data) return -1;
    
    memcpy(&current_state, data, sizeof(celestial_data_t));
    return 0;
}

/**
 * Read from a virtual file
 */
int astral_fs_read(const char *path, char *buffer, size_t size) {
    if (!is_mounted || !buffer) return -1;
    
    /* moon_phase */
    if (strstr(path, "moon_phase") != NULL) {
        snprintf(buffer, size, "%s\n", ephemeris_moon_phase_name(current_state.moon_phase));
        return strlen(buffer);
    }
    
    /* moon_illumination */
    if (strstr(path, "moon_illumination") != NULL) {
        snprintf(buffer, size, "%.2f\n", current_state.moon_illumination);
        return strlen(buffer);
    }
    
    /* numerology_day */
    if (strstr(path, "numerology_day") != NULL) {
        snprintf(buffer, size, "%d\n", current_state.numerology_day);
        return strlen(buffer);
    }
    
    /* planet_positions.json */
    if (strstr(path, "planet_positions.json") != NULL) {
        int offset = 0;
        offset += snprintf(buffer + offset, size - offset, "{\n");
        offset += snprintf(buffer + offset, size - offset, "  \"timestamp\": %ld,\n", 
                          current_state.timestamp);
        offset += snprintf(buffer + offset, size - offset, "  \"planets\": [\n");
        
        for (int i = 0; i < current_state.planet_count; i++) {
            offset += snprintf(buffer + offset, size - offset,
                              "    {\"name\": \"%s\", \"sign\": \"%s\", \"degree\": %.2f}%s\n",
                              current_state.planets[i].name,
                              current_state.planets[i].sign,
                              current_state.planets[i].degree,
                              (i < current_state.planet_count - 1) ? "," : "");
        }
        
        offset += snprintf(buffer + offset, size - offset, "  ]\n");
        offset += snprintf(buffer + offset, size - offset, "}\n");
        
        return offset;
    }
    
    return -1;
}

/**
 * Write to a virtual file (limited support)
 */
int astral_fs_write(const char *path, const char *buffer, size_t size) {
    /* Most astral files are read-only */
    fprintf(stderr, "[ASTRAL FS] Write not supported for: %s\n", path);
    return -1;
}

/**
 * List directory contents
 */
int astral_fs_list(const char *path, char **entries, int max_entries) {
    if (!is_mounted) return -1;
    
    if (strcmp(path, mount_point) == 0 || strcmp(path, "/astral") == 0) {
        const char *root_files[] = {
            "moon_phase",
            "moon_illumination",
            "planet_positions.json",
            "numerology_day",
            "triggers/",
            "profiles/"
        };
        
        int count = sizeof(root_files) / sizeof(root_files[0]);
        if (count > max_entries) count = max_entries;
        
        for (int i = 0; i < count; i++) {
            entries[i] = strdup(root_files[i]);
        }
        
        return count;
    }
    
    return 0;
}
