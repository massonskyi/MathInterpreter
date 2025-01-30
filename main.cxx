#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "include/core.hxx"
#include "include/interpreter.hxx"
#include "lib/cxxopts-3.2.0/include/cxxopts.hpp"
#include "include/io/ioreader.hxx"

#ifdef _WIN32
void initConsole()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
}
#endif

void printHelp() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  --help           Print usage" << std::endl;
    std::cout << "  --version        Print version" << std::endl;
    std::cout << "  --file <path>    Path to file" << std::endl;
}
void printVersion() {
    std::cout << VERSION << std::endl;
}
std::string processFile(const std::string& filePath) {
    return filePath;
}
cxxopts::ParseResult parseOptions(int argc, char** argv) {
    cxxopts::Options options("app", "Console application");

    options.add_options()
        ("h,help", "Print usage")
        ("v,version", "Print version")
        ("f,file", "Path to file", cxxopts::value<std::string>());

    return options.parse(argc, argv);
}

std::string  handleOptions(const cxxopts::ParseResult& result) {
    if (result.count("help")) {
        printHelp();
        return "";
    }

    if (result.count("version")) {
        printVersion();
        return "";
    }

    if (result.count("file")) {
        std::string filePath = result["file"].as<std::string>();
        return processFile(filePath);
        
    }

    return "s";
}

int main(int argc, char** argv) {
#ifdef _WIN32
    initConsole(); // Инициализация консольного ввода/вывода для UTF-8
#endif
    Interpreter interpreter;
    auto result = parseOptions(argc, argv);
    auto r = handleOptions(result);
    if(r.empty()) {
        exit(0x00);
    }else if(r == "s"){
        interpreter.processConsole();
    }else{
        interpreter.processFile(r);
    }
    return 0;
}