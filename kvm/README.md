# SpiritOS QEMU Testing

**Note:** The scripts in this directory (create-initramfs.sh, run-kvm.sh, setup-kernel.sh) are now obsolete. They were used for running a hosted kernel in a VM. 

Use `make kvm-test` from the root directory to test the freestanding kernel directly in QEMU.

## Testing the Freestanding Kernel

The freestanding kernel can be executed directly in QEMU using the Makefile:

```bash
# From the root directory
make kvm-test
```

This will boot the standalone `spiritos.elf` kernel using QEMU's multiboot support.

## Prerequisites

- QEMU (qemu-system-x86_64)
- KVM support (optional, for hardware acceleration)

### Installing QEMU

On Ubuntu/Debian:
```bash
sudo apt-get install qemu-system-x86 qemu-utils
```

On Fedora/RHEL:
```bash
sudo dnf install qemu-kvm qemu-system-x86
```

## What Happens

When you run `make kvm-test`:

1. **Direct Boot**: QEMU boots the SpiritOS freestanding kernel directly using multiboot
2. **Hardware Initialization**: The kernel initializes VGA, serial port, and timer
3. **SpiritOS Execution**: The kernel initializes all components:
   - Soul Core (process management)
   - Ephemeris Provider (celestial calculations)
   - Destiny Engine (cosmic scheduler)
   - Astral FS (virtual filesystem)
4. **Cosmic Tick Loop**: The kernel runs for 60 cosmic ticks
5. **Completion**: Kernel completes its demonstration and halts

## Output

You should see output in the QEMU console similar to:

```
╔═══════════════════════════════════════════════════════╗
║            SpiritOS - Spiritual Operating System      ║
║              Freestanding Kernel Mode                 ║
╚═══════════════════════════════════════════════════════╝

[VGA] Display initialized (80x25)
[SERIAL] COM1 initialized
[KERNEL] Initializing kernel components...
[SOUL CORE] Awakening... The heart of SpiritOS begins to beat.
...
```

## Technical Details

The freestanding kernel:
- Boots directly via multiboot protocol (no Linux host)
- Uses custom VGA driver for console output
- Uses serial port (COM1) for debugging output
- Implements its own timer and string functions
- Runs completely in kernel space (no userland processes)

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

## Creating a Bootable ISO

For testing on real hardware or other virtual machines, you can create a bootable ISO:

```bash
make iso
```

This creates `build/spiritos.iso` which can be burned to a CD/DVD or used with any ISO-capable VM software.

## Troubleshooting

### Need to exit the VM

Press Ctrl-A, then X to exit QEMU manually. When using the hosted kernel approach (via `run-kvm.sh`), you can also type `exit` at the shell prompt.

### KVM not available

This is normal in some environments (e.g., nested virtualization). The system will automatically fall back to software emulation.

## Clean Up

To remove generated build artifacts:

```bash
make clean
```

## See Also

- [Main README](../README.md) - SpiritOS overview
- [Technical Design Document](../docs/TDD.md) - Architecture details
- [Standalone Kernel Documentation](../docs/STANDALONE_KERNEL.md) - Freestanding kernel details
- [QEMU Documentation](https://www.qemu.org/docs/master/) - QEMU/KVM reference

