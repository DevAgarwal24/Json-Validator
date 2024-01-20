#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

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

#endif