#ifndef FUNCTION_BODY_VALIDATOR_h
#define FUNCTION_BODY_VALIDATOR_h


#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <set>

#include "../exceptions/exceptions.h"
class FunctionBodyValidator final {
public:
    FunctionBodyValidator(const std::string& funcName, 
                         const std::vector<std::pair<std::string, std::string>>& args, 
                         const std::string& body, 
                         const std::string& returnType)
        : _func_name(funcName), _args(args), _body(body), _return_type(returnType) {}

    void validate() const {
        validateSyntax();
        validateVariableAccess();
        validateReturnType();
    }

private:
    std::string _func_name;
    std::vector<std::pair<std::string, std::string>> _args;
    std::string _body;
    std::string _return_type;

    void validateSyntax() const {
        // Проверка баланса фигурных скобок
        int braceCount = 0;
        for (char ch : _body) {
            if (ch == '{') braceCount++;
            if (ch == '}') braceCount--;
            if (braceCount < 0) {
                throw UnbalancedBracesError("Unexpected closing brace in function: " + _func_name);
            }
        }
        if (braceCount != 0) {
            throw UnbalancedBracesError("Unbalanced braces in function: " + _func_name);
        }

        // Проверка наличия точки с запятой в конце выражений
        std::regex stmtRegex(R"([^;}\n]+$)");
        if (std::regex_search(_body, stmtRegex)) {
            throw MissingSemicolonError("Missing semicolon in function: " + _func_name);
        }
    }

    void validateVariableAccess() const {
        std::regex varPattern(R"(\b\w+\b)");
        std::smatch matches;
        std::set<std::string> usedVariables;

        std::string::const_iterator searchStart(_body.cbegin());
        while (std::regex_search(searchStart, _body.cend(), matches, varPattern)) {
            usedVariables.insert(matches[0]);
            searchStart = matches.suffix().first;
        }

        for (const auto& var : usedVariables) {
            bool isDeclared = false;
            for (const auto& arg : _args) {
                if (var == arg.first) {
                    isDeclared = true;
                    break;
                }
            }
            if (!isDeclared && !isBuiltInKeyword(var)) {
                throw UndeclaredVariableError("Undeclared variable '" + var + "' in function: " + _func_name);
            }
        }
    }

    void validateReturnType() const {
        bool hasReturnStatement = _body.find("return") != std::string::npos;
        
        if (_return_type == "void") {
            if (hasReturnStatement && _body.find("return ") != std::string::npos) {
                throw InvalidReturnTypeError("Void function cannot return a value: " + _func_name);
            }
        } else {
            if (!hasReturnStatement) {
                throw InvalidReturnTypeError("Function must return a value of type '" + 
                    _return_type + "': " + _func_name);
            }
        }
    }

    bool isBuiltInKeyword(const std::string& word) const {
        static const std::set<std::string> keywords = {
            "num", "str", "bool", "void", "return", "if", "else", "while", "for",
            "break", "continue", "true", "false", "let", "fn"
        };
        return keywords.find(word) != keywords.end();
    }
};
#endif /* FUNCTION_BODY_VALIDATOR_h */