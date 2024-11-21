# Google Test Introduction

Google Test, also known as **GTest**, is a unit testing framework for C++ developed by Google. It provides a rich set of features for writing and managing test cases and supports test assertions, test fixtures, and custom configurations.

---

## Basic Google Test Commands and Their Functions

### **Test Definitions**
- `TEST(TestSuiteName, TestName)`
  - Defines a test case. TestSuiteName groups related tests, and TestName identifies the test.

---

### **Assertions**
#### Fatal Assertions : Halts the test on failure.
- `ASSERT_TRUE(condition)`  
  - Verifies the condition is `true`. 
- `ASSERT_FALSE(condition)`  
  - Verifies the condition is `false`. 
- `ASSERT_EQ(val1, val2)`  
  - Verifies `val1` is equal to `val2`. 
- `ASSERT_NE(val1, val2)`  
  - Verifies `val1` is not equal to `val2`. 
- `ASSERT_LT(val1, val2)`  
  - Verifies `val1` is less than `val2`. 
- `ASSERT_GT(val1, val2)`  
  - Verifies `val1` is greater than `val2`. 

#### Non-Fatal Assertions : Continues the test on failure.
- `EXPECT_TRUE(condition)`  
  - Verifies the condition is `true`. 
- `EXPECT_FALSE(condition)`  
  - Verifies the condition is `false`. 
- `EXPECT_EQ(val1, val2)`  
  - Verifies `val1` is equal to `val2`. 
- `EXPECT_NE(val1, val2)`  
  - Verifies `val1` is not equal to `val2`. 
- `EXPECT_LT(val1, val2)`  
  - Verifies `val1` is less than `val2`. 
- `EXPECT_GT(val1, val2)`  
  - Verifies `val1` is greater than `val2`. 

---

### **Test Fixtures**
- `TEST_F(TestFixtureName, TestName)`
  - Defines a test using a test fixture for shared setup and teardown code.

---

### **Parameterized Tests**
- `INSTANTIATE_TEST_SUITE_P(Prefix, TestSuiteName, Generator)`
  - Generates tests with different parameters for a parameterized test suite.

---

### **Test Execution**
- `RUN_ALL_TESTS()`
  - Executes all defined tests in the program.

---

### **Custom Failure Messages**
- `ADD_FAILURE()`
  - Explicitly marks a failure in a test case with a custom message.
- `FAIL()`
  - Immediately fails the test with a custom message.

---

### **Setup and Teardown**
- `SetUp()`
  - Runs before each test in a test suite.
- `TearDown()`
  - Runs after each test in a test suite.
