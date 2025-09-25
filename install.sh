#!/usr/bin/env bash

set -e  # Exit on any error

echo "Detecting Linux distribution..."

# Read distro info
if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
else
    echo "Cannot detect Linux distribution."
    exit 1
fi

echo "Detected: $DISTRO"

case "$DISTRO" in
    ubuntu|debian)
        echo "Updating package lists..."
        sudo apt-get update

        echo "Installing build-essential..."
        sudo apt-get install -y build-essential

        echo "Installing GLFW (development files, optional)..."
        sudo apt-get install -y libglfw3-dev

        echo "Installing GLFW runtime (.so files)..."
        sudo apt-get install -y libglfw3
        ;;

    fedora|rhel|centos)
        echo "Updating packages..."
        sudo dnf update -y

        echo "Installing development tools..."
        sudo dnf groupinstall -y "Development Tools"

        echo "Installing GLFW runtime..."
        sudo dnf install -y glfw

        echo "Installing GLFW development files..."
        sudo dnf install -y glfw-devel
        ;;

    *)
        echo "Unsupported Linux distribution: $DISTRO"
        exit 1
        ;;
esac

echo "Installation complete!"
