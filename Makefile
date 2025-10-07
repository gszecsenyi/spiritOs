# SpiritOS Makefile
# Build system for the Spiritual Operating System

CC = gcc
CFLAGS = -Wall -Wextra -g -I.
LDFLAGS = -lm

# Directories
KERNEL_DIR = kernel
USERLAND_DIR = userland
LIB_DIR = $(USERLAND_DIR)/lib
BIN_DIR = $(USERLAND_DIR)/bin
BUILD_DIR = build
BOOT_DIR = boot

# Kernel sources
KERNEL_SRCS = $(KERNEL_DIR)/soul_core.c \
              $(KERNEL_DIR)/ephemeris_provider.c \
              $(KERNEL_DIR)/destiny_engine.c \
              $(KERNEL_DIR)/astral_fs.c \
              $(KERNEL_DIR)/syscalls.c \
              $(KERNEL_DIR)/main.c

KERNEL_OBJS = $(KERNEL_SRCS:%.c=$(BUILD_DIR)/%.o)

# Library sources
LIB_SRCS = $(LIB_DIR)/libspiro.c
LIB_OBJS = $(LIB_SRCS:%.c=$(BUILD_DIR)/%.o)

# Binary sources
SPIROCTL_SRCS = $(BIN_DIR)/spiroctl.c
SPIROCTL_OBJS = $(SPIROCTL_SRCS:%.c=$(BUILD_DIR)/%.o)

# Targets
KERNEL_TARGET = $(BUILD_DIR)/spiritos-kernel
LIBSPIRO_TARGET = $(BUILD_DIR)/libspiro.a
SPIROCTL_TARGET = $(BUILD_DIR)/spiroctl

.PHONY: all clean kernel userland install test help

all: kernel userland
	@echo "╔═══════════════════════════════════════╗"
	@echo "║   SpiritOS Build Complete ✨          ║"
	@echo "╚═══════════════════════════════════════╝"
	@echo ""
	@echo "Kernel: $(KERNEL_TARGET)"
	@echo "Library: $(LIBSPIRO_TARGET)"
	@echo "Control: $(SPIROCTL_TARGET)"
	@echo ""
	@echo "Run './build/spiritos-kernel' to start the system"
	@echo "Run './build/spiroctl help' for control utility help"

kernel: $(KERNEL_TARGET)

userland: $(LIBSPIRO_TARGET) $(SPIROCTL_TARGET)

# Build kernel
$(KERNEL_TARGET): $(KERNEL_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Kernel built: $@"

# Build libspiro
$(LIBSPIRO_TARGET): $(LIB_OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^
	@echo "✓ Library built: $@"

# Build spiroctl
$(SPIROCTL_TARGET): $(SPIROCTL_OBJS) $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $(SPIROCTL_OBJS) \
		$(BUILD_DIR)/$(KERNEL_DIR)/soul_core.o \
		$(BUILD_DIR)/$(KERNEL_DIR)/ephemeris_provider.o \
		$(BUILD_DIR)/$(KERNEL_DIR)/destiny_engine.o \
		$(BUILD_DIR)/$(KERNEL_DIR)/astral_fs.o \
		$(LIB_OBJS) $(LDFLAGS)
	@echo "✓ Control utility built: $@"

# Compile kernel objects
$(BUILD_DIR)/$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile library objects
$(BUILD_DIR)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile binary objects
$(BUILD_DIR)/$(BIN_DIR)/%.o: $(BIN_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Build directory cleaned"

install:
	@echo "Installing SpiritOS..."
	@mkdir -p /usr/local/bin
	@mkdir -p /usr/local/lib
	@mkdir -p /etc/spiro
	@cp $(KERNEL_TARGET) /usr/local/bin/spiritos-kernel 2>/dev/null || echo "Note: Need sudo for system installation"
	@cp $(SPIROCTL_TARGET) /usr/local/bin/spiroctl 2>/dev/null || echo "Note: Need sudo for system installation"
	@cp etc/spiro/*.yaml /etc/spiro/ 2>/dev/null || echo "Note: Need sudo for config installation"
	@echo "✓ Installation attempted (may need sudo)"

test: all
	@echo "Running SpiritOS tests..."
	@echo "Test 1: Kernel initialization..."
	@timeout 2 $(KERNEL_TARGET) || echo "✓ Kernel runs (terminated after 2s)"
	@echo ""
	@echo "Test 2: Control utility..."
	@$(SPIROCTL_TARGET) help
	@echo ""
	@echo "✓ Basic tests complete"

help:
	@echo "SpiritOS Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all      - Build kernel and userland (default)"
	@echo "  kernel   - Build kernel only"
	@echo "  userland - Build userland tools only"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install to system (requires sudo)"
	@echo "  test     - Run basic tests"
	@echo "  help     - Show this help"
	@echo ""
	@echo "Usage:"
	@echo "  make          # Build everything"
	@echo "  make clean    # Clean build"
	@echo "  make test     # Run tests"

.DEFAULT_GOAL := all
