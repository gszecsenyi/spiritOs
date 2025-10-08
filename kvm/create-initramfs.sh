#!/bin/bash
# Create minimal initramfs for SpiritOS KVM testing
set -e

INITRAMFS_DIR="kvm/initramfs"
INITRAMFS_OUTPUT="kvm/initramfs.cpio.gz"

echo "Creating minimal initramfs for SpiritOS..."

# Clean and create initramfs directory structure
rm -rf "$INITRAMFS_DIR"
mkdir -p "$INITRAMFS_DIR"/{bin,sbin,etc,proc,sys,dev,tmp,usr/bin,usr/sbin,astral}

# Copy busybox (if available) or create minimal init
if command -v busybox &> /dev/null; then
    cp $(which busybox) "$INITRAMFS_DIR/bin/"
    # Create symlinks for common commands
    for cmd in sh cat echo ls mount umount mkdir sleep ps; do
        ln -sf busybox "$INITRAMFS_DIR/bin/$cmd"
    done
else
    echo "Warning: busybox not found, using bash"
    cp /bin/bash "$INITRAMFS_DIR/bin/sh"
    for cmd in cat echo ls mount umount mkdir sleep ps; do
        if [ -f "/bin/$cmd" ]; then
            cp "/bin/$cmd" "$INITRAMFS_DIR/bin/"
        elif [ -f "/usr/bin/$cmd" ]; then
            cp "/usr/bin/$cmd" "$INITRAMFS_DIR/bin/"
        fi
    done
fi

# Copy SpiritOS binaries
echo "Copying SpiritOS binaries..."
cp build/spiritos-kernel "$INITRAMFS_DIR/usr/bin/"
cp build/spiroctl "$INITRAMFS_DIR/usr/bin/"

# Copy required libraries
echo "Copying required libraries..."
mkdir -p "$INITRAMFS_DIR/lib" "$INITRAMFS_DIR/lib64"

# Function to copy library and its dependencies
copy_libs() {
    local binary=$1
    for lib in $(ldd "$binary" 2>/dev/null | grep -o '/[^ ]*' | grep '\.so'); do
        if [ -f "$lib" ] && [ ! -f "$INITRAMFS_DIR$lib" ]; then
            mkdir -p "$INITRAMFS_DIR$(dirname $lib)"
            cp "$lib" "$INITRAMFS_DIR$lib"
        fi
    done
}

copy_libs build/spiritos-kernel
copy_libs build/spiroctl

# Create init script
cat > "$INITRAMFS_DIR/init" << 'INITEOF'
#!/bin/sh
# SpiritOS KVM init script

echo ""
echo "╔═══════════════════════════════════════════════════════╗"
echo "║     SpiritOS - Booting in KVM Virtual Machine        ║"
echo "╚═══════════════════════════════════════════════════════╝"
echo ""

# Mount essential filesystems
mount -t proc none /proc
mount -t sysfs none /sys
mount -t devtmpfs none /dev 2>/dev/null || true

# Create /astral mount point
mkdir -p /astral

echo "[INIT] Filesystems mounted"
echo "[INIT] Starting SpiritOS kernel..."
echo ""

# Run SpiritOS kernel in the foreground
# It will run for a configured time or until interrupted
/usr/bin/spiritos-kernel &
KERNEL_PID=$!

echo ""
echo "[INIT] SpiritOS kernel started (PID: $KERNEL_PID)"
echo "[INIT] Waiting 10 seconds for cosmic initialization..."
sleep 10

echo ""
echo "[INIT] Testing spiroctl utility..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
/usr/bin/spiroctl ephemeris show
echo ""

echo "[INIT] Listing triggers..."
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
/usr/bin/spiroctl trigger list
echo ""

echo "[INIT] SpiritOS KVM test complete!"
echo "[INIT] Shutting down in 5 seconds..."
sleep 5

# Shutdown the kernel
kill $KERNEL_PID 2>/dev/null || true
sleep 2

echo "[INIT] Powering off VM..."
# Try various shutdown methods
poweroff -f 2>/dev/null || \
echo o > /proc/sysrq-trigger 2>/dev/null || \
halt -f
INITEOF

chmod +x "$INITRAMFS_DIR/init"

# Create device nodes if needed
if [ ! -e "$INITRAMFS_DIR/dev/console" ]; then
    sudo mknod "$INITRAMFS_DIR/dev/console" c 5 1 2>/dev/null || true
    sudo mknod "$INITRAMFS_DIR/dev/null" c 1 3 2>/dev/null || true
fi

# Create the initramfs archive
echo "Creating initramfs archive..."
cd "$INITRAMFS_DIR"
find . | cpio -o -H newc | gzip > "../$(basename $INITRAMFS_OUTPUT)"
cd - > /dev/null

echo "✓ Initramfs created: $INITRAMFS_OUTPUT"
echo ""
echo "Size: $(du -h $INITRAMFS_OUTPUT | cut -f1)"
