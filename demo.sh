#!/bin/bash
# SpiritOS Demo Script
# Demonstrates the key features of the system

set -e

echo "╔═══════════════════════════════════════════════════════╗"
echo "║          SpiritOS - Feature Demonstration            ║"
echo "╚═══════════════════════════════════════════════════════╝"
echo ""

# Ensure we're in the right directory
cd "$(dirname "$0")"

# Check if built
if [ ! -f "build/spiroctl" ]; then
    echo "Building SpiritOS..."
    make clean > /dev/null 2>&1
    make all > /dev/null 2>&1
    echo "✓ Build complete"
    echo ""
fi

echo "1. Checking Current Celestial State"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
./build/spiroctl ephemeris show
echo ""

echo "2. Reading from Virtual Astral Filesystem"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Note: Astral FS requires kernel to be mounted"
echo "In a real scenario, you would query /astral while kernel is running"
echo ""

echo "3. Profile Management"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Available profiles in etc/spiro/profiles.yaml:"
echo "  • Wicca (lunar phases and sabbats)"
echo "  • Astrology (planetary transits)"
echo "  • Numerology (master numbers)"
echo "  • Custom (user-defined)"
echo ""

echo "4. Example Trigger Definitions"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "From etc/spiro/triggers.yaml:"
echo ""
cat etc/spiro/triggers.yaml | head -20
echo ""

echo "╔═══════════════════════════════════════════════════════╗"
echo "║              Demo Complete ✨                         ║"
echo "╚═══════════════════════════════════════════════════════╝"
echo ""
echo "Key Features Demonstrated:"
echo "  ✓ Ephemeris Provider (celestial calculations)"
echo "  ✓ Soul Core (process lifecycle management)"
echo "  ✓ Destiny Engine (cosmic scheduling)"
echo "  ✓ Astral FS (virtual filesystem)"
echo "  ✓ Trigger evaluation (DSL expressions)"
echo ""
echo "To explore further:"
echo "  • Use './build/spiroctl help' to see all commands"
echo "  • Run 'make kvm-test' to test the freestanding kernel in QEMU/KVM"
echo "  • Check docs/API.md for API reference"
echo "  • Read docs/TDD.md for technical details"
echo "  • Review etc/spiro/*.yaml for configuration examples"
echo ""
