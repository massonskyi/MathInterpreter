#include "../include/utils.hpp"

bool containsAnySymbol(const std::string& str, const std::string& symbols) {
    for (char ch : symbols) {
        if (ch != ' ' && str.find(ch) != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string findContainsSymbol(const std::string& str, const std::string& symbols){
    for (char ch : symbols) {
        if (ch != ' ' && str.find(ch) != std::string::npos) {
            return std::string(1, ch);
        }
    }
}