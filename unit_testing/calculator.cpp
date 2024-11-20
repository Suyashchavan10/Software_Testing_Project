#include <stdexcept>
using namespace std;

class Calculator {
public:
    // Adds two numbers
    double add(double a, double b) {
        return a + b;
    }

    // Subtracts b from a
    double subtract(double a, double b) {
        return a - b;
    }

    // Multiplies two numbers
    double multiply(double a, double b) {
        return a * b;
    }

    // Divides a by b
    // Throws exception if dividing by zero
    double divide(double a, double b) {
        if (b == 0) {
            throw invalid_argument("Division by zero is undefined");
        }
        return a / b;
    }
};
