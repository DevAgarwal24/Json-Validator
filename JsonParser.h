#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include <string>
#include <cctype>

class JsonParser {
public:
    JsonParser(const std::string& input) : input_(input), position_(0), isValidJson_(true) {}

    bool parse() {
        trimWhitespace(); // Skip leading whitespace characters

        if (position_ >= input_.size()) {
            std::cerr << "Error: Input is empty. JSON must contain at least an object or an array." << std::endl;
            isValidJson_ = false;
        } else {
            parseValue();
            trimWhitespace(); // Skip trailing whitespace characters
        }

        return isValidJson_;
    } // parse()

private:

    void parseValue() {
        char currentChar = getCurrentChar();

        if (currentChar == '\0') {
            
        } else if (currentChar == '{') {
            parseObject();
        } else if (currentChar == '\"') {
            parseString();
        } else if (currentChar == 't' || currentChar == 'f') {
            parseBoolean();
        } else if (currentChar == 'n'){
            parseNull();
        } else {
            isValidJson_ = false;
            std::cerr << "Error: Unexpected character '" << currentChar << "'" << std::endl;
        }
    } // parseValue()

    void parseObject() {
        // Expecting "{"
        if (getCurrentChar() == '{') {
            // Move the position forward to skip it
            position_++;

            // Parse key-value pair within the object
            parseObjectMembers();

            // Expecting "}"
            if (getCurrentChar() == '}') {
                position_++;
                std::cout << "Parsed Object" << std::endl;
                trimWhitespace();
                // After parsing the object, make a recursive call to parse the next JSON value
                parseValue();
            } else {
                // Handle error for missing closing curly bracket
                isValidJson_ = false;
                std::cerr << "Error: Expected '}' but found '" << extractUnexpected(1) << "'" << std::endl;
            }
        } else {
            isValidJson_ = false;
            std::cerr << "Error: Expected '{' but found '" << extractUnexpected(1) << "'" << std::endl;
        }
    } // parseObject()

    void parseObjectMembers() {
        while (getCurrentChar() != '}' && position_ < input_.size()) {
            trimWhitespace();

            // Expecting a string
            if (!parseString()) {
                return;
            }

            trimWhitespace();

            // Expecting ":"
            if (getCurrentChar() == ':') {
                position_++;
                trimWhitespace();

                // Parse Value
                // Parsing string for the test case
                parseValue();
                trimWhitespace();

                // Expecting "," for the next pair or "}" to end the object
                if (getCurrentChar() == ',') {
                    position_++;
                    trimWhitespace();

                    // Check if there is another object member
                    if (getCurrentChar() == '}') {
                        isValidJson_ = false;
                        std::cerr << "Error: Trailing comma in an object" << std::endl;
                    }
                } else if (getCurrentChar() != '}') {
                    isValidJson_ = false;
                    std::cerr << "Error: Expected ',' or '}' but found '" << extractUnexpected(1) << "'" << std::endl;
                }
            } else {
                // Handle error for ":" in a key value pair
                isValidJson_ = false;
                std::cerr << "Error: Expected ':' but found '" << extractUnexpected(1) << "'" << std::endl;
            }
        }
    } // parseObjectMembers()

    bool parseString() {
        if (getCurrentChar() == '\"') {
            position_++;

            std::string parsedString;

            // Parse characters until the closing double quote is found
            while (getCurrentChar() != '\"' && position_ < input_.size()) {
                // Handle escaped characters
                if (getCurrentChar() == '\\') {
                    position_++;
                    if (position_ < input_.size()) {
                        // Handle common escape sequences
                        char escapedChar = getCurrentChar();
                        switch (escapedChar) {
                            case '\"':
                            case '\\':
                            case '/':
                                parsedString += escapedChar;
                                break;
                            case 'b':
                                parsedString += '\b'; // Backspace
                                break;
                            case 'f':
                                parsedString += '\f'; // Form feed
                                break;
                            case 'n':
                                parsedString += '\n'; // New line
                                break;
                            case 'r':
                                parsedString += '\r'; // Carriage return
                                break;
                            case 't':
                                parsedString += '\t'; // Tab
                                break;
                            // Add more escape sequences as needed
                            default:
                                // Handle unrecognized escape sequences as-is
                                parsedString += '\\';
                                parsedString += escapedChar;
                        }
                    }
                } else {
                    // Append the current character to the parsed string
                    parsedString += getCurrentChar();
                }

                position_++;
            }

            // Expecting the closing double quotes to end the string
            if (getCurrentChar() == '\"') {
                position_++;
                std::cout << "Parsed string: " << parsedString << std::endl;
            } else {
                // Handle error for missing closing double quotes
                isValidJson_ = false;
                std::cerr << "Error: Expected '\"' but found '" << extractUnexpected(1) << "'" << std::endl;
                return false;
            }
        } else {
            // Handle error for missing opening double quotes
            isValidJson_ = false;
            std::cerr << "Error Expected '\"' but found '" << extractUnexpected(1) << "'" << std::endl;
            return false;
        }

        return true;
    } // parseString()

    void parseBoolean() {
        if (input_.compare(position_, 4, "true") == 0) {
            // Ensure that the next character after "true" is not a valid identifier character
            if (position_ + 4 <= (input_.size() - 1) && !isIdentifierChar(input_[position_ + 4])) {
                std::cout << "Parsed boolean: true" << std::endl;
                position_ += 4;
            } else {
                std::cerr << "Error: Unexpected characters after 'true'" << std::endl;
            }
        } else if (input_.compare(position_, 5, "false") == 0) {
            if (position_ + 5 <= (input_.size() - 1) && !isIdentifierChar(input_[position_ + 5])) {
                std::cout << "Parsed boolean: false" << std::endl;
                position_ += 5;
            } else {
                std::cerr << "Error: Unexpected characters after 'true'" << std::endl;
            }
        } else {
            std::cerr << "Error: Expected 'true' or 'false' but found '" << extractUnexpected(6) << "'" << std::endl;
        }
    } // parseBoolean()

    void parseNull() {
        if (input_.compare(position_, 4, "null") == 0) {
            // Ensure that the next character after "null" is not a valid identifier character
            if (position_ + 4 <= (input_.size() - 1) && !isIdentifierChar(input_[position_ + 4])) {
                std::cout << "Parsed null" << std::endl;
                position_ += 4;
            } else {
                std::cerr << "Error: Unexpected characters after 'null'" << std::endl;
            }
        } else {
            std::cerr << "Error: Expected 'true' or 'false' but found '" << extractUnexpected(5) << "'" << std::endl;
        }
    } // parseNull()

    // Helper functions
    char getCurrentChar() {
        return position_ < input_.size() ? input_[position_] : '\0';
    }

    std::string extractUnexpected(size_t count) {
        std::string unexpected;
        for (size_t i = 0; i < count && (position_ + i) < input_.size(); ++i) {
            unexpected += input_[position_ + i];
        }
        return unexpected;
    }

    void trimWhitespace() {
        while (position_ < input_.size() && std::isspace(getCurrentChar())) {
            position_++;
        }
    }

    bool isIdentifierChar(char c) {
        // Check if the character is a valid identifier character
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
    }

    const std::string& input_;
    size_t position_;
    bool isValidJson_;
};

#endif