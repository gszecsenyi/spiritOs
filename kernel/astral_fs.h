/**
 * Virtual Astral File System (/astral)
 * 
 * Exposes cosmic and spiritual state as readable files
 */

#ifndef ASTRAL_FS_H
#define ASTRAL_FS_H

#include "ephemeris_provider.h"

/* Virtual file paths */
#define ASTRAL_ROOT "/astral"
#define ASTRAL_MOON_PHASE ASTRAL_ROOT "/moon_phase"
#define ASTRAL_MOON_ILLUMINATION ASTRAL_ROOT "/moon_illumination"
#define ASTRAL_PLANETS ASTRAL_ROOT "/planet_positions.json"
#define ASTRAL_NUMEROLOGY ASTRAL_ROOT "/numerology_day"
#define ASTRAL_TRIGGERS ASTRAL_ROOT "/triggers"
#define ASTRAL_PROFILES ASTRAL_ROOT "/profiles"

/* Astral FS Interface */
int astral_fs_init(void);
int astral_fs_shutdown(void);
int astral_fs_mount(const char *mount_point);
int astral_fs_unmount(void);

/* Virtual file operations */
int astral_fs_read(const char *path, char *buffer, size_t size);
int astral_fs_write(const char *path, const char *buffer, size_t size);
int astral_fs_list(const char *path, char **entries, int max_entries);

/* Update functions */
int astral_fs_update_state(celestial_data_t *data);

#endif /* ASTRAL_FS_H */
