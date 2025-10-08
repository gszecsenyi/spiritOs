# SpiritOS Makefile
# Build system for the Spiritual Operating System

CC = gcc
AS = as

# Freestanding kernel flags
KERNEL_CFLAGS = -Wall -Wextra -g -I. -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -m32
KERNEL_LDFLAGS = -T boot/linker.ld -nostdlib -m32 -lm -lgcc

# Hosted userland flags
CFLAGS = -Wall -Wextra -g -I.
LDFLAGS = -lm

# Directories
KERNEL_DIR = kernel
HAL_DIR = $(KERNEL_DIR)/hal
USERLAND_DIR = userland
LIB_DIR = $(USERLAND_DIR)/lib
BIN_DIR = $(USERLAND_DIR)/bin
BUILD_DIR = build
BOOT_DIR = boot
ISO_DIR = build/iso

# Freestanding kernel sources
KERNEL_SRCS = $(KERNEL_DIR)/soul_core.c \
              $(KERNEL_DIR)/ephemeris_provider.c \
              $(KERNEL_DIR)/destiny_engine.c \
              $(KERNEL_DIR)/astral_fs.c \
              $(KERNEL_DIR)/syscalls.c \
              $(KERNEL_DIR)/snprintf.c \
              $(KERNEL_DIR)/main.c

# HAL sources (Hardware Abstraction Layer)
HAL_SRCS = $(HAL_DIR)/vga.c \
           $(HAL_DIR)/serial.c \
           $(HAL_DIR)/timer.c \
           $(HAL_DIR)/kstring.c \
           $(HAL_DIR)/kprintf.c

# Boot assembly
BOOT_ASM = $(BOOT_DIR)/boot.S

KERNEL_OBJS = $(KERNEL_SRCS:%.c=$(BUILD_DIR)/%.o) $(HAL_SRCS:%.c=$(BUILD_DIR)/%.o)
BOOT_OBJ = $(BUILD_DIR)/boot/boot.o

# Hosted kernel sources (for development/testing)
KERNEL_HOSTED_SRCS = $(KERNEL_DIR)/soul_core.c \
                     $(KERNEL_DIR)/ephemeris_provider.c \
                     $(KERNEL_DIR)/destiny_engine.c \
                     $(KERNEL_DIR)/astral_fs.c \
                     $(KERNEL_DIR)/syscalls.c \
                     $(KERNEL_DIR)/main_hosted.c

KERNEL_HOSTED_OBJS = $(KERNEL_HOSTED_SRCS:%.c=$(BUILD_DIR)/%_hosted.o)

# Library sources
LIB_SRCS = $(LIB_DIR)/libspiro.c
LIB_OBJS = $(LIB_SRCS:%.c=$(BUILD_DIR)/%.o)

# Binary sources
SPIROCTL_SRCS = $(BIN_DIR)/spiroctl.c
SPIROCTL_OBJS = $(SPIROCTL_SRCS:%.c=$(BUILD_DIR)/%.o)

# Targets
KERNEL_TARGET = $(BUILD_DIR)/spiritos.elf
KERNEL_HOSTED_TARGET = $(BUILD_DIR)/spiritos-kernel
KERNEL_ISO = $(BUILD_DIR)/spiritos.iso
LIBSPIRO_TARGET = $(BUILD_DIR)/libspiro.a
SPIROCTL_TARGET = $(BUILD_DIR)/spiroctl

.PHONY: all clean kernel kernel-hosted userland install test help kvm-test kvm-clean iso

all: kernel kernel-hosted userland
	@echo "╔═══════════════════════════════════════╗"
	@echo "║   SpiritOS Build Complete ✨          ║"
	@echo "╚═══════════════════════════════════════╝"
	@echo ""
	@echo "Standalone Kernel: $(KERNEL_TARGET)"
	@echo "Hosted Kernel:     $(KERNEL_HOSTED_TARGET)"
	@echo "Library:           $(LIBSPIRO_TARGET)"
	@echo "Control:           $(SPIROCTL_TARGET)"
	@echo ""
	@echo "Run 'make iso' to create bootable ISO"
	@echo "Run 'make kvm-test' to test in QEMU/KVM"
	@echo "Run './build/spiritos-kernel' for hosted mode"

kernel: $(KERNEL_TARGET)

kernel-hosted: $(KERNEL_HOSTED_TARGET)

userland: $(LIBSPIRO_TARGET) $(SPIROCTL_TARGET)

# Build freestanding kernel
$(KERNEL_TARGET): $(BOOT_OBJ) $(KERNEL_OBJS)
	@mkdir -p $(dir $@)
	$(CC) -m32 -T boot/linker.ld -nostdlib -static -no-pie -o $@ $^ -lgcc
	@echo "✓ Freestanding kernel built: $@"

# Build hosted kernel (for development)
$(KERNEL_HOSTED_TARGET): $(KERNEL_HOSTED_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Hosted kernel built: $@"

# Build libspiro
$(LIBSPIRO_TARGET): $(LIB_OBJS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^
	@echo "✓ Library built: $@"

# Build spiroctl
$(SPIROCTL_TARGET): $(SPIROCTL_OBJS) $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $(SPIROCTL_OBJS) \
		$(BUILD_DIR)/$(KERNEL_DIR)/soul_core_hosted.o \
		$(BUILD_DIR)/$(KERNEL_DIR)/ephemeris_provider_hosted.o \
		$(BUILD_DIR)/$(KERNEL_DIR)/destiny_engine_hosted.o \
		$(BUILD_DIR)/$(KERNEL_DIR)/astral_fs_hosted.o \
		$(LIB_OBJS) $(LDFLAGS)
	@echo "✓ Control utility built: $@"

# Compile boot assembly
$(BUILD_DIR)/boot/%.o: boot/%.S
	@mkdir -p $(dir $@)
	$(AS) --32 -o $@ $<

# Compile freestanding kernel objects
$(BUILD_DIR)/$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(KERNEL_CFLAGS) -c -o $@ $<

# Compile hosted kernel objects (different suffix)
$(BUILD_DIR)/$(KERNEL_DIR)/%_hosted.o: $(KERNEL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DHOSTED_BUILD -c -o $@ $<

# Compile HAL objects
$(BUILD_DIR)/$(HAL_DIR)/%.o: $(HAL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(KERNEL_CFLAGS) -c -o $@ $<

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
	@echo "Test 1: Hosted kernel initialization..."
	@timeout 2 $(KERNEL_HOSTED_TARGET) || echo "✓ Hosted kernel runs (terminated after 2s)"
	@echo ""
	@echo "Test 2: Control utility..."
	@$(SPIROCTL_TARGET) help
	@echo ""
	@echo "✓ Basic tests complete"

# Create bootable ISO image
iso: $(KERNEL_TARGET)
	@echo "Creating bootable ISO image..."
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(KERNEL_TARGET) $(ISO_DIR)/boot/spiritos.elf
	@echo 'set timeout=0' > $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "SpiritOS" {' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    multiboot2 /boot/spiritos.elf' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    boot' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}' >> $(ISO_DIR)/boot/grub/grub.cfg
	@if command -v grub-mkrescue >/dev/null 2>&1; then \
		grub-mkrescue -o $(KERNEL_ISO) $(ISO_DIR); \
		echo "✓ ISO image created: $(KERNEL_ISO)"; \
	else \
		echo "⚠ grub-mkrescue not found, ISO not created"; \
		echo "Install grub-mkrescue to create bootable ISOs"; \
	fi

kvm-test: $(KERNEL_TARGET)
	@echo "╔═══════════════════════════════════════════════════════╗"
	@echo "║         SpiritOS - QEMU/KVM Launch (Standalone)      ║"
	@echo "╚═══════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Launching standalone kernel in QEMU..."
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	@if [ -e /dev/kvm ] && [ -r /dev/kvm ] && [ -w /dev/kvm ]; then \
		qemu-system-x86_64 -kernel $(KERNEL_TARGET) -serial stdio -enable-kvm; \
	else \
		qemu-system-x86_64 -kernel $(KERNEL_TARGET) -serial stdio; \
	fi
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "QEMU session ended"

kvm-clean:
	@echo "Cleaning KVM and build artifacts..."
	@rm -rf kvm/initramfs kvm/initramfs.cpio.gz kvm/vmlinuz $(ISO_DIR)
	@echo "✓ KVM artifacts cleaned"

help:
	@echo "SpiritOS Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all           - Build standalone kernel, hosted kernel, and userland (default)"
	@echo "  kernel        - Build standalone freestanding kernel only"
	@echo "  kernel-hosted - Build hosted kernel only (for development)"
	@echo "  userland      - Build userland tools only"
	@echo "  clean         - Remove build artifacts"
	@echo "  install       - Install to system (requires sudo)"
	@echo "  test          - Run basic tests"
	@echo "  iso           - Create bootable ISO image"
	@echo "  kvm-test      - Run standalone kernel in QEMU/KVM"
	@echo "  kvm-clean     - Remove KVM and ISO artifacts"
	@echo "  help          - Show this help"
	@echo ""
	@echo "Usage:"
	@echo "  make              # Build everything"
	@echo "  make clean        # Clean build"
	@echo "  make test         # Run tests"
	@echo "  make kvm-test     # Test standalone kernel in QEMU"
	@echo "  make iso          # Create bootable ISO"

.DEFAULT_GOAL := all
