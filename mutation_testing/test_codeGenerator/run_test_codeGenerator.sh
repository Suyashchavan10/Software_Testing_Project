#!/bin/bash

# Define paths for source files and the output executable
CODEGENERATOR_SRC="../../src/codeGenerator/codeGenerator.cpp"
TEST_CODEGENERATOR_SRC="test_codeGenerator.cpp"
OUTPUT_EXEC="codeGenerator_test"

# Ensure required files exist
if [[ ! -f $CODEGENERATOR_SRC ]]; then
    echo "CodeGenerator source file not found: $CODEGENERATOR_SRC"
    exit 1
fi

if [[ ! -f $TEST_CODEGENERATOR_SRC ]]; then
    echo "Test file not found: $TEST_CODEGENERATOR_SRC"
    exit 1
fi

# Step 1: Compile the source and test files with clang-12 and Mull
clang-12 -fexperimental-new-pass-manager \
         -fpass-plugin=/usr/lib/mull-ir-frontend-12 \
         -stdlib=libstdc++ \
         -g -grecord-command-line \
         $TEST_CODEGENERATOR_SRC -o $OUTPUT_EXEC -lstdc++ -lm

# Check if compilation was successful
if [[ $? -ne 0 ]]; then
    echo "Compilation failed. Exiting..."
    exit 1
fi

echo "Compilation successful. Running Mull tests..."

# Step 2: Run the compiled executable with Mull runner
mull-runner-12 -ide-reporter-show-killed $OUTPUT_EXEC

# Check if Mull tests ran successfully
if [[ $? -ne 0 ]]; then
    echo "Mull testing failed."
    exit 1
fi

echo "All tests passed successfully."
exit 0

