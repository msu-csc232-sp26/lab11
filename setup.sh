#!/bin/bash

# This script updates, upgrades, and installs development packages on Ubuntu 24.04 without user interaction.

# Check if the script is being run as root.
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root."
   exit 1
fi

# Update package lists.
apt update -y && export DEBIAN_FRONTEND=noninteractive
if [ $? -ne 0 ]; then
    echo "Error updating package lists. Exiting."
    exit 1
fi

# Upgrade installed packages.
apt upgrade -y
if [ $? -ne 0 ]; then
    echo "Error upgrading packages. Exiting."
    exit 1
fi

# Install the specified packages without user interaction.
# The -y flag automatically answers "yes" to prompts.
apt install -y build-essential cmake cmake-doc doxygen mscgen dia graphviz valgrind gdb-doc gdbserver valgrind-mpi clangd clang llvm clang-tidy clang-format
if [ $? -ne 0 ]; then
    echo "Error installing packages. Exiting."
    exit 1
fi

echo "All specified packages have been installed successfully."
