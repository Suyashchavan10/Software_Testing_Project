# Notes on Mutation Testing

## **1. Overview**
Mutation testing is a software testing technique that evaluates the quality of test cases by introducing small, deliberate modifications (mutations) into the source code and assessing whether the test cases can detect those changes. The goal is to ensure the robustness of tests and identify weaknesses.

---

## **2. Types of Mutation Testing**

### **Unit Mutation Testing**
- Focuses on individual units (e.g., functions or methods).
- **Objective**: Assess the robustness of unit tests.
- **Key Characteristics**:
  - Isolates units using mocks or stubs.
  - Mutates within the boundaries of the unit.
- Example Mutation:
  - Original Code: `return x + y;`
  - Mutation: `return x - y;`
- **Use Case**: Testing during early development stages.

### **Integration Mutation Testing**
- Focuses on multiple units interacting together.
- **Objective**: Evaluate integration reliability between units.
- **Key Characteristics**:
  - Tests at the boundaries between units.
  - Uses real or simulated components for testing.
- Example Mutation:
  - Original Code: `if (service.isValid())`
  - Mutation: `if (!service.isValid())`
- **Use Case**: Testing integration points during system development.

---

## **3. Mull Mutation Testing**
Mull is a mutation testing tool specifically designed for **C and C++ projects**. It automates mutation testing by introducing changes, running test cases, and evaluating the test outcomes.

### **Key Features:**
- **Platform**: Supports C and C++ codebases.
- **Automation**: Applies mutations automatically and executes tests.
- **Mutations Applied**:
  - Arithmetic operator changes (e.g., `+` to `-`).
  - Logical operator changes (e.g., `&&` to `||`).
  - Constant modifications (e.g., replacing `5` with `0`).

### **Execution Reports:**
- **Killed Mutants**: Mutations detected by test cases.
- **Survived Mutants**: Mutations not detected by test cases.
- **Ignored Mutants**: Mutations ignored due to test setup or configuration.

### **Example Usage:**
**Original Function**:
```cpp
bool isEven(int x) { return x % 2 == 0; }
```

Mutation: Change x % 2 == 0 to x % 2 != 0.

Test Objective: Ensure that test cases fail when this mutation occurs.

**Mutated Function**:
```cpp
bool isEven(int x) { return x % 2 != 0; }
```

---

## **4. Comparison of Mutation Testing Types**

| **Aspect**            | **Unit Mutation Testing**             | **Integration Mutation Testing**    | **Mull Mutation Testing**          |
|-----------------------|---------------------------------------|-------------------------------------|------------------------------------|
| **Scope**             | Single unit (method or function).     | Multiple units interacting together.| Entire codebase or targeted functions. |
| **Objective**         | Test unit-level robustness.           | Test integration-level reliability. | Automate mutation testing for C/C++ code. |
| **Mutations Applied** | Inside a single unit.                 | At interaction points between units.| Operator, constant, and boundary tweaks. |
| **Dependencies**      | Uses mocks/stubs for isolation.       | Requires real or simulated components. | Requires Mull tool configuration. |
| **Usage Stage**       | During development (low level).       | During system/integration testing.  | Continuous integration or manual analysis. |

---

## **5. Benefits of Mutation Testing**
1. **Improved Test Quality**: Ensures test cases effectively detect bugs.
2. **Code Robustness**: Identifies weak or missing test cases.
3. **Automation with Mull**: Speeds up mutation testing for C/C++.
4. **Early Detection**: Helps identify potential vulnerabilities early in development.

---

## **6. Challenges of Mutation Testing**
1. **Performance Overhead**: Running mutated tests increases execution time.
2. **False Positives**: Some mutations might not represent real-world scenarios.
3. **Setup Complexity**: Requires tools and configuration for large codebases.
