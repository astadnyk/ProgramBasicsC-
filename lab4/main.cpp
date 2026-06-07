#include <iostream>
#include <string>

// Class representing a string with overloaded operators
class MyString {
private:
    std::string value; // Encapsulated string characters

public:
    // Default constructor
    MyString() : value("") {
        std::cout << "[Log] Default constructor called" << std::endl;
    }

    // Parameterized constructor
    MyString(const std::string& str) : value(str) {
        std::cout << "[Log] Parameterized constructor called with: \"" << str << "\"" << std::endl;
    }

    // Copy constructor
    MyString(const MyString& other) : value(other.value) {
        std::cout << "[Log] Copy constructor called to replicate: \"" << other.value << "\"" << std::endl;
    }

    // Method to calculate string length
    size_t getLength() const {
        return value.length();
    }

    // Method to get string value
    std::string getValue() const {
        return value;
    }

    // Overloading '+' operator to concatenate two MyString objects
    MyString operator+(const MyString& other) const {
        return MyString(this->value + other.value);
    }

    // Overloading '-' operator to subtract (remove) a specific character from the string
    MyString operator-(char ch) const {
        std::string resultStr = "";
        for (char c : this->value) {
            if (c != ch) {
                resultStr += c; // Keep characters that are NOT equal to 'ch'
            }
        }
        return MyString(resultStr);
    }

    // Overloading assignment operator for seamless object copying during math steps
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            this->value = other.value;
        }
        return *this;
    }
};

int main() {
    std::cout << "--- Testing Advanced Operator Overloading ---" << std::endl << std::endl;

    std::cout << "--- Step 1: Creating objects using three different constructors ---" << std::endl;
    
    // Creating S1 using the Default Constructor
    MyString S1; 

    // Creating S2 using the Parameterized Constructor (contains '#' symbols)
    MyString S2("KPI#Information#Systems#and#Technologies#"); 

    // Creating S3 using the Copy Constructor (copied from a temporary string)
    MyString temporaryBase(" - C++ is powerful!");
    MyString S3(temporaryBase); 

    std::cout << std::endl;
    std::cout << "Initial states of objects:" << std::endl;
    std::cout << "S1: \"" << S1.getValue() << "\" (Length: " << S1.getLength() << ")" << std::endl;
    std::cout << "S2: \"" << S2.getValue() << "\" (Length: " << S2.getLength() << ")" << std::endl;
    std::cout << "S3: \"" << S3.getValue() << "\" (Length: " << S3.getLength() << ")" << std::endl;
    std::cout << std::endl;

    // Task action 1: "deduct" the character '#' from object S2
    std::cout << "--- Step 2: Subtracting character '#' from object S2 ---" << std::endl;
    S2 = S2 - '#';
    std::cout << "Modified S2: \"" << S2.getValue() << "\" (Length: " << S2.getLength() << ")" << std::endl;
    std::cout << std::endl;

    // Task action 2: "add" objects S2, S3 and "place" the result into object S1
    std::cout << "--- Step 3: Adding objects S2 and S3, placing result into S1 ---" << std::endl;
    S1 = S2 + S3;

    // Printing final results on the screen
    std::cout << std::endl;
    std::cout << "=== FINAL OUTPUT RESULTS ===" << std::endl;
    std::cout << "S1 (S2 + S3): \"" << S1.getValue() << "\" (Length: " << S1.getLength() << ")" << std::endl;
    std::cout << "S2 (Cleaned):  \"" << S2.getValue() << "\"" << std::endl;
    std::cout << "S3 (Original): \"" << S3.getValue() << "\"" << std::endl;

    return 0;
}
