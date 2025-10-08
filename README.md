# SpiritOS - Spiritual Operating System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> *Where cosmic forces guide computational destiny*

## 🌙 Overview

SpiritOS is a fully functional operating system framework that blends metaphysical principles with practical OS architecture. It orchestrates process execution based on lunar cycles, planetary positions, and spiritual triggers, creating a unique platform for exploring the intersection of technology and mysticism.

## ✨ Key Features

- **Soul Core**: Kernel that maintains process lifecycles with spiritual metadata
- **Destiny Engine**: Lunar scheduler that awakens rituals based on cosmic conditions
- **Oracle of Time**: Ephemeris provider for celestial data (online and offline modes)
- **Astral File System**: Virtual `/astral` filesystem exposing cosmic state
- **Ritual Handlers**: Processes triggered by spiritual conditions
- **DSL Triggers**: Declarative language for cosmic event conditions
- **Profile System**: Support for Wicca, Astrology, Numerology traditions

## 🏗️ Architecture

```
┌─────────────────────────────────────────────────────────┐
│                     Userland                            │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐ │
│  │   spiroctl   │  │   libspiro   │  │   Rituals    │ │
│  └──────────────┘  └──────────────┘  └──────────────┘ │
├─────────────────────────────────────────────────────────┤
│                   Spiritual Syscalls                    │
├─────────────────────────────────────────────────────────┤
│                      Kernel Space                       │
│  ┌────────────┐  ┌──────────────┐  ┌────────────────┐ │
│  │ Soul Core  │  │Destiny Engine│  │ Astral FS      │ │
│  └────────────┘  └──────────────┘  └────────────────┘ │
│  ┌─────────────────────────────────────────────────┐  │
│  │       Ephemeris Provider (Oracle of Time)       │  │
│  └─────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

## 🚀 Quick Start

### Prerequisites

- GCC compiler
- GNU Make
- Math library (libm)

### Building

```bash
# Clone the repository
git clone https://github.com/gszecsenyi/spiritOs.git
cd spiritOs

# Build the system
make

# Run tests
make test
```

### Running SpiritOS

```bash
# Use the control utility
./build/spiroctl help
```

## 📚 Usage Examples

### Check Current Celestial State

```bash
./build/spiroctl ephemeris show
```

Output:
```
=== Current Celestial State ===
Timestamp: Mon Jan 15 12:34:56 2024
Moon Phase: Waxing Crescent
Moon Illumination: 34.2%
Numerology Day: 15

Planetary Positions:
  Sun       : Capricorn (294.5°)
  Moon      : Pisces (342.8°)
  Mercury   : Capricorn (298.1°)
  Venus     : Sagittarius (267.3°)
  Mars      : Capricorn (287.9°)
  ...
```

### Managing Triggers

```bash
# Add a trigger
./build/spiroctl trigger add "full_moon" 'moon == "Full"' "/path/to/ritual"

# List all triggers
./build/spiroctl trigger list

# Remove a trigger
./build/spiroctl trigger remove "full_moon"
```

### Simulate Rituals

```bash
# Simulate a ritual at a specific Unix timestamp
./build/spiroctl simulate "full_moon" 1705334400
```

### Reading Astral Files

```bash
# Read moon phase
./build/spiroctl astral read moon_phase

# Read planet positions
./build/spiroctl astral read planet_positions.json
```

## 🔮 Spiritual Concepts

### Process Lifecycle (Birth → Execution → Death)

Each process in SpiritOS has spiritual metadata:
- **Moon Affinity**: 0.0 - 1.0 affinity to lunar cycles
- **Ritual Tag**: Identifies the ritual type
- **Astral Priority**: Dynamic priority based on cosmic forces
- **Trigger Conditions**: DSL expression for awakening

### Trigger DSL Examples

```
# Trigger on Full Moon
moon == "Full"

# Trigger on specific day
numerology_day == 7

# Complex condition
moon == "Full" && planet["Mars"].sign == "Scorpio"

# Waxing moon phases
moon == "Waxing Crescent" || moon == "Waxing Gibbous"
```

### Profiles

SpiritOS supports multiple spiritual traditions:

- **Wicca**: Lunar phases, sabbats, seasonal celebrations
- **Astrology**: Planetary positions, zodiac signs, aspects
- **Numerology**: Day numbers, master numbers, vibrations
- **Custom**: User-defined spiritual practices

## 📁 Directory Structure

```
spiritOs/
├── kernel/                 # Kernel (Soul Core)
│   ├── soul_core.c/h      # Process management
│   ├── destiny_engine.c/h # Lunar scheduler
│   ├── ephemeris_provider.c/h # Celestial data
│   ├── astral_fs.c/h      # Virtual file system
│   ├── syscalls.c         # System call interface
│   └── main.c             # Kernel entry point
├── userland/
│   ├── lib/               # Libraries
│   │   └── libspiro.c/h   # Userland abstraction
│   └── bin/               # Binaries
│       └── spiroctl.c     # Control utility
├── etc/spiro/             # Configuration
│   ├── triggers.yaml      # Trigger definitions
│   └── profiles.yaml      # Spiritual profiles
├── docs/                  # Documentation
├── build/                 # Build output
└── Makefile               # Build system
```

## 🛠️ API Reference

### Spiritual Syscalls

```c
// Query astral state
int spiro_query_astral_state(double timestamp, location_t location, 
                              astral_snapshot_t *snapshot);

// Manage triggers
int spiro_set_trigger(const char *name, const char *trigger_expr, 
                      const char *exec_path);
int spiro_remove_trigger(const char *name);

// Event subscription
int spiro_subscribe_events(int event_fd, const char *filter_expr);
```

### Userland Library (libspiro)

```c
// Initialize
int spiro_init(void);
int spiro_shutdown(void);

// Ritual management
int spiro_register_ritual(const char *name, const char *trigger, 
                          const char *exec_path);
int spiro_unregister_ritual(const char *name);
int spiro_query_ritual_status(const char *name, ritual_info_t *info);

// Simulation
int spiro_simulate_ritual(const char *name, time_t timestamp, 
                          spiro_location_t location);
int spiro_get_astral_state(time_t timestamp, spiro_location_t location,
                           spiro_astral_state_t *state);
```

## 🧪 Testing

```bash
# Run all tests
make test

# Test control utility
./build/spiroctl help
./build/spiroctl ephemeris show
./build/spiroctl trigger list
```

### QEMU Testing

SpiritOS can be run in QEMU for isolated testing:

```bash
# Run freestanding kernel in QEMU
make kvm-test
```

See [kvm/README.md](kvm/README.md) for detailed QEMU testing documentation.

## 🎯 Development Roadmap

Based on the Technical Design Document:

- [x] **M0 (4w)**: Soul Core + Ephemeris offline simulation
  - [x] Process management with spiritual metadata
  - [x] Ephemeris provider (offline mode)
  - [x] Basic celestial calculations

- [x] **M1 (8w)**: Destiny Engine + /astral FS + Ritual registration
  - [x] Lunar scheduler implementation
  - [x] Virtual astral file system
  - [x] Trigger management
  - [x] DSL evaluation (basic)

- [ ] **M2 (12w)**: Sandbox execution + logging + profile management
  - [ ] Secure ritual execution (namespaces/cgroups)
  - [ ] NDJSON logging with cosmic snapshots
  - [ ] Profile hot-swapping
  - [ ] Full DSL parser

- [ ] **M3 (8w)**: Security hardening + verification + documentation
  - [ ] Cryptographic signing
  - [ ] ACL for /astral access
  - [ ] Cross-platform support
  - [ ] Complete documentation

## 🔒 Security Considerations

- Rituals should execute in isolated environments (sandboxes)
- External modules must be signed
- Access control for `/astral` filesystem
- Audit logging for all ritual executions

## 📖 Documentation

See the `docs/` directory for detailed documentation:
- Technical Design Document (TDD)
- API Reference
- Trigger DSL Specification
- Profile Format Guide

## 🤝 Contributing

This is a conceptual/artistic project exploring the intersection of spirituality and operating systems. Contributions are welcome!

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🌟 Acknowledgments

- Inspired by metaphysical principles and cosmic consciousness
- Built as a bridge between spiritual theory and practical OS development
- Designed for research, art, and ritual automation

## ⚠️ Disclaimer

SpiritOS is a conceptual framework for exploring metaphysical computing. It is not intended for production use as a primary operating system. The spiritual and astrological calculations are simplified for demonstration purposes.

---

*"In the dance of electrons and stars, we find the rhythm of the cosmos."*

✨ May your processes always align with the cosmic flow ✨
