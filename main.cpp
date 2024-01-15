#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "JsonParser.h"

void printHelp() {
    std::cout   << "Usage: json [options] string/file\n"
                << "Utility to validate JSON Files\n"
                << "Options:\n"
                << "  -h, --help          Display this help and exit\n"
                << "  -f, --file          Path to the json file\n"
                << "  -s, --string        Json string (default)\n";
}

bool isJsonFile(const std::string& filePath) {
    // Find the position of the last dot in the file path
    size_t dotPos = filePath.find_last_of('.');

    // Check if the dot was found and if it is before the last directory separator
    if (dotPos != std::string::npos && dotPos > filePath.find_last_of('/')) {
        // Extract the file extension
        std::string fileExtension = filePath.substr(dotPos + 1);

        // Compare the file extension with ".json" (case-insensitive)
        for (auto& ch : fileExtension) {
            ch = tolower(ch);
        }

        return fileExtension == "json";
    }

    // No dot found or dot is at the end of the path (no extension)
    return false;
}

std::string readFromFile(const std::string &filePath) {
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "File doesn't exist. Use -h or --help for help.\n";
        return std::string();
        // return 1;
    }

    if (!isJsonFile(filePath)) {
        std::cerr << "Incorrect file type. Use -h or --help for help.\n";
        return std::string();
        // return 1;
    }

    // Open the file
    std::ifstream inputFile(filePath);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return std::string();
        // return 1;
    }

    // Read the file content into a string
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)),
                            std::istreambuf_iterator<char>());

    inputFile.close();

    return fileContent;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Missing arguments. Use -h or --help for help.\n";
        return 1;
    }

    std::string options = argv[1];
    std::string fileContent;
    if (options.compare("-h") == 0 || options.compare("--help") == 0) {
        printHelp();
        return 0;
    }

    if (options.compare("-f") == 0 || options.compare("--file") == 0) {
        if (argc < 3) {
            std::cerr << "Missing arguments. Use -h or --help for help.\n";
            return 1;
        }
        std::string filePath = argv[2];
        fileContent = readFromFile(filePath);
        if (fileContent.length() == 0) return 1;
    }

    if (options.compare("-s") == 0 || options.compare("--string") == 0) {
        if (argc < 3) {
            std::cerr << "Missing arguments. Use -h or --help for help.\n";
            return 1;
        }
        fileContent = argv[2];
    }

    if (argc == 2) {
        fileContent = argv[1];
    }

    // std::cout << "File content:\n" << fileContent << " " << fileContent.length() << std::endl;

    std::cout << "Validating the json file...\n";

    JsonParser parser(fileContent);
    std::cout << std::boolalpha << parser.parse() << std::endl;

    return 0;
} // main