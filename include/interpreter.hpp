#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <memory>
#include <regex>
#include <utility>

#include "utils.h++"
#include "data/data.h"
#include "base/abstractobject.h"
#include "exceptions/core.h"

#include "types/matrix.hpp"
#include "types/variable.hpp"
#include "types/vector.hpp"
#include "types/rational.hpp"

#include "parsers/regexmanager.hpp"
#include "parsers/matrixparser.hpp"
#include "parsers/vectorparser.hpp"
#include "parsers/rationalparser.hpp"
#include "parsers/variableparser.hpp"
#include "parsers/expressionparser.hpp"

#include "function/base.hpp"
#include "function/binaryexecuter.hpp"
class Interpreter final
{
public:
    Interpreter() 
    : _M_expression_parser()
    , _M_binary_executer()
    {
        append_(_M_variables, "pi", make_variable_ptr(3.14159265358979323846));
        append_(_M_variables, "e",  make_variable_ptr(2.71828182845904523536));

        append_(_M_regexes, "MatrixLiteral",        std::regex(R"(\[\s*(\[\s*\d+\s*(?:,\s*\d+\s*)*\]\s*(?:,\s*\[\s*\d+\s*(?:,\s*\d+\s*)*\]\s*)*)\])"));
        append_(_M_regexes, "VectorLiteral",        std::regex(R"(^\[\s*(\d+\s*,\s*)*\d+\s*\]$)"));
        append_(_M_regexes, "RationalLiteral",      std::regex(R"((\d+\/\d+))"));
        append_(_M_regexes, "VariableLiteral",      std::regex(R"(\d+)"));
        append_(_M_regexes, "VectorOperation",      std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))"));
        append_(_M_regexes, "MatrixOperation",      std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))"));
        append_(_M_regexes, "RationalOperation",    std::regex(R"((\w+|(\d+\/\d+))\s*([+\-*/])\s*(\w+|(\d+\/\d+)))"));
        append_(_M_regexes, "VariableOperation",    std::regex(R"((\w+|d+)\s*([+\-*/])\s*(\w+|\d+))"));
        append_(_M_regexes, "functionLiteral",      std::regex(R"((\w+)\((.*?)\))"));
    };

    void processConsole()
    {
        std::string line;
        std::cout << "Math Interpreter. Enter commands or 'exit' to quit." << std::endl;
        while (true)
        {
            std::cout << ">>> ";
            std::getline(std::cin, line);
            if (line == "exit")
                break;
            if (!_M_validator.validate(line)) {
                    _M_validator.printErrors();
                    continue;
            }
            try
            {
                // line = "x = 2";
                if (_M_contains_any_symbol(line, OPERATORS))
                {
                    if (std::string op = _M_find_contains_symbol(line, OPERATORS); !op.empty())
                        _M_execute_command(line, op);
                    else
                        throw InvalidCommand("Operator is undefined");
                }
                else if (_M_contains_function_call(line))
                    _M_function_execute(line);
                else
                    _M_print_variable(line);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    void processFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        bool inBlockComment = false;
        std::string line;
        while (std::getline(file, line))
        {
            if (line.find("//") == 0 || line.find("#") == 0) {
                continue;
            }

            // Пропускаем строки, которые содержат блочные комментарии /* ... */
            size_t startComment = line.find("/*");
            size_t endComment = line.find("*/");

            if (startComment != std::string::npos) {
                inBlockComment = true;
            }

            if (inBlockComment) {
                if (endComment != std::string::npos) {
                    inBlockComment = false;
                    line = line.substr(endComment + 2); // Удаляем комментарий и продолжаем обработку строки
                } else {
                    continue; // Пропускаем строку, если она внутри блочного комментария
                }
            }

            if (!_M_validator.validate(line)) {
                    _M_validator.printErrors();
                    continue;
            }
            
            if(line.find("//") == std::string::npos)
            try
            {
                if (_M_contains_any_symbol(line, OPERATORS))
                {
                    if (std::string op = _M_find_contains_symbol(line, OPERATORS); !op.empty())
                    {
                        _M_execute_command(line, op);
                    }
                    else
                    {
                        _M_print_variable(line);
                    }
                }
                else if (_M_contains_function_call(line))
                {
                    _M_function_execute(line);
                }
                else
                {
                    _M_print_variable(line);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

private:
    std::unordered_map<std::string, std::regex> _M_regexes;

    std::unordered_map<std::string, value_type> _M_variables{};
    ExpressionEvaluator _M_expression_parser;
    BinaryExecute _M_binary_executer;
    StringValidator _M_validator;
    // Generic expression parsing
    template <AllowedType T>
    value_type _M_parse_expression(
            const std::string& exp,
            const std::string& op
    ) {
        if constexpr (std::is_same_v<T, Variable>) {
            return _M_parse_variable_expression(exp, op);
        } else if constexpr (std::is_same_v<T, Vector>) {
            return _M_parse_vector_expression(exp, op);
        } else if constexpr (std::is_same_v<T, Matrix>) {
            return _M_parse_matrix_expression(exp, op);
        } else if constexpr (std::is_same_v<T, Rational>) {
            return _M_parse_rational_expression(exp, op);
        }
        throw InvalidExpression("Unsupported type for expression: " + exp);
    }

    value_type 
    _M_function_expression(const std::string &expression, const std::string &op)
    {
        if (std::smatch match; std::regex_match(expression, match, _M_regexes.find("functionLiteral")->second))
        {
            const std::string func_name = match[1]; // Имя функции (например, sin, cos)
            const std::string param_str = match[2]; // Параметр для функции

            const FunctionType func_type = get_function_type(func_name);

            if (_M_is_number(param_str))
            {
                return _M_function_call(std::stod(param_str), func_type);
            }

            if (const auto var_it = _M_variables.find(param_str); var_it != _M_variables.end())
            {
                const auto var = var_it->second;
                return _M_function_call(var, func_type);
            }
            throw std::invalid_argument("Variable not found: " + param_str);
        }
    };

    template <AllowedTypes _Tp>
    value_type 
    _M_function_call(_Tp args, const FunctionType func_type)
    {
        if (!std::is_arithmetic_v<_Tp>)
        {
            throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type));
        }
        switch (func_type)
        {
        case FunctionType::Sin:
            return make_variable_ptr(std::sin(args));
            break;
        case FunctionType::Cos:
            return make_variable_ptr(std::cos(args));
            break;
        case FunctionType::CreateRat:
        {
            Variable var(args);
            return make_rational_ptr(_M_create_rat(var));
            break;
        }
        default:
            throw std::invalid_argument("Unknown function: " + get_function_name(func_type));
        }
    }

    value_type 
    _M_function_call(const value_type &args, const FunctionType func_type)
    {
        switch (func_type)
        {
        case FunctionType::Sin:
            if (const auto var = std::dynamic_pointer_cast<Variable>(args))
            {
                return make_variable_ptr(_M_sin(*var));
            }
            else if (const auto vec = std::dynamic_pointer_cast<Vector>(args))
            {
                return make_vector_ptr(_M_sin(*vec));
            }
            else if (const auto mat = std::dynamic_pointer_cast<Matrix>(args))
            {
                return make_matrix_ptr(_M_sin(*mat));
            }
            else if (const auto rational = std::dynamic_pointer_cast<Rational>(args))
            {
                return make_rational_ptr(_M_sin(*rational));
            }
            break;
        case FunctionType::Cos:
            if (const auto var = std::dynamic_pointer_cast<Variable>(args))
            {
                return make_variable_ptr(_M_cos(*var));
            }
            else if (const auto vec = std::dynamic_pointer_cast<Vector>(args))
            {
                return make_vector_ptr(_M_cos(*vec));
            }
            else if (const auto mat = std::dynamic_pointer_cast<Matrix>(args))
            {
                return make_matrix_ptr(_M_cos(*mat));
            }
            else if (const auto rational = std::dynamic_pointer_cast<Rational>(args))
            {
                return make_rational_ptr(_M_cos(*rational));
            }
            break;
        case FunctionType::CreateRat:
            if (auto x = std::dynamic_pointer_cast<Variable>(args))
            {
                return make_rational_ptr(_M_create_rat(*x));
            }
            else
                throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type) + "\nOnly matrix support transpose");
        case FunctionType::Transpose:
            if (const auto mat = std::dynamic_pointer_cast<Matrix>(args))
            {
                return make_matrix_ptr(mat->transpose());
            }
            else
                throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type) + "\nOnly matrix support transpose");
            break;
        default:
            throw std::invalid_argument("Unknown function: " + get_function_name(func_type));
        }
    }

    void 
    _M_function_execute(const std::string &command)
    {
        if (const bool isFunctionCalled = !_M_assignment_with_function(command); !isFunctionCalled)
        {
            std::istringstream stream(command);
            std::string variableName, equalsSign, expression;
            stream >> variableName >> equalsSign;
            std::getline(stream, expression);

            if (expression.empty())
            {
                throw InvalidExpression("Expression cannot be empty");
            }

            upload_(_M_variables, variableName, _M_function_expression(expression, equalsSign));
        }
        else
        {
            _M_print_object(_M_function_expression(command, ""));
        }
    }

    void 
    _M_execute_command(const std::string &command, const std::string &op)
    {
        std::istringstream stream(command);
        std::string variableName, equalsSign, expression;

        stream >> variableName >> equalsSign;
        std::getline(stream, expression);

        if (expression.empty())
        {
            throw InvalidExpression("Expression cannot be empty");
        }

        expression = _M_trim_leading_spaces(expression);

        if (_M_contains_function_call(expression))
        {
            expression = _M_binary_executer.replace_variables(expression, _M_variables);
            _M_variables[variableName] = _M_function_expression(expression, equalsSign);
            return;
        }

        if (!equalsSign.empty() && equalsSign == "=" && !_M_contains_math_evaluate_expression(expression))
        {
            // expression = _M_binary_executer.replace_variables(expression);
            _M_creating_object(variableName, expression, op);
            return;
        }

        // Check if this is an operation between existing variables
        if (_M_contains_math_evaluate_expression(expression))
        {
            expression = _M_binary_executer.replace_variables(expression, _M_variables);
            _M_variables[variableName] = _M_binary_executer.calculate(expression);
        }
    }

    void
    _M_creating_object(const std::string &name, const std::string &expression, const std::string &op)
    {
        if (_M_is_vector_expression(expression))
        {
            _M_variables[name] = _M_parse_expression<Vector>(expression, op);
        }
        else if (_M_is_matrix_expression(expression))
        {
            _M_variables[name] = _M_parse_expression<Matrix>(expression, op);
        }
        else if (_M_is_rational_expression(expression))
        {
            _M_variables[name] = _M_parse_expression<Rational>(expression, op);
        }
        else
        {
            _M_variables[name] = _M_parse_expression<Variable>(expression, op);
        }
    }

    Vector _M_parse_vector(const std::string &expression)
    {
        try
        {
            size_t index = 0;
            return VectorParser::parse(expression, index);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Ошибка при разборе матрицы: " + std::string(e.what()));
        }
    }

    std::string _M_remove_whitespaces(const std::string &str)
    {
        std::string result;
        std::for_each(str.begin(), str.end(), [&](char c)
                      {
                if (!std::isspace(c)) {
                    result.push_back(c);
                } });

        return result;
    }

    Matrix _M_parse_matrix(const std::string &expression)
    {
        try
        {
            size_t index = 0;
            return MatrixParser::parse(expression, index);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Ошибка при разборе матрицы: " + std::string(e.what()));
        }
    }

    [[nodiscard]] rational_ptr 
    _M_parse_rational_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Direct rational number assignment (e.g., "3/4")
        if (std::regex_match(expression, match, _M_regexes.find("RationalLiteral")->second))
        {
            const int numerator = std::stoi(match[1]);
            const int denominator = std::stoi(match[2]);
            if (denominator == 0)
            {
                throw InvalidExpression("Division by zero in rational number");
            }
            return make_rational_ptr(
                    Rational(Variable(numerator),
                            Variable(denominator)));
        }

        // Binary operations with rationals
        if (std::regex_match(expression, match, _M_regexes.find("RationalOperation")->second))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            // Если левый операнд число, а правый переменная
            if (_M_is_number(lhs) && _M_variables.find(rhs) != _M_variables.end())
            {

                auto rhsVar = _M_variables.find(rhs);
                if (rhsVar == _M_variables.end())
                {
                    throw UnknownVariable("Right operand not found");
                };
                auto &rhsPtr = rhsVar->second;
                return _M_binary_executer.calculate<rational_ptr>(lhs, rhsPtr, expression, oper);
            }

            // Если левый операнд переменная, а правый число
            if (_M_variables.find(lhs) != _M_variables.end() && _M_is_number(rhs))
            {
                auto lhsVar = _M_variables.find(lhs);
                if (lhsVar == _M_variables.end())
                {
                    throw UnknownVariable("Right operand not found");
                };
                auto &lhsPtr = lhsVar->second;
                return _M_binary_executer.calculate<rational_ptr>(lhsPtr, rhs, expression, oper);
            }
            // Get the type of the operands
            auto lhsVar = _M_variables.find(lhs);
            auto rhsVar = _M_variables.find(rhs);

            if (lhsVar == _M_variables.end() || rhsVar == _M_variables.end())
            {
                throw UnknownVariable("One or both operands not found");
            }

            // Check types and perform operation
            auto &lhsPtr = lhsVar->second;
            auto &rhsPtr = rhsVar->second;

            return _M_binary_executer.calculate<rational_ptr>(lhsPtr, rhsPtr, expression, op);
        }

        throw InvalidExpression("Invalid rational expression: " + expression);
    }

    matrix_ptr _M_parse_matrix_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Matrix operations
        if (std::regex_match(expression, match, _M_regexes.find("MatrixOperation")->second))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            // Если левый операнд число, а правый переменная
            if (_M_is_number(lhs) && _M_variables.find(rhs) != _M_variables.end())
            {

                auto rhsVar = _M_variables.find(rhs);
                if (rhsVar == _M_variables.end())
                {
                    throw UnknownVariable("Right operand not found");
                };
                auto &rhsPtr = rhsVar->second;
                return _M_binary_executer.calculate<matrix_ptr>(lhs, rhsPtr, expression, oper);
            }

            // Если левый операнд переменная, а правый число
            if (_M_variables.find(lhs) != _M_variables.end() && _M_is_number(rhs))
            {
                auto lhsVar = _M_variables.find(lhs);
                if (lhsVar == _M_variables.end())
                {
                    throw UnknownVariable("Right operand not found");
                };
                auto &lhsPtr = lhsVar->second;
                return _M_binary_executer.calculate<matrix_ptr>(lhsPtr, rhs, expression, oper);
            }
            // Get the type of the operands
            auto lhsVar = _M_variables.find(lhs);
            auto rhsVar = _M_variables.find(rhs);

            if (lhsVar == _M_variables.end() || rhsVar == _M_variables.end())
            {
                throw UnknownVariable("One or both operands not found");
            }

            // Check types and perform operation
            auto &lhsPtr = lhsVar->second;
            auto &rhsPtr = rhsVar->second;

            return _M_binary_executer.calculate<matrix_ptr>(lhsPtr, rhsPtr, expression, op);
        }
        // Matrix literal
        if (std::regex_match(expression, match,_M_regexes.find("MatrixLiteral")->second) )
        {
            return make_matrix_ptr(_M_parse_matrix(expression));
        }
        throw InvalidExpression("Invalid matrix expression: " + expression);
    }

    vector_ptr _M_parse_vector_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Binary operations
        if (std::regex_match(expression, match, _M_regexes.find("VectorOperation")->second))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            // Если левый операнд число, а правый переменная
            if (_M_is_number(lhs) && _M_variables.find(rhs) != _M_variables.end())
            {
                auto rhsVar = _M_variables.find(rhs);
                if (rhsVar == _M_variables.end())
                {
                    throw UnknownVariable("Right operand not found");
                };
                auto &rhsPtr = rhsVar->second;
                return _M_binary_executer.calculate<vector_ptr>(lhs, rhsPtr, expression, oper);
            }

            // Если левый операнд переменная, а правый число
            if (_M_variables.find(lhs) != _M_variables.end() && _M_is_number(rhs))
            {
                auto lhsVar = _M_variables.find(lhs);
                if (lhsVar == _M_variables.end())
                {
                    throw UnknownVariable("Right operand not found");
                };
                auto &lhsPtr = lhsVar->second;
                return _M_binary_executer.calculate<vector_ptr>(lhsPtr, rhs, expression, oper);
            }
            // Get the type of the operands
            auto lhsVar = _M_variables.find(lhs);
            auto rhsVar = _M_variables.find(rhs);

            if (lhsVar == _M_variables.end() || rhsVar == _M_variables.end())
            {
                throw UnknownVariable("One or both operands not found");
            }

            // Check types and perform operation
            auto &lhsPtr = lhsVar->second;
            auto &rhsPtr = rhsVar->second;

            return _M_binary_executer.calculate<vector_ptr>(lhsPtr, rhsPtr, expression, op);
        }

        // Direct number assignment
        if (std::regex_match(expression, match, _M_regexes.find("VectorLiteral")->second))
        {
            return make_vector_ptr(Vector(_M_parse_vector(expression)));
        }

        throw InvalidExpression("Invalid variable expression: " + expression);
    }
    variable_ptr _M_parse_variable_expression(
            const std::string& expression,
            const std::string& op
    ) {
        std::smatch match;

        // Direct number assignment
        if (std::regex_match(expression, match, _M_regexes.find("VariableLiteral")->second)) {
            return make_variable_ptr(Variable(std::stoi(expression)));
        }

        const std::string lhs = match[1];
        const std::string oper = match[2];
        const std::string rhs = match[3];

        // Left operand is number, right is variable
        if (_M_is_number(lhs) && _M_variables.find(rhs) != _M_variables.end()) {
            auto rhsVar = _M_variables.find(rhs);
            return _M_binary_executer.calculate<variable_ptr>(lhs, rhsVar->second, expression, oper);
        }

        // Left operand is variable, right is number
        if (_M_variables.find(lhs) != _M_variables.end() && _M_is_number(rhs)) {
            auto lhsVar = _M_variables.find(lhs);
            return _M_binary_executer.calculate<variable_ptr>(lhsVar->second, rhs, expression, oper);
        }

        // Both operands are variables
        auto lhsVar = _M_variables.find(lhs);
        auto rhsVar = _M_variables.find(rhs);

        if (lhsVar == _M_variables.end() || rhsVar == _M_variables.end()) {
            throw UnknownVariable("One or both operands not found");
        }

        return _M_binary_executer.calculate<variable_ptr>(
                lhsVar->second, rhsVar->second, expression, op
        );
        

        throw InvalidExpression("Invalid variable expression: " + expression);
    }
    void _M_print_variable(const std::string &variableName)
    {
        if (variableName.empty())
        {
            return;
        }

        const auto it = _M_variables.find(variableName);
        if (it == _M_variables.end())
        {
            throw UnknownVariable("Variable not found: " + variableName);
        }

        std::cout << *it->second << std::endl;
    }

    void _M_print_object(const value_type &obj)
    {
        std::cout << *obj << std::endl;
    }

    bool _M_contains_any_symbol(const std::string &str, const std::string &symbols)
    {
        bool found = false;

        std::for_each(str.begin(), str.end(), [&](const char ch)
                      {
                if (ch != ' ' && symbols.find(ch) != std::string::npos) {
                    found = true;
                } });
        return found;
    }

    std::string _M_find_contains_symbol(const std::string &str, const std::string &symbols)
    {
        for (const char ch : symbols)
        {
            if (ch != ' ' && str.find(ch) != std::string::npos)
            {
                return {1, ch};
            }
        }
        return "";
    }

    // Helper methods to determine expression type
    [[nodiscard]] bool _M_is_vector_expression(const std::string &expr)
    {
        auto expression = _M_binary_executer.replace_variables(expr, _M_variables);
        size_t index = 0;
        while (index < expression.size() && isspace(expression[index]))
            ++index;

        if (expression[index] == '[' && index + 1 < expression.size() && expression[index + 1] == '[')
        {
            return false; // Это матрица
        }


        return VectorParser::search(expression);
    }

    [[nodiscard]] bool _M_is_matrix_expression(const std::string &expr)
    {
        auto expression = _M_binary_executer.replace_variables(expr, _M_variables);
        size_t index = 0;
        while (index < expression.size() && isspace(expression[index]))
            ++index;

        // Проверяем, начинается ли строка с '['
        if (expression[index] == '[' && (index + 1 == expression.size() || expression[index + 1] != '['))
        {
            return false; // Это вектор
        }

        return MatrixParser::search(expression);
    }

    [[nodiscard]] bool _M_is_variable_expression(const std::string& expr){
        auto expression = _M_binary_executer.replace_variables(expr, _M_variables);
        return std::regex_match(expression, _M_regexes.find("VariableLiteral")->second);
    }
    [[nodiscard]] bool _M_is_rational_expression(const std::string &expr)
    {
        auto expression = _M_binary_executer.replace_variables(expr, _M_variables);
        return RationalParser::search(expression);
    }

    static std::string _M_trim_leading_spaces(const std::string &input)
    {
        const size_t start = input.find_first_not_of(' ');
        return (start == std::string::npos) ? "" : input.substr(start);
    }

    bool _M_is_number(const std::string &s)
    {
        const std::regex numberRegex(R"(^[-+]?[0-9]*\.?[0-9]+$)");
        return std::regex_match(s, numberRegex);
    }



    template <typename T>
    T _M_compute_operation(T lhs, T rhs, const std::string &oper)
    {
        if (oper == "+")
            return lhs + rhs;
        if (oper == "-")
            return lhs - rhs;
        if (oper == "*")
            return lhs * rhs;
        if (oper == "/")
        {
            if (rhs == 0)
                throw std::runtime_error("Division by zero");
            return lhs / rhs;
        }
        throw std::invalid_argument("Unsupported operator: " + oper);
    }

    bool _M_contains_math_evaluate_expression(const std::string &expression)
    {
        std::stack<char> parentheses; // Стек для проверки сбалансированности скобок
        bool lastWasOperator = true;  // Флаг для отслеживания, был ли предыдущий символ оператором
        bool hasOperator = false;     // Флаг, который проверяет, есть ли оператор в выражении

        // Пропускаем пробелы
        for (size_t i = 0; i < expression.length(); ++i)
        {
            char c = expression[i];

            if (std::isalpha(c))
            {
                auto var = _M_variables.find(std::string(1, c));
                if (var == _M_variables.end())
                    return false;
                if (auto varPtr = dynamic_pointer_cast<Variable>(var->second); varPtr == nullptr)
                    return false;
                continue;
            }

            if (c == ' ')
            {
                continue;
            }

            // Если это цифра или буква, то это допустимо
            if (std::isdigit(c))
            {
                lastWasOperator = false;
            }
            // Если это оператор, он должен идти после операнда
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                if (lastWasOperator)
                { // Два оператора подряд - ошибка
                    return false;
                }
                hasOperator = true; // Установим флаг, если оператор найден
                lastWasOperator = true;
            }
            // Если это открывающая скобка
            else if (c == '(')
            {
                parentheses.push(c);
                lastWasOperator = true;
            }
            // Если это закрывающая скобка
            else if (c == ')')
            {
                if (parentheses.empty() || lastWasOperator)
                { // Закрывающая скобка без соответствующей открывающей
                    return false;
                }
                parentheses.pop();
                lastWasOperator = false;
            }
            else
            { // Недопустимый символ
                return false;
            }
        }
        // Если в конце остались открытые скобки или выражение заканчивается на оператор
        return !lastWasOperator && parentheses.empty() && hasOperator;
    }

    static bool _M_contains_function_call(const std::string &expression)
    {
        size_t i = 0;
        while (i < expression.size())
        {
            // Пропускаем пробелы
            while (i < expression.size() && std::isspace(expression[i]))
            {
                ++i;
            }

            // Проверяем на функции в множестве
            for (const auto &func : functions)
            {
                if (expression.substr(i, func.size()) == func)
                {
                    i += func.size(); // Пропускаем имя функции
                    while (i < expression.size() && std::isspace(expression[i]))
                    {
                        ++i;
                    }
                    if (i < expression.size() && expression[i] == '(')
                    {
                        return true; // Нашли вызов функции
                    }
                }
            }

            ++i; // Переходим к следующему символу
        }
        return false;
    }
    static bool _M_assignment_with_function(const std::string &expression)
    {
        // Множество всех поддерживаемых функций
        static const std::unordered_set<std::string> functions = {"sin", "cos", "transpose", "tan", "log", "exp", "sqrt"};

        size_t i = 0;
        while (i < expression.size())
        {
            // Пропускаем пробелы
            while (i < expression.size() && std::isspace(expression[i]))
            {
                ++i;
            }

            // Проверяем на присваивание (переменная = функция)
            size_t start = i;
            while (i < expression.size() && std::isalnum(expression[i]))
            {
                ++i; // Ищем имя переменной
            }

            std::string lhs = expression.substr(start, i - start); // Получаем переменную

            // Пропускаем возможные пробелы и символ '='
            while (i < expression.size() && std::isspace(expression[i]))
            {
                ++i;
            }
            if (i < expression.size() && expression[i] == '=')
            {
                ++i; // Пропускаем '='

                while (i < expression.size() && std::isspace(expression[i]))
                {
                    ++i;
                }

                // Проверяем наличие функции (sin, cos, transpose)
                for (const auto &func : functions)
                {
                    if (expression.substr(i, func.size()) == func)
                    {
                        i += func.size(); // Пропускаем имя функции
                        while (i < expression.size() && std::isspace(expression[i]))
                        {
                            ++i;
                        }
                        if (i < expression.size() && expression[i] == '(')
                        {
                            return true; // Нашли присваивание с функцией
                        }
                    }
                }
            }

            ++i; // Переходим к следующему символу
        }
        return false;
    }
};
#endif /* INTERPRETER_H */
