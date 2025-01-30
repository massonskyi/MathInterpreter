#ifndef MATHINTERPRETER_TYPEDETECTOR_HPP
#define MATHINTERPRETER_TYPEDETECTOR_HPP

#include "../parsers/matrixparser.hxx"
#include "../parsers/vectorparser.hxx"
#include "../parsers/rationalparser.hxx"
#include "../data/data.hxx"
#include "../utils.hxx"

#include <regex>

class TypeDetector {
public:
    enum class DataType {
        Variable,
        Vector,
        Matrix,
        Rational,
        FunctionCall,
        Expression,
        Unknown
    };

    static DataType detect(const std::string& input) {
        std::string expr = remove_whitespaces(input);

        // Приоритетная проверка сложных типов
        if (MatrixParser::search(expr))    return DataType::Matrix;
        if (VectorParser::search(expr))    return DataType::Vector;
        if (RationalParser::search(expr))  return DataType::Rational;
        if (isFunctionCall(expr))          return DataType::FunctionCall;
        if (isExpression(expr))            return DataType::Expression;
        if (isNumber(expr))                return DataType::Variable;

        return DataType::Unknown;
    }

private:
    static std::unordered_map<std::string, DataType> type_cache;


    static bool isNumber(const std::string& expr) {
        static const std::regex number_regex(
                R"(^[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?$)"
        );
        return std::regex_match(expr, number_regex);
    }

    static bool isFunctionCall(const std::string& expr) {
        static const std::regex func_regex(
                R"(\b(sin|cos|transpose|log|exp|sqrt)\(.*\))",
                std::regex::icase
        );
        return std::regex_search(expr, func_regex);
    }

    static bool isExpression(const std::string& expr) {
        return expr.find_first_of("+-*/") != std::string::npos;
    }
};

#endif //MATHINTERPRETER_TYPEDETECTOR_HPP
