#include <iostream>
#include <cmath>
#include <string>

// Class representing a mathematical expression: (2 * c - lg(d / 4)) / (a * a - 1)
class MathExpression {
private:
    double a; // Operand a
    double c; // Operand c
    double d; // Operand d

public:
    // Default constructor
    MathExpression() {
        a = 0.0;
        c = 0.0;
        d = 4.0; // Avoid log(0) by default
    }

    // Parameterized constructor
    MathExpression(double aVal, double cVal, double dVal) {
        a = aVal;
        c = cVal;
        d = dVal;
    }

    // Setters for changing values dynamically
    void setA(double val) { a = val; }
    void setC(double val) { c = val; }
    void setD(double val) { d = val; }

    // Getters for retrieving internal data
    double getA() const { return a; }
    double getC() const { return c; }
    double getD() const { return d; }

    // Method to calculate the expression with built-in exception handling logic
    double calculate() const {
        // Exception 1: Logarithm domain error. d/4 must be strictly greater than 0.
        if (d <= 0) {
            throw "Mathematical Error: Logarithm argument must be positive (d > 0).";
        }

        // Exception 2: Division by zero error. Denominator (a*a - 1) cannot be equal to 0.
        // Using epsilon (1e-9) to securely compare double precision values
        if (std::abs(a * a - 1.0) < 1e-9) {
            throw "Mathematical Error: Division by zero detected (a^2 - 1 is equal to 0).";
        }

        // Safe computation using std::log10 for common logarithm (lg)
        double numerator = 2.0 * c - std::log10(d / 4.0);
        double denominator = a * a - 1.0;

        return numerator / denominator;
    }
};

int main() {
    std::cout << "--- Testing Exception Handling ---" << std::endl << std::endl;

    // Creating a static array of MathExpression objects to simulate different test cases
    MathExpression expressions[4] = {
        MathExpression(2.0, 3.0, 40.0),  // Case 1: Perfectly valid data
        MathExpression(1.0, 5.0, 16.0),  // Case 2: Division by zero error (a = 1)
        MathExpression(3.0, 2.0, -8.0),  // Case 3: Logarithm negative argument error (d <= 0)
        MathExpression(-1.0, 4.0, 4.0)   // Case 4: Division by zero error (a = -1)
    };

    // Processing each object in a standard loop using try-catch blocks
    for (int i = 0; i < 4; i++) {
        std::cout << "Evaluating Expression #" << i + 1 << ":" << std::endl;
        std::cout << "  Operands -> a: " << expressions[i].getA() 
                  << ", c: " << expressions[i].getC() 
                  << ", d: " << expressions[i].getD() << std::endl;

        try {
            // Attempting block calculation that might trigger an exception
            double result = expressions[i].calculate();
            std::cout << "  Computed Result: " << result << std::endl;
        }
        catch (const char* errorMessage) {
            // Catching mathematical runtime errors thrown as string literals
            std::cout << "  [EXCEPTION CAUGHT]: " << errorMessage << std::endl;
        }
        catch (...) {
            // Generic catch block to handle any other unexpected exceptions
            std::cout << "  [UNKNOWN EXCEPTION CAUGHT]!" << std::endl;
        }
        std::cout << "--------------------------------------------------" << std::endl;
    }

    return 0;
}
