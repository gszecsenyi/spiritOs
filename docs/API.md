# SpiritOS API Reference

## Table of Contents
- [Kernel API](#kernel-api)
- [Userland Library](#userland-library)
- [Virtual Astral Filesystem](#virtual-astral-filesystem)
- [Trigger DSL](#trigger-dsl)

---

## Kernel API

### Process Control Block (Extended)

```c
typedef struct {
    uint32_t pid;
    uint32_t state;
    spiritual_metadata_t spirit;
    void *context;
    uint64_t astral_birth_tick;
} process_control_block_t;
```

**Spiritual Metadata:**
```c
typedef struct {
    float moon_affinity;        /* 0.0 - 1.0 */
    char ritual_tag[64];
    int astral_priority;
    char trigger_conditions[256];
} spiritual_metadata_t;
```

### System Calls

#### spiro_query_astral_state()
```c
int spiro_query_astral_state(double timestamp, location_t location, 
                              astral_snapshot_t *snapshot);
```

**Parameters:**
- `timestamp`: Unix timestamp to query
- `location`: Geographic coordinates
- `snapshot`: Output buffer for astral state

**Returns:** 0 on success, -1 on error

**Example:**
```c
location_t loc = {40.7128, -74.0060}; // New York
astral_snapshot_t snapshot;
spiro_query_astral_state(time(NULL), loc, &snapshot);
```

#### spiro_set_trigger()
```c
int spiro_set_trigger(const char *name, const char *trigger_expr, 
                      const char *exec_path);
```

**Parameters:**
- `name`: Unique trigger name
- `trigger_expr`: DSL expression for activation
- `exec_path`: Path to ritual handler

**Returns:** 0 on success, -1 on error

#### spiro_remove_trigger()
```c
int spiro_remove_trigger(const char *name);
```

**Parameters:**
- `name`: Trigger name to remove

**Returns:** 0 on success, -1 on error

#### spiro_subscribe_events()
```c
int spiro_subscribe_events(int event_fd, const char *filter_expr);
```

**Parameters:**
- `event_fd`: File descriptor for event delivery
- `filter_expr`: Filter expression for events

**Returns:** 0 on success, -1 on error

---

## Userland Library

### Initialization

#### spiro_init()
```c
int spiro_init(void);
```

Initializes the userland library. Must be called before any other library functions.

**Returns:** 0 on success, -1 on error

#### spiro_shutdown()
```c
int spiro_shutdown(void);
```

Shuts down the library and releases resources.

### Ritual Management

#### spiro_register_ritual()
```c
int spiro_register_ritual(const char *name, const char *trigger, 
                          const char *exec_path);
```

**Example:**
```c
spiro_init();
spiro_register_ritual("full_moon_celebration", 
                      "moon == \"Full\"",
                      "/usr/bin/celebrate");
```

#### spiro_query_ritual_status()
```c
int spiro_query_ritual_status(const char *name, ritual_info_t *info);
```

**Ritual Info Structure:**
```c
typedef struct {
    char name[64];
    char trigger[256];
    char exec_path[256];
    bool active;
    int execution_count;
    time_t last_execution;
} ritual_info_t;
```

#### spiro_list_rituals()
```c
int spiro_list_rituals(ritual_info_t *rituals, int max_count);
```

**Returns:** Number of rituals returned

### Simulation

#### spiro_simulate_ritual()
```c
int spiro_simulate_ritual(const char *name, time_t timestamp, 
                          spiro_location_t location);
```

Simulates whether a ritual would trigger at a specific time.

**Returns:** 1 if would trigger, 0 if not, -1 on error

#### spiro_get_astral_state()
```c
int spiro_get_astral_state(time_t timestamp, spiro_location_t location,
                           spiro_astral_state_t *state);
```

**Astral State Structure:**
```c
typedef struct {
    time_t timestamp;
    double moon_phase;          /* 0.0 - 1.0 */
    double moon_illumination;   /* 0.0 - 1.0 */
    int numerology_day;
    char planets_json[512];
} spiro_astral_state_t;
```

---

## Virtual Astral Filesystem

The `/astral` virtual filesystem exposes cosmic state as readable files.

### File Hierarchy

```
/astral/
├── moon_phase              # Current moon phase name
├── moon_illumination       # Percentage (0.00 - 1.00)
├── numerology_day          # Day of month (1-31)
├── planet_positions.json   # JSON array of planet data
├── triggers/               # Directory of active triggers
└── profiles/               # Directory of loaded profiles
```

### Reading Files

Use the standard file operations or `spiroctl`:

```bash
# Using spiroctl
./build/spiroctl astral read moon_phase

# In code
char buffer[256];
astral_fs_read("/astral/moon_phase", buffer, sizeof(buffer));
```

### File Formats

**moon_phase:**
```
Full Moon
```

**moon_illumination:**
```
0.98
```

**planet_positions.json:**
```json
{
  "timestamp": 1705334400,
  "planets": [
    {"name": "Sun", "sign": "Capricorn", "degree": 294.50},
    {"name": "Moon", "sign": "Pisces", "degree": 342.80},
    {"name": "Mercury", "sign": "Capricorn", "degree": 298.10}
  ]
}
```

---

## Trigger DSL

The Trigger Domain-Specific Language defines conditions for ritual awakening.

### Syntax

#### Moon Phase Conditions

```
moon == "New"
moon == "Waxing Crescent"
moon == "First Quarter"
moon == "Waxing Gibbous"
moon == "Full"
moon == "Waning Gibbous"
moon == "Last Quarter"
moon == "Waning Crescent"
```

#### Numerology Conditions

```
numerology_day == 7
numerology_day == 11
```

#### Planet Conditions

```
planet["Mars"].sign == "Scorpio"
planet["Venus"].sign == "Taurus"
```

#### Logical Operators

```
moon == "Full" && numerology_day == 7
moon == "Waxing Crescent" || moon == "Waxing Gibbous"
```

### Examples

**Simple Full Moon Trigger:**
```
moon == "Full"
```

**Complex Astrological Trigger:**
```
moon == "Full" && planet["Mars"].sign == "Scorpio"
```

**Numerology Trigger:**
```
numerology_day == 7 || numerology_day == 14 || numerology_day == 21
```

**Waxing Moon Growth:**
```
moon == "Waxing Crescent" || moon == "Waxing Gibbous"
```

### Evaluation

Triggers are evaluated on each cosmic tick (configurable interval). When all conditions are met, the associated ritual handler is awakened.

**Priority Calculation:**
```c
astral_priority = base_priority + moon_influence + planet_influence
```

Where:
- Full Moon: +10
- New Moon: +5
- Quarter Moons: +3
- Plus moon illumination factor (0-5)
- Plus numerology factor (special days: +3)

---

## Error Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| -1 | General error |
| -2 | Not initialized |
| -3 | Invalid parameter |
| -4 | Resource exhausted |
| -5 | Not found |

---

## Constants

### Process States

```c
#define PROCESS_STATE_BIRTH     0x01
#define PROCESS_STATE_EXECUTING 0x02
#define PROCESS_STATE_DEATH     0x03
#define PROCESS_STATE_DORMANT   0x04
```

### Execution Modes

```c
typedef enum {
    EXEC_MODE_NATIVE,    // Native process
    EXEC_MODE_SANDBOX,   // Sandboxed container
    EXEC_MODE_OBSERVER   // Lightweight observer
} execution_mode_t;
```

### Moon Phases

```c
typedef enum {
    MOON_NEW = 0,
    MOON_WAXING_CRESCENT,
    MOON_FIRST_QUARTER,
    MOON_WAXING_GIBBOUS,
    MOON_FULL,
    MOON_WANING_GIBBOUS,
    MOON_LAST_QUARTER,
    MOON_WANING_CRESCENT
} moon_phase_t;
```

---

*This API is subject to evolution as SpiritOS develops.*
