#!/bin/bash

# Ensure the script stops on any error
set -e

# Define paths for source files and the output executable
PARSER_SRC="../../src/parser/parser.cpp"
TEST_PARSER_SRC="test_parser.cpp"
OUTPUT_EXEC="parser_test"

# Define the path to GoogleTest
GTEST_INCLUDE_PATH="/usr/include/gtest"
GTEST_LIB_PATH="/usr/lib/x86_64-linux-gnu"

# Step 1: Compile the source files and tests
echo "Compiling Parser and test files..."
g++ -std=c++11 -isystem $GTEST_INCLUDE_PATH -pthread $PARSER_SRC $TEST_PARSER_SRC -lgtest -lgtest_main -o $OUTPUT_EXEC -L$GTEST_LIB_PATH

# Step 2: Run the tests
echo "Running tests..."
./$OUTPUT_EXEC

