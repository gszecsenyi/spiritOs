#!/bin/bash
# Download a minimal kernel for KVM testing
set -e

KERNEL_DIR="kvm"
KERNEL_URL="https://github.com/buildroot/buildroot/raw/2024.02.x/board/qemu/x86_64/linux.config"

echo "Setting up kernel for KVM testing..."

# For simplicity, we'll use the host kernel with sudo
# or build a minimal kernel if needed

# Check if we can use the host kernel with sudo
HOST_KERNEL="/boot/vmlinuz-$(uname -r)"

if [ -f "$HOST_KERNEL" ]; then
    echo "Found host kernel: $HOST_KERNEL"
    echo "Copying to kvm directory (this requires read access)..."
    
    # Try to copy kernel (may need sudo)
    if sudo cp "$HOST_KERNEL" "$KERNEL_DIR/vmlinuz" 2>/dev/null; then
        sudo chmod 644 "$KERNEL_DIR/vmlinuz"
        echo "✓ Kernel copied to $KERNEL_DIR/vmlinuz"
    else
        echo "Warning: Could not copy kernel. Will try to use host kernel directly."
        echo "Note: You may need to run with sudo"
    fi
else
    echo "Host kernel not found at $HOST_KERNEL"
fi

echo "Kernel setup complete"
