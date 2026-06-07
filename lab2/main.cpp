#include <iostream>
#include <string>
#include <cctype>

// Class representing a single line of text
class TextLine {
private:
    std::string content;

public:
    TextLine() : content("") {}
    TextLine(const std::string& text) : content(text) {}

    std::string getContent() const {
        return content;
    }

    void setContent(const std::string& text) {
        content = text;
    }

    void capitalizeWords() {
        bool isNewWord = true;
        for (size_t i = 0; i < content.length(); ++i) {
            if (std::isspace(static_cast<unsigned char>(content[i]))) {
                isNewWord = true;
            } else if (isNewWord) {
                content[i] = std::toupper(static_cast<unsigned char>(content[i]));
                isNewWord = false;
            }
        }
    }

    void print() const {
        std::cout << content << std::endl;
    }
};

// Class-container representing the whole text (using a standard array)
class Text {
private:
    static const size_t MAX_LINES = 100; // Maximum allowed lines in our text array
    TextLine lines[MAX_LINES];           // Standard array of TextLine objects
    size_t lineCount;                    // Counter for current active lines

public:
    // Constructor initializes the line counter to 0
    Text() : lineCount(0) {}

    // Add a line to the text
    void addLine(const TextLine& line) {
        if (lineCount < MAX_LINES) {
            lines[lineCount] = line; // Place the object at the current free index
            lineCount++;             // Increment the total count
        } else {
            std::cout << "Error: Maximum text capacity reached!" << std::endl;
        }
    }

    // Remove a line from the text by its index
    void removeLine(size_t index) {
        if (index < lineCount) {
            // Shift all subsequent lines to the left to fill the gap
            for (size_t i = index; i < lineCount - 1; ++i) {
                lines[i] = lines[i + 1];
            }
            lineCount--; // Decrease the counter because one line is gone
        } else {
            std::cout << "Error: Index " << index << " out of bounds!" << std::endl;
        }
    }

    // Remove all lines that contain a specific substring
    void removeLinesContaining(const std::string& substring) {
        for (size_t i = 0; i < lineCount; ) {
            // Check if the substring is found in the current line
            if (lines[i].getContent().find(substring) != std::string::npos) {
                removeLine(i); // removeLine shifts everything left, so we DON'T increment 'i'
            } else {
                ++i; // Move to the next line only if no line was deleted
            }
        }
    }

    // Clear the entire text
    void clearText() {
        lineCount = 0; // Simply resetting the counter makes the array "empty" for us
    }

    // Find the length of the longest line
    size_t findLongestLineLength() const {
        size_t maxLength = 0;
        for (size_t i = 0; i < lineCount; ++i) {
            if (lines[i].getContent().length() > maxLength) {
                maxLength = lines[i].getContent().length();
            }
        }
        return maxLength;
    }

    // Capitalize the first letter of every word in the whole text
    void capitalizeAllLines() {
        for (size_t i = 0; i < lineCount; ++i) {
            lines[i].capitalizeWords(); // Call the logic for each individual line
        }
    }

    // Method to display the whole text
    void print() const {
        if (lineCount == 0) {
            std::cout << "[The text is completely empty]" << std::endl;
            return;
        }
        for (size_t i = 0; i < lineCount; ++i) {
            std::cout << "Line " << i << ": ";
            lines[i].print();
        }
    }
};

// Main function to demonstrate all functionality
int main() {
    std::cout << "--- Testing Simple Container Class 'Text' ---" << std::endl << std::endl;

    Text myDocument;

    // Adding lines
    std::cout << "--- Step 1: Adding lines to the text ---" << std::endl;
    myDocument.addLine(TextLine("welcome to c++ programming class."));
    myDocument.addLine(TextLine("this line contains a secret keyword."));
    myDocument.addLine(TextLine("short line."));
    myDocument.addLine(TextLine("another line with the secret word inside."));
    myDocument.print();
    std::cout << std::endl;

    // Finding the longest line length
    std::cout << "--- Step 2: Finding the longest line length ---" << std::endl;
    std::cout << "The longest line length is: " << myDocument.findLongestLineLength() << " characters." << std::endl;
    std::cout << std::endl;

    // Capitalizing all words
    std::cout << "--- Step 3: Capitalizing first letters of all words ---" << std::endl;
    myDocument.capitalizeAllLines();
    myDocument.print();
    std::cout << std::endl;

    // Removing a single line by index
    std::cout << "--- Step 4: Removing line at index 2 ---" << std::endl;
    myDocument.removeLine(2);
    myDocument.print();
    std::cout << std::endl;

    // Removing lines containing a substring
    std::cout << "--- Step 5: Removing lines containing 'Secret' ---" << std::endl;
    myDocument.removeLinesContaining("Secret");
    myDocument.print();
    std::cout << std::endl;

    // Clearing the text
    std::cout << "--- Step 6: Clearing all text ---" << std::endl;
    myDocument.clearText();
    myDocument.print();

    return 0;
}
