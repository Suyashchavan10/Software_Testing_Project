#include <gtest/gtest.h>
#include "calculator.cpp"  // Including the Calculator class for testing
using namespace std;

// Test cases for Calculator class
TEST(CalculatorTest, AddTest) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.add(3.0, 2.0), 5.0);  // Test addition
    EXPECT_DOUBLE_EQ(calc.add(-3.0, 2.0), -1.0); // Test addition with negative number
}

TEST(CalculatorTest, SubtractTest) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.subtract(3.0, 2.0), 1.0);  // Test subtraction
    EXPECT_DOUBLE_EQ(calc.subtract(2.0, 3.0), -1.0); // Test subtraction where result is negative
}

TEST(CalculatorTest, MultiplyTest) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.multiply(3.0, 2.0), 6.0);  // Test multiplication
    EXPECT_DOUBLE_EQ(calc.multiply(-3.0, 2.0), -6.0); // Test multiplication with negative number
}

TEST(CalculatorTest, DivideTest) {
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.divide(6.0, 2.0), 3.0);  // Test division
    EXPECT_DOUBLE_EQ(calc.divide(-6.0, 2.0), -3.0); // Test division with negative number
    EXPECT_THROW(calc.divide(6.0, 0.0), invalid_argument);  // Test division by zero, should throw
}

