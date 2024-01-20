#ifndef _TEST_PARSER_H_
#define _TEST_PARSER_H_

#include <iostream>
#include <string>
#include <filesystem>

#include "JsonParser.h"
#include "fileHandler.h"

// ANSI escape codes for color formatting
#define GREEN_TEXT "\033[32m" // Green
#define RED_TEXT "\033[31m"   // Red
#define RESET_TEXT "\033[0m"  // Reset color

bool containsInvalid(const std::string &str) {
    return str.find("invalid") != std::string::npos;
}

// Helper function to compare expected and actual results
void test(const std::string& json, bool expected, int &passed, int &failed) {
    JsonParser parser(json);
    bool result = parser.parse();
    
    std::cout << "Input: " << json << std::endl;
    std::cout << "Expected: " << std::boolalpha << expected << std::endl;
    std::cout << "Actual: " << result << std::endl;
    
    if (result == expected) {
        std::cout << GREEN_TEXT << "Test Passed!" << RESET_TEXT << std::endl;
        passed++;
    } else {
        std::cout << RED_TEXT << "Test Failed!" << RESET_TEXT << std::endl;
        failed++;
    }

    std::cout << "------------------------" << std::endl;
}

void testParser() {
    int passed = 0, failed = 0;

    test("{\"key\": \"value\"}", true, passed, failed);
    test("{\"number\": 42}", true, passed, failed);
    test("{\"bool\": true}", true, passed, failed);
    test("{\"array\": [1, 2, 3]}", true, passed, failed);
    test("{\"object\": {\"nested_key\": \"nested_value\"}}", true, passed, failed);
    test("{\"escaped_quotes\": \"This is a string with \\\"double quotes\\\"\"}", true, passed, failed);
    test("{\"invalid_json\": {\"key\": \"value\"", false, passed, failed);
    test("{\"invalid_json\": [1, 2, 3}", false, passed, failed);
    test("{\"invalid_json\": \"missing_quote: \"value\"}", false, passed, failed);
    test("{\"array_with_null\": [null, null, null]}", true, passed, failed);
    test("{\"nested_empty_object\": {}}", true, passed, failed);
    test("{\"escaped_newline\": \"This is a string with \\n new line\"}", true, passed, failed);
    test("{\"invalid_escape\": \"This is a string with \\\\q invalid escape\"}", true, passed, failed);
    test("{\"valid_float_number\": 3.1415}", true, passed, failed);
    test("{\"invalid_boolean\": truee}", false, passed, failed);
    test("{\"empty_object\": {}}", true, passed, failed);
    test("{\"empty_array\": []}", true, passed, failed);
    test("{\"key_with_spaces\": \"value with spaces\"}", true, passed, failed);
    test("{\"nested_arrays\": [[1, 2], [3, 4]]}", true, passed, failed);
    test("{\"mixed_array\": [1, \"two\", {\"key\": \"value\"}]}", true, passed, failed);
    test("{\"escaped_slash\": \"This is a string with \\\\/ escaped slash\"}", true, passed, failed);
    test("{\"multiline_string\": \"This is a\nmultiline\nstring\"}", true, passed, failed);
    test("{\"boolean_false\": false}", true, passed, failed);
    test("{\"unicode_escape\": \"\\u0041BC\"}", true, passed, failed);
    test("{\"escaped_backspace\": \"This is a string with \\b backspace\"}", true, passed, failed);

    // Print summary
    std::cout << "------------------------" << std::endl;
    std::cout << "Summary:" << std::endl;
    std::cout << "Total Tests: " << passed + failed << std::endl;
    std::cout << "Tests Passed: " << passed << std::endl;
    std::cout << "Tests Failed: " << failed << std::endl;
    std::cout << "------------------------" << std::endl;
}

void testParserFiles() {
    int passed = 0, failed = 0, total = 0;

    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator("tests")) {
            if (std::filesystem::is_regular_file(entry.path())) {
                std::string filePath = entry.path().relative_path().string();
                std::cout << "File: " << filePath << std::endl;
                std::string content = readFromFile(filePath);
                if (containsInvalid(filePath)) {
                    test(content, false, passed, failed);
                } else {
                    test(content, true, passed, failed);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Print summary
    std::cout << "------------------------" << std::endl;
    std::cout << "Summary:" << std::endl;
    std::cout << "Total Tests: " << passed + failed << std::endl;
    std::cout << "Tests Passed: " << passed << std::endl;
    std::cout << "Tests Failed: " << failed << std::endl;
    std::cout << "------------------------" << std::endl;
}

#endif