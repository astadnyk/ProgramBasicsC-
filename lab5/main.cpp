#include <iostream>
#include <cmath>
#include <iomanip>

// Base class - Figures
class Figure {
protected:
    // Protected access modifier allows derived classes to access these coordinates directly
    double x1, y1; // Vertex 1
    double x2, y2; // Vertex 2
    double x3, y3; // Vertex 3

public:
    // Parameterized constructor
    Figure(double x1, double y1, double x2, double y2, double x3, double y3)
        : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {
        std::cout << "[Log] Base class 'Figure' constructor called." << std::endl;
    }

    // Method to calculate the length of a side between two coordinate points
    double computeSideLength(double xA, double yA, double xB, double yB) const {
        return std::sqrt(std::pow(xB - xA, 2) + std::pow(yB - yA, 2));
    }
};

// Derived class - Triangles
class Triangle : public Figure {
public:
    // Parameterized constructor passing arguments to the base class constructor
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
        : Figure(x1, y1, x2, y2, x3, y3) {
        std::cout << "[Log] Derived class 'Triangle' constructor called." << std::endl;
    }

    // Helper methods to get lengths of all three sides using the inherited base method
    double getSideA() const { return computeSideLength(x1, y1, x2, y2); }
    double getSideB() const { return computeSideLength(x2, y2, x3, y3); }
    double getSideC() const { return computeSideLength(x3, y3, x1, y1); }

    // Method to calculate Perimeter
    double calculatePerimeter() const {
        return getSideA() + getSideB() + getSideC();
    }

    // Method to calculate Area using Heron's formula
    double calculateArea() const {
        double a = getSideA();
        double b = getSideB();
        double c = getSideC();
        double p = calculatePerimeter() / 2.0; // Semi-perimeter
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    // Method to output object data
    void printTriangleData() const {
        std::cout << "Triangle Vertex Coordinates:" << std::endl;
        std::cout << "  Vertex 1 (A): (" << x1 << ", " << y1 << ")" << std::endl;
        std::cout << "  Vertex 2 (B): (" << x2 << ", " << y2 << ")" << std::endl;
        std::cout << "  Vertex 3 (C): (" << x3 << ", " << y3 << ")" << std::endl;
        std::cout << "Calculated Side Lengths:" << std::endl;
        std::cout << "  Side AB: " << getSideA() << " units" << std::endl;
        std::cout << "  Side BC: " << getSideB() << " units" << std::endl;
        std::cout << "  Side CA: " << getSideC() << " units" << std::endl;
    }
};

int main() {
    std::cout << "--- Testing Single Inheritance ---" << std::endl << std::endl;

    std::cout << "--- Step 1: Instantiating a Derived Class Object ---" << std::endl;
    // Creating a triangle with coordinates: (0,0), (4,0), (0,3)
    Triangle myTriangle(0.0, 0.0, 4.0, 0.0, 0.0, 3.0);
    std::cout << std::endl;

    std::cout << "--- Step 2: Displaying Object Input Data ---" << std::endl;
    myTriangle.printTriangleData();
    std::cout << std::endl;

    std::cout << "--- Step 3: Computing and Outputting Area & Perimeter ---" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Perimeter of the triangle: " << myTriangle.calculatePerimeter() << " units" << std::endl;
    std::cout << "Area of the triangle:      " << myTriangle.calculateArea() << " sq. units" << std::endl;

    return 0;
}
