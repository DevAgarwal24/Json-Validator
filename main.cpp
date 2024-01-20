#include <iostream>
#include <string>

#include "JsonParser.h"
#include "testParser.h"

void printHelp() {
    std::cout   << "Usage: json [options] string/file\n"
                << "Utility to validate JSON Files\n"
                << "Options:\n"
                << "  -h, --help          Display this help and exit\n"
                << "  -f, --file          Path to the json file\n"
                << "  -s, --string        Json string (default)\n";
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Missing arguments. Use -h or --help for help.\n";
        return 1;
    }

    std::string options = argv[1];
    std::string fileContent;

    if (options.compare("-t") == 0) {
        testParser();
        testParserFiles();
        return 0;
    }

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