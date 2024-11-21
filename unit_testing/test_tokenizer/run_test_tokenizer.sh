#!/bin/bash

# Ensure the script stops on any error
set -e

# Define paths for source files and the output executable
TOKENIZER_SRC="../../src/tokenizer/tokenizer.cpp"
TEST_TOKENIZER_SRC="test_tokenizer.cpp"
OUTPUT_EXEC="tokenizer_test"

# Define the path to GoogleTest
GTEST_INCLUDE_PATH="/usr/include/gtest"
GTEST_LIB_PATH="/usr/lib/x86_64-linux-gnu"

# Step 1: Compile the source files and tests
echo "Compiling Tokenizer and test files..."
g++ -std=c++11 -isystem $GTEST_INCLUDE_PATH -pthread $TOKENIZER_SRC $TEST_TOKENIZER_SRC -lgtest -lgtest_main -o $OUTPUT_EXEC -L$GTEST_LIB_PATH

# Step 2: Run the tests
echo "Running tests..."
./$OUTPUT_EXEC

