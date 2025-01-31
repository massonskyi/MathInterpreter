//
// Created by massonskyi on 21.01.25.
//

#ifndef REGEXMANAGER_HPP
#define REGEXMANAGER_HPP
#include <string>
#include <unordered_map>
#include <stdexcept>

class _M_regex_manager final{
public:
    enum class RegexType{
        VECTOR_REGEX,
        MATRIX_REGEX,
        RATIONAL_ASSIGNMENT_REGEX,
        RATIONAL_OPERATION_REGEX,
        INTEGER_REGEX,
        MATRIX_OPERATION_REGEX,
        VECTOR_LITERAL_REGEX,
        VECTOR_OPERATION_REGEX,
        VARIABLE_ASSIGNMENT_REGEX,
        WHITESPACE_TRIM_REGEX,
        SYMBOLS_REGEX
    };

    std::string get_regex_basic_string(const RegexType type) const {
        if (const auto it = _M_regex_patterns.find(type); it != _M_regex_patterns.end()) {
            return it->second;
        }
        throw std::runtime_error("Invalid RegexType");
    }
private:
    const std::unordered_map<RegexType, std::string> _M_regex_patterns = {
        {RegexType::VECTOR_REGEX, R"(\[\s*(\d+\s*(,\s*\d+\s*)*)\])"},
        {RegexType::MATRIX_REGEX, R"(\[\s*\[\s*(\d+(\s+\d+)*)\s*\](\s*\[\s*(\d+(\s+\d+)*)\s*\])*\s*\])"},
        {RegexType::RATIONAL_ASSIGNMENT_REGEX, R"((\d+)\/(\d+))"},
        {RegexType::RATIONAL_OPERATION_REGEX, R"((\w+|(\d+\/\d+))\s*([+\-*/])\s*(\w+|(\d+\/\d+)))"},
        {RegexType::INTEGER_REGEX, R"(\d+)"},
        {RegexType::MATRIX_OPERATION_REGEX, R"((\w+)\s*([+\-*/])\s*(\w+))"},
        {RegexType::VECTOR_LITERAL_REGEX, R"(^\[\s*(\d+\s*,\s*)*\d+\s*\]$)"},
        {RegexType::VECTOR_OPERATION_REGEX, R"((\w+)\s*([+\-*/])\s*(\w+))"},
        {RegexType::VARIABLE_ASSIGNMENT_REGEX, R"((\w+|d+)\s*([+\-*/])\s*(\w+|\d+))"},
        {RegexType::WHITESPACE_TRIM_REGEX, R"(\s+)"},
        {RegexType::SYMBOLS_REGEX, R"(\s*(\S+))"}
    };
};
#endif //REGEXMANAGER_HPP
