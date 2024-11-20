#!/bin/bash

# Set environment variables or paths if necessary
# export PATH=$PATH:/usr/local/bin:/usr/bin

# First command: Compile the C++ file with clang-12 and Mull
clang-12 -fexperimental-new-pass-manager \
         -fpass-plugin=/usr/lib/mull-ir-frontend-12 \
         -g -grecord-command-line \
         main.cpp -o hello-world

# Check if the first command was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running Mull tests..."

    # Second command: Run Mull tests with the runner
    mull-runner-12 -ide-reporter-show-killed hello-world
else
    echo "Compilation failed. Exiting..."
    exit 1
fi
