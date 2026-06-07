#include <iostream>
#include <string>

// Base class representing a string interface
class StringBase {
protected:
    std::string value; // Encapsulated string data accessible by derived classes

public:
    // Parameterized constructor
    StringBase(std::string val) {
        value = val;
    }

    // Virtual destructor required for secure polymorphism and preventing memory leaks
    virtual ~StringBase() {}

    // Virtual function to calculate string length
    virtual size_t calculateLength() const {
        return value.length();
    }

    // Pure virtual function for character removal (polymorphic interface)
    virtual void removeTargetChar() = 0;

    // Getter method to retrieve the string value
    std::string getValue() const {
        return value;
    }
};

// Derived class for digit-based string processing
class Digits : public StringBase {
public:
    // Constructor passing argument to the base class
    Digits(std::string val) : StringBase(val) {}

    // Overriding the length calculation method
    size_t calculateLength() const override {
        return value.length();
    }

    // Overriding the method to remove all '5' characters
    void removeTargetChar() override {
        std::string result = "";
        // Classic indexed loop preferred by 2nd-year students
        for (size_t i = 0; i < value.length(); i++) {
            if (value[i] != '5') {
                result += value[i]; // Append all characters except '5'
            }
        }
        value = result; // Update the internal string state
    }
};

// Derived class for letter-based string processing
class Letters : public StringBase {
public:
    // Constructor passing argument to the base class
    Letters(std::string val) : StringBase(val) {}

    // Overriding the length calculation method
    size_t calculateLength() const override {
        return value.length();
    }

    // Overriding the method to remove all 'a' characters
    void removeTargetChar() override {
        std::string result = "";
        // Classic indexed loop preferred by 2nd-year students
        for (size_t i = 0; i < value.length(); i++) {
            if (value[i] != 'a') {
                result += value[i]; // Append all characters except 'a'
            }
        }
        value = result; // Update the internal string state
    }
};

int main() {
    std::cout << "--- Testing Polymorphism ---" << std::endl << std::endl;

    // Instantiating objects of derived classes
    Digits digitsObj("12345_KPI_555_Sugar_5");
    Letters lettersObj("abracadabra_labs_aaaa");

    // Creating a static array of base class pointers for upcasting (no vector used)
    StringBase* polyArray[2];
    
    // Storing addresses of derived objects in the base class array
    polyArray[0] = &digitsObj;
    polyArray[1] = &lettersObj;

    // Processing objects in a loop utilizing dynamic polymorphism
    for (int i = 0; i < 2; i++) {
        std::cout << "Processing object #" << i + 1 << " via base class pointer:" << std::endl;
        std::cout << "  Original string:  \"" << polyArray[i]->getValue() << "\"" << std::endl;
        std::cout << "  Original length: " << polyArray[i]->calculateLength() << " chars." << std::endl;
        
        // Polymorphic call: executes custom logic depending on runtime object type
        polyArray[i]->removeTargetChar();
        
        std::cout << "  Processed string:   \"" << polyArray[i]->getValue() << "\"" << std::endl;
        std::cout << "  New length:       " << polyArray[i]->calculateLength() << " chars." << std::endl;
        std::cout << "--------------------------------------------------------" << std::endl;
    }

    return 0;
}
