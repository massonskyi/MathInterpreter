#include <iostream>
#include "include/core.h"
#include "include/interpreter.hpp"
#include "lib/cxxopts-3.2.0/include/cxxopts.hpp"

void printHelp() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  --help           Print usage" << std::endl;
    std::cout << "  --version        Print version" << std::endl;
    std::cout << "  --file <path>    Path to file" << std::endl;
}
void printVersion() {
    std::cout << VERSION << std::endl;
}
void processFile(const std::string& filePath) {
    std::cout << "File path: " << filePath << std::endl;
    // Добавьте здесь обработку файла
}
cxxopts::ParseResult parseOptions(int argc, char** argv) {
    cxxopts::Options options("app", "Console application");

    options.add_options()
        ("h,help", "Print usage")
        ("v,version", "Print version")
        ("f,file", "Path to file", cxxopts::value<std::string>());

    return options.parse(argc, argv);
}

int handleOptions(const cxxopts::ParseResult& result) {
    if (result.count("help")) {
        printHelp();
        return 0x00;
    }

    if (result.count("version")) {
        printVersion();
        return 0x00;
    }

    if (result.count("file")) {
        std::string filePath = result["file"].as<std::string>();
        processFile(filePath);
        return 0x55;
    }

    std::cout << "No valid command provided. Use --help for usage." << std::endl;
}

int main(int argc, char** argv) {
    auto result = parseOptions(argc, argv);
    auto r = handleOptions(result);
    if(r == 0x00) {
        exit(0x00);
    }
    Interpreter interpreter;
    interpreter.processConsole();
    return 0;
}