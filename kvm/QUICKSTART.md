# SpiritOS KVM Quick Start Guide

This is a quick reference for testing SpiritOS in a KVM/QEMU virtual machine.

## One-Command Test

```bash
make kvm-test
```

This single command will:
1. Build SpiritOS (if needed)
2. Setup the kernel for KVM
3. Create the initramfs with SpiritOS
4. Launch QEMU and run SpiritOS
5. Execute automated tests
6. Shutdown cleanly

## Expected Output

You should see:
- SeaBIOS boot messages
- Custom SpiritOS boot banner
- Kernel initialization logs
- Ephemeris provider awakening
- Destiny Engine activating
- Astral FS mounting
- Cosmic tick loop executing
- Spiroctl utility tests
- Clean shutdown

## What's Happening Inside the VM

1. **Boot (0-2s)**: Linux kernel boots with SpiritOS initramfs
2. **Init (2-3s)**: Custom init script mounts filesystems and starts SpiritOS
3. **SpiritOS (3-13s)**: Kernel runs, components initialize, cosmic ticks execute
4. **Tests (13-18s)**: Spiroctl tests celestial state and triggers
5. **Shutdown (18-20s)**: Clean kernel shutdown and VM poweroff

## Success Indicators

Look for these messages to confirm success:

✓ "SpiritOS is now alive ✨"
✓ "Trigger registered: 'full_moon_ritual'"
✓ "=== Current Celestial State ==="
✓ "SpiritOS KVM test complete!"
✓ "reboot: Power down"

## Troubleshooting

**Problem**: "Permission denied" on kernel
**Solution**: Run `./kvm/setup-kernel.sh` again

**Problem**: VM doesn't shutdown
**Solution**: Press Ctrl-A, then X to force quit QEMU

**Problem**: No KVM acceleration
**Solution**: This is normal in some environments (GitHub Actions, nested VMs). It will use software emulation automatically.

## Manual Steps (Optional)

If you prefer to run steps individually:

```bash
# 1. Build SpiritOS
make all

# 2. Setup kernel
./kvm/setup-kernel.sh

# 3. Create initramfs
./kvm/create-initramfs.sh

# 4. Launch VM
./kvm/run-kvm.sh
```

## Cleanup

```bash
make kvm-clean
```

Removes all generated KVM artifacts (vmlinuz, initramfs, etc.)

## More Information

See [kvm/README.md](README.md) for detailed documentation.
