#!/bin/bash

# Ensure the script stops on any error
set -e

# Define paths for source files and the output executable
CODEGENERATOR_SRC="../../src/codeGenerator/codeGenerator.cpp"
TEST_CODEGENERATOR_SRC="test_codeGenerator.cpp"
OUTPUT_EXEC="codeGenerator_test"

# Define the path to GoogleTest
GTEST_INCLUDE_PATH="/usr/include/gtest"
GTEST_LIB_PATH="/usr/lib/x86_64-linux-gnu"

# Step 1: Compile the source files and tests
echo "Compiling CodeGenerator and test files..."
g++ -std=c++11 -isystem $GTEST_INCLUDE_PATH -pthread $CODEGENERATOR_SRC $TEST_CODEGENERATOR_SRC -lgtest -lgtest_main -o $OUTPUT_EXEC -L$GTEST_LIB_PATH

# Step 2: Run the tests
echo "Running tests..."
./$OUTPUT_EXEC

