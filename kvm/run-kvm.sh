#!/bin/bash
# Launch SpiritOS in KVM/QEMU
set -e

KERNEL_PATH="kvm/vmlinuz"
INITRAMFS_PATH="kvm/initramfs.cpio.gz"

echo "╔═══════════════════════════════════════════════════════╗"
echo "║         SpiritOS - KVM/QEMU Launch Script            ║"
echo "╚═══════════════════════════════════════════════════════╝"
echo ""

# Check if kernel image exists
if [ ! -f "$KERNEL_PATH" ]; then
    echo "Error: Kernel not found at $KERNEL_PATH"
    echo "Please run './kvm/setup-kernel.sh' first"
    exit 1
fi

# Check if initramfs exists
if [ ! -f "$INITRAMFS_PATH" ]; then
    echo "Error: Initramfs not found at $INITRAMFS_PATH"
    echo "Please run './kvm/create-initramfs.sh' first"
    exit 1
fi

echo "Kernel:    $KERNEL_PATH"
echo "Initramfs: $INITRAMFS_PATH"
echo ""
echo "Starting KVM virtual machine..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""

# Check if KVM is available and accessible
KVM_OPTS=""
if [ -e /dev/kvm ] && [ -r /dev/kvm ] && [ -w /dev/kvm ]; then
    KVM_OPTS="-enable-kvm"
    echo "Using KVM acceleration"
else
    echo "KVM not available or not accessible, using software emulation"
    echo "(This will be slower but still functional)"
fi
echo ""

# Launch QEMU with KVM acceleration (if available)
# -enable-kvm: Use KVM hardware acceleration (if available)
# -nographic: Run without graphical display (console only)
# -serial mon:stdio: Redirect serial console to stdout
# -kernel: Linux kernel to boot
# -initrd: Initial ramdisk with SpiritOS
# -append: Kernel command line parameters
# -m: Memory allocation (256MB should be enough)
# -smp: Number of CPUs

qemu-system-x86_64 \
    $KVM_OPTS \
    -nographic \
    -serial mon:stdio \
    -kernel "$KERNEL_PATH" \
    -initrd "$INITRAMFS_PATH" \
    -append "console=ttyS0 quiet" \
    -m 256M \
    -smp 1 \
    2>&1 || true

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "KVM session ended"
