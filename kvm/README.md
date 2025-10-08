# SpiritOS KVM Testing

This directory contains scripts and resources for running SpiritOS in a KVM/QEMU virtual machine environment.

## Overview

SpiritOS can be executed in a virtualized environment using QEMU with optional KVM acceleration. This provides an isolated testing environment that closely mimics a real system boot process.

## Prerequisites

- QEMU (qemu-system-x86_64)
- KVM support (optional, for hardware acceleration)
- sudo access (for initial kernel setup)

### Installing QEMU

On Ubuntu/Debian:
```bash
sudo apt-get install qemu-system-x86 qemu-utils
```

On Fedora/RHEL:
```bash
sudo dnf install qemu-kvm qemu-system-x86
```

## Quick Start

The easiest way to test SpiritOS in KVM is using the Makefile targets:

```bash
# Build and run in KVM (all-in-one)
make kvm-test

# Or step-by-step:
make all              # Build SpiritOS
make kvm-image        # Create initramfs and setup kernel
./kvm/run-kvm.sh      # Launch in QEMU/KVM
```

## What Happens

When you run `make kvm-test` or `./kvm/run-kvm.sh`:

1. **Kernel Boot**: QEMU boots a Linux kernel with the SpiritOS initramfs
2. **Init Script**: The custom init script mounts filesystems and starts SpiritOS
3. **SpiritOS Execution**: The SpiritOS kernel initializes all components:
   - Soul Core (process management)
   - Ephemeris Provider (celestial calculations)
   - Destiny Engine (cosmic scheduler)
   - Astral FS (virtual filesystem)
4. **Demonstration**: 
   - SpiritOS runs for 10 seconds
   - Tests the spiroctl utility
   - Shows current celestial state
   - Lists registered triggers
5. **Shutdown**: Clean VM shutdown after completion

## Output

You should see output similar to:

```
╔═══════════════════════════════════════════════════════╗
║     SpiritOS - Booting in KVM Virtual Machine        ║
╚═══════════════════════════════════════════════════════╝

[INIT] Filesystems mounted
[INIT] Starting SpiritOS kernel...

╔═══════════════════════════════════════════════════════╗
║            SpiritOS - Spiritual Operating System      ║
║                  Soul Core Awakening                  ║
╚═══════════════════════════════════════════════════════╝

[KERNEL] Initializing kernel components...
[SOUL CORE] Awakening... The heart of SpiritOS begins to beat.
...
```

## Files

- **create-initramfs.sh**: Creates a minimal initramfs with SpiritOS binaries
- **setup-kernel.sh**: Copies the host kernel for QEMU use
- **run-kvm.sh**: Launches QEMU with appropriate parameters
- **vmlinuz**: Linux kernel image (generated)
- **initramfs.cpio.gz**: Initial RAM filesystem with SpiritOS (generated)

## Technical Details

### Initramfs Structure

The initramfs contains:
- `/init`: Custom init script that starts SpiritOS
- `/usr/bin/spiritos-kernel`: SpiritOS kernel binary
- `/usr/bin/spiroctl`: SpiritOS control utility
- `/bin/`, `/lib/`, `/lib64/`: Essential binaries and libraries
- `/proc`, `/sys`, `/dev`: Standard Linux filesystem mount points
- `/astral`: Mount point for SpiritOS virtual filesystem

### QEMU Parameters

```bash
qemu-system-x86_64 \
    -enable-kvm \           # Use KVM acceleration (if available)
    -nographic \            # Console-only mode
    -serial mon:stdio \     # Serial console to stdout
    -kernel vmlinuz \       # Linux kernel
    -initrd initramfs.cpio.gz \  # Initial ramdisk
    -append "console=ttyS0 quiet" \  # Kernel parameters
    -m 256M \               # 256MB RAM
    -smp 1                  # Single CPU core
```

## KVM Acceleration

If KVM is available and accessible, QEMU will use hardware acceleration for significantly better performance. If KVM is not available (e.g., on systems without virtualization support or when running in a nested VM), QEMU will fall back to software emulation.

To check KVM availability:
```bash
ls -la /dev/kvm
```

To add your user to the kvm group (for KVM access without sudo):
```bash
sudo usermod -a -G kvm $USER
# Log out and back in for changes to take effect
```

## Customization

### Modifying Init Behavior

Edit `create-initramfs.sh` and modify the init script section to change what happens when the VM boots.

### Changing VM Resources

Edit `run-kvm.sh` and modify the QEMU parameters:
- `-m 256M`: Change memory allocation
- `-smp 1`: Change CPU count
- Add `-display gtk`: Enable graphical window instead of console

### Using a Different Kernel

Replace `kvm/vmlinuz` with your preferred kernel image, or modify `setup-kernel.sh` to download a specific kernel version.

## Troubleshooting

### "Permission denied" when accessing kernel

Run `./kvm/setup-kernel.sh` again with sudo if needed.

### VM doesn't shutdown automatically

Press Ctrl-A, then X to exit QEMU manually.

### KVM not available

This is normal in some environments (e.g., nested virtualization). The system will automatically fall back to software emulation.

### "No such file or directory" errors in VM

Ensure all required libraries were copied. Check the initramfs creation output for errors.

## Clean Up

To remove generated KVM artifacts:

```bash
make kvm-clean
```

This removes:
- `kvm/initramfs/` (temporary directory)
- `kvm/initramfs.cpio.gz` (initramfs archive)
- `kvm/vmlinuz` (kernel copy)

## See Also

- [Main README](../README.md) - SpiritOS overview
- [Technical Design Document](../docs/TDD.md) - Architecture details
- [QEMU Documentation](https://www.qemu.org/docs/master/) - QEMU/KVM reference
