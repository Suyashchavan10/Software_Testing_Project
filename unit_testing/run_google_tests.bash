#!/bin/bash

# Ensure the script stops on any error
set -e

# Define paths for source files and the output executable
CALCULATOR_SRC="calculator.cpp"
TEST_SRC="calculator_test.cpp"
OUTPUT_EXEC="calculator_test"

# Define the path to GoogleTest (change it to where GoogleTest is installed on your system)
GTEST_INCLUDE_PATH="/usr/include/gtest"
GTEST_LIB_PATH="/usr/lib/x86_64-linux-gnu"

# Step 1: Compile the source files and tests
echo "Compiling Calculator and test files..."
g++ -std=c++11 -isystem $GTEST_INCLUDE_PATH -pthread $CALCULATOR_SRC $TEST_SRC -lgtest -lgtest_main -o $OUTPUT_EXEC -L$GTEST_LIB_PATH

# Step 2: Run the tests
echo "Running tests..."
./$OUTPUT_EXEC

# End of script
