#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <any>

#include "base/abstractobject.h"
#include "types/matrix.hpp"
#include "types/variable.hpp"
#include "types/vector.hpp"
#include "types/rational.hpp"
#include "data/data.h"
#include "parsers/regexmanager.hpp"
#include "parsers/matrixparser.hpp"
#include "parsers/vectorparser.hpp"
#include "parsers/rationalparser.hpp"
#include "parsers/variableparser.hpp"
#include "function/base.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <memory>
#include <regex>
#include <utility>



template <typename T>
concept isValidType = std::is_same_v<T, Variable> || std::is_same_v<T, Vector> || std::is_same_v<T, Matrix> || std::is_same_v<T, Rational>;


class Interpreter final {
public:
    Interpreter()  {
        _M_variables.emplace("pi", std::make_shared<Variable>(3.14159265358979323846));
        _M_variables.emplace("e", std::make_shared<Variable>(2.71828182845904523536));

    };
    struct Exception : public std::exception
    {
        Exception() = default;
        explicit Exception(std::string err) : err(std::move(err)) {}

        [[nodiscard]] const char *what() const noexcept override
        {
            return err.empty() ? "Interpreter exception with err: Unknown error" : err.c_str();
        }

    private:
        std::string err;
    };

    struct InvalidCommand final : public Exception
    {
        InvalidCommand() : Exception("Invalid command") {}
        explicit InvalidCommand(const std::string &err) : Exception(err) {}
    };

    struct UnknownVariable final : public Exception
    {
        UnknownVariable() : Exception("Unknown variable") {}
        explicit UnknownVariable(const std::string &err) : Exception(err) {}
    };

    struct UnknownOperator final : public Exception
    {
        UnknownOperator() : Exception("Unknown operator") {}
        explicit UnknownOperator(const std::string &err) : Exception(err) {}
    };

    struct UnknownFunction final : public Exception
    {
        UnknownFunction() : Exception("Unknown function") {}
        explicit UnknownFunction(const std::string &err) : Exception(err) {}
    };

    struct InvalidExpression final : public Exception
    {
        InvalidExpression() : Exception("Invalid expression") {}
        explicit InvalidExpression(const std::string &err) : Exception(err) {}
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
            try
            {
                // line = "x = 2";
                if (_M_contains_any_symbol(line, OPERATORS))
                {
                    if (std::string op = _M_find_contains_symbol(line, OPERATORS); !op.empty())
                    {
                        _M_execute_command(line, op);
                    }
                    else
                    {
                        throw InvalidCommand("Operator is undefined");
                    }
                }
                else if(_M_contains_function_call(line)) {
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

    void processFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line))
        {
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
                else if(_M_contains_function_call(line)) {
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
    using _M_value_type = std::shared_ptr<AbstractObject>;

    std::unordered_map<std::string, _M_value_type> _M_variables {};

    template<isValidType T>
    std::shared_ptr<T> _M_parse_expression(const std::string &exp, const std::string &op)
    {

        std::smatch match;

        // Parse based on type
        if constexpr (std::is_same_v<T, Variable>)
        {
            const auto expression = _M_remove_whitespaces(exp);
            return _M_parse_variable_expression(expression, op);
        }
        else if constexpr (std::is_same_v<T, Vector>)
        {
            return _M_parse_vector_expression(exp, op);
        }
        else if constexpr (std::is_same_v<T, Matrix>)
        {
            return _M_parse_matrix_expression(exp, op);
        }
        else if constexpr (std::is_same_v<T, Rational>)
        {
            return _M_parse_rational_expression(exp, op);
        }

        throw InvalidExpression("Unsupported type for expression: " + exp);
    }

    void _M_function_execute(const std::string& command) {
        if(const bool isFunctionCalled = !_M_assignment_with_function(command); !isFunctionCalled) {
            std::istringstream stream(command);
            std::string variableName, equalsSign, expression;
            stream >> variableName >> equalsSign;
            std::getline(stream, expression);

            if (expression.empty()) {
                throw InvalidExpression("Expression cannot be empty");
            }

            _M_variables[variableName] = _M_function_expression(expression, equalsSign);
        }
        else {
            _M_print_object(_M_function_expression(command, ""));
        }
    }
    std::shared_ptr<AbstractObject> _M_function_expression(const std::string& expression, const std::string &op) {
        // Регулярное выражение для поиска вызова функции
        const std::regex funcRegex(R"((\w+)\((.*?)\))");

        if (std::smatch match; std::regex_match(expression, match, funcRegex)) {
            const std::string func_name = match[1];  // Имя функции (например, sin, cos)
            const std::string param_str = match[2];  // Параметр для функции

            const FunctionType func_type = get_function_type(func_name);

            if (_M_is_number(param_str)) {
                return _M_function_call(std::stod(param_str), func_type);
            }

            if (const auto var_it = _M_variables.find(param_str); var_it != _M_variables.end()) {
                const auto var = var_it->second;
                return _M_function_call(var, func_type);
            }
            throw std::invalid_argument("Variable not found: " + param_str);
        }
    };
    template<AllowedTypes _Tp>
    std::shared_ptr<AbstractObject> _M_function_call( _Tp args, const FunctionType func_type) {
        if (!std::is_arithmetic_v<_Tp>) {
            throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type));
        }
        switch (func_type) {
            case FunctionType::Sin:
                return std::make_shared<Variable>(std::sin(args));
            break;
            case FunctionType::Cos:
                return std::make_shared<Variable>(std::cos(args));
            break;
            default:
                throw std::invalid_argument("Unknown function: " + get_function_name(func_type));
        }
    }

    std::shared_ptr<AbstractObject> _M_function_call(const std::shared_ptr<AbstractObject>& args, const FunctionType func_type) {
        switch (func_type) {
            case FunctionType::Sin:
                if (const auto var = std::dynamic_pointer_cast<Variable>(args)) {
                    return std::make_shared<Variable>(_M_sin(*var));
                }else if (const auto vec = std::dynamic_pointer_cast<Vector>(args)) {
                    return std::make_shared<Vector>(_M_sin(*vec));
                }else if (const auto mat = std::dynamic_pointer_cast<Matrix>(args)) {
                    return std::make_shared<Matrix>(_M_sin(*mat));
                }else if (const auto rational = std::dynamic_pointer_cast<Rational>(args)) {
                    return std::make_shared<Rational>(_M_sin(*rational));
                }
            break;
            case FunctionType::Cos:
                if (const auto var = std::dynamic_pointer_cast<Variable>(args)) {
                    return std::make_shared<Variable>(_M_cos(*var));
                }else if (const auto vec = std::dynamic_pointer_cast<Vector>(args)) {
                    return std::make_shared<Vector>(_M_cos(*vec));
                }else if (const auto mat = std::dynamic_pointer_cast<Matrix>(args)) {
                    return std::make_shared<Matrix>(_M_cos(*mat));
                }else if (const auto rational = std::dynamic_pointer_cast<Rational>(args)) {
                    return std::make_shared<Rational>(_M_cos(*rational));
                }
            break;
            case FunctionType::Transpose:
                if (const auto mat = std::dynamic_pointer_cast<Matrix>(args)) {
                    return std::make_shared<Matrix>(mat->transpose());
                }
                else
                    throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type)+"\nOnly matrix support transpose");
            break;
            default:
                throw std::invalid_argument("Unknown function: " + get_function_name(func_type));
        }
    }

void _M_execute_command(const std::string &command, const std::string &op) {
        std::istringstream stream(command);
        std::string variableName, equalsSign, expression;

        stream >> variableName >> equalsSign;
        std::getline(stream, expression);

        if (expression.empty()) {
            throw InvalidExpression("Expression cannot be empty");
        }

        expression = _M_trim_leading_spaces(expression);



        if(_M_contains_function_call(expression)) {
            expression = _M_replace_variables(expression);
            _M_variables[variableName] = _M_function_expression(expression, equalsSign);
            return;
        }

        // Check if this is an operation between existing variables
        if (std::smatch match; std::regex_match(expression, match, std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))"))) {

            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];
            // Проверяем, являются ли оба операнда числами
            if (_M_is_number(lhs) && _M_is_number(rhs)) {
                // Преобразуем операнды в числа и вычисляем результат
                double lhsValue = std::stod(lhs);
                double rhsValue = std::stod(rhs);
                double result = _M_compute_operation(lhsValue, rhsValue, oper);

                // Сохраняем результат как переменную
                _M_variables[variableName] = std::make_shared<Variable>(Variable(result));
                return;
            }
            // Get the type of the operands
            auto lhsVar = _M_variables.find(lhs);
            auto rhsVar = _M_variables.find(rhs);

            if (lhsVar == _M_variables.end() || rhsVar == _M_variables.end()) {
                throw UnknownVariable("One or both operands not found");
            }

            // Check types and perform operation
            auto lhsPtr = lhsVar->second;
            auto rhsPtr = rhsVar->second;

            // Try to cast to each type and perform operation
            if (auto lhsVec = std::dynamic_pointer_cast<Vector>(lhsPtr)) {
                if (auto rhsVec = std::dynamic_pointer_cast<Vector>(rhsPtr)) {
                    _M_variables[variableName] = _M_parse_expression<Vector>(expression, oper);
                    return;
                }
            }
            else if (auto lhsMat = std::dynamic_pointer_cast<Matrix>(lhsPtr)) {
                if (auto rhsMat = std::dynamic_pointer_cast<Matrix>(rhsPtr)) {
                    _M_variables[variableName] = _M_parse_expression<Matrix>(expression, oper);
                    return;
                }
            }
            else if (auto lhsRat = std::dynamic_pointer_cast<Rational>(lhsPtr)) {
                if (auto rhsRat = std::dynamic_pointer_cast<Rational>(rhsPtr)) {
                    _M_variables[variableName] = _M_parse_expression<Rational>(expression, oper);
                    return;
                }
            }
            else if (auto lhsVar = std::dynamic_pointer_cast<Variable>(lhsPtr)) {
                if (auto rhsVar = std::dynamic_pointer_cast<Variable>(rhsPtr)) {
                    _M_variables[variableName] = _M_parse_expression<Variable>(expression, oper);
                    return;
                }
            }

            throw InvalidExpression("Incompatible types for operation");
        }
        else {
            expression = _M_replace_variables(expression);
            _M_creating_object(variableName, expression, op);
        }
    }

    void _M_creating_object(const std::string& name, const std::string& expression, const std::string& op) {

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

    Vector _M_parse_vector(const std::string &expression) {
        try {
            size_t index = 0;
            return VectorParser::parse(expression, index);
        } catch (const std::exception &e) {
            throw std::runtime_error("Ошибка при разборе матрицы: " + std::string(e.what()));
        }
    }

     std::string _M_remove_whitespaces(const std::string &str)
    {
        std::string result;
        ranges::remove_copy_if(str, std::back_inserter(result), ::isspace);
        return result;
    }

     Matrix _M_parse_matrix(const std::string &expression)
    {
        try {
            size_t index = 0;
            return MatrixParser::parse(expression, index);
        } catch (const std::exception &e) {
            throw std::runtime_error("Ошибка при разборе матрицы: " + std::string(e.what()));
        }
    }
    [[nodiscard]]  std::shared_ptr<Rational> _M_parse_rational_expression(const std::string &expression, const std::string &op) {
        std::smatch match;

        // Direct rational number assignment (e.g., "3/4")
        if (std::regex_match(expression, match, std::regex(R"((\d+)\/(\d+))"))) {
            const int numerator = std::stoi(match[1]);
            const int denominator = std::stoi(match[2]);
            if (denominator == 0) {
                throw InvalidExpression("Division by zero in rational number");
            }
            return std::make_shared<Rational>(Variable(numerator), Variable(denominator));
        }

        // Binary operations with rationals
        if (std::regex_match(expression, match, std::regex(R"((\w+|(\d+\/\d+))\s*([+\-*/])\s*(\w+|(\d+\/\d+)))"))) {
            const std::string lhs = match[1];
            const std::string oper = match[3];
            const std::string rhs = match[4];

            const auto lhsRat = _M_get_rational_operand(lhs);
            const auto rhsRat = _M_get_rational_operand(rhs);

            if (oper == "+") return std::make_shared<Rational>(*lhsRat + *rhsRat);
            if (oper == "-") return std::make_shared<Rational>(*lhsRat - *rhsRat);
            if (oper == "*") return std::make_shared<Rational>(*lhsRat * *rhsRat);
            if (oper == "/") {
                if (rhsRat->getDen() == 0 || rhsRat->getNum() == 0) {
                    throw InvalidExpression("Division by zero in rational operation");
                }
                return std::make_shared<Rational>(*lhsRat / *rhsRat);
            }
        }

        // Convert integer to rational
        if (std::regex_match(expression, match, std::regex(R"(\d+)"))) {
            const int value = std::stoi(expression);
            return std::make_shared<Rational>(Variable(value));
        }

        throw InvalidExpression("Invalid rational expression: " + expression);
    }

     std::shared_ptr<Rational> _M_get_rational_operand(const std::string &operand) {
        // Check if it's a direct rational number (e.g., "3/4")
        std::smatch match;
        if (std::regex_match(operand, match, std::regex(R"((\d+)\/(\d+))"))) {
            const int numerator = std::stoi(match[1]);
            const int denominator = std::stoi(match[2]);
            if (denominator == 0) {
                throw InvalidExpression("Division by zero in rational number");
            }
            return std::make_shared<Rational>(Variable(numerator), Variable(denominator));
        }

        // Check if it's an integer
        if (std::regex_match(operand, match, std::regex(R"(\d+)"))) {
            const int value = std::stoi(operand);
            return std::make_shared<Rational>(Variable(value));
        }

        // Check if it's a variable
        const auto it = _M_variables.find(operand);
        if (it == _M_variables.end()) {
            throw UnknownVariable("Variable not found: " + operand);
        }

        auto rat = std::dynamic_pointer_cast<Rational>(it->second);
        if (!rat) {
            throw InvalidExpression("Operand is not a rational number: " + operand);
        }

        return rat;
    }

     std::shared_ptr<Matrix> _M_parse_matrix_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Новое регулярное выражение для матрицы
        const std::regex matrixLiteral(R"(\[\s*(\[\s*\d+\s*(?:,\s*\d+\s*)*\]\s*(?:,\s*\[\s*\d+\s*(?:,\s*\d+\s*)*\]\s*)*)\])");


        // Matrix literal
        if (std::regex_match(expression, match, matrixLiteral))
        {
            return std::make_shared<Matrix>(_M_parse_matrix(expression));
        }
        // Matrix operations
        if (std::regex_match(expression, match, std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))")))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            const auto lhsMat = std::dynamic_pointer_cast<Matrix>(_M_variables[lhs]);
            const auto rhsMat = std::dynamic_pointer_cast<Matrix>(_M_variables[rhs]);

            if (!lhsMat || !rhsMat)
            {
                throw InvalidExpression("Invalid matrix operands");
            }

            if (oper == "+")
                return std::make_shared<Matrix>(*lhsMat + *rhsMat);
            if (oper == "-")
                return std::make_shared<Matrix>(*lhsMat - *rhsMat);
            if (oper == "*")
                return std::make_shared<Matrix>(*lhsMat * *rhsMat);
        }

        throw InvalidExpression("Invalid matrix expression: " + expression);
    }

     std::shared_ptr<Variable> _M_parse_variable_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Direct number assignment
        if (std::regex_match(expression, match, std::regex(R"(\d+)")))
        {
            Variable temp_var (std::stoi(expression));
            return std::make_shared<Variable>(temp_var);
        }

        // Binary operations
        if (std::regex_match(expression, match, std::regex(R"((\w+|d+)\s*([+\-*/])\s*(\w+|\d+))")))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            const auto lhsVal = _M_get_oerand_value(lhs);
            const auto rhsVal = _M_get_oerand_value(rhs);

            if (oper == "+")
                return std::make_shared<Variable>(*lhsVal + *rhsVal);
            if (oper == "-")
                return std::make_shared<Variable>(*lhsVal - *rhsVal);
            if (oper == "*")
                return std::make_shared<Variable>(*lhsVal * *rhsVal);
            if (oper == "/")
                return std::make_shared<Variable>(*lhsVal / *rhsVal);
        }

        throw InvalidExpression("Invalid variable expression: " + expression);
    }

     std::shared_ptr<Vector> _M_parse_vector_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Vector literal
        if (std::regex_match(expression, match, std::regex(R"(^\[\s*(\d+\s*,\s*)*\d+\s*\]$)")))
        {
            return std::make_shared<Vector>(_M_parse_vector(expression));
        }

        // Vector operations
        if (std::regex_match(expression, match, std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))")))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            const auto lhsVec = std::dynamic_pointer_cast<Vector>(_M_variables[lhs]);
            const auto rhsVec = std::dynamic_pointer_cast<Vector>(_M_variables[rhs]);

            if (!lhsVec || !rhsVec)
            {
                throw InvalidExpression("Invalid vector operands");
            }

            if (oper == "+")
                return std::make_shared<Vector>(*lhsVec + *rhsVec);
            if (oper == "-")
                return std::make_shared<Vector>(*lhsVec - *rhsVec);
            if (oper == "*")
                return std::make_shared<Vector>(*lhsVec * *rhsVec);
            if (oper == "/")
                return std::make_shared<Vector>(*lhsVec / *rhsVec);
        }

        throw InvalidExpression("Invalid vector expression: " + expression);
    }
     void _M_print_variable(const std::string &variableName)
    {
        const auto it = _M_variables.find(variableName);
        if (it == _M_variables.end())
        {
            throw UnknownVariable("Variable not found: " + variableName);
        }

        std::cout << *it->second << std::endl;
    }

    void _M_print_object(const std::shared_ptr<AbstractObject>& obj) {
        std::cout << *obj << std::endl;
    }
     bool _M_contains_any_symbol(const std::string &str, const std::string &symbols)
    {
        std::ranges::any_of(str, [&symbols](const char ch) {
            return ch != ' ' && symbols.find(ch) != std::string::npos;
        });
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
    [[nodiscard]]  bool _M_is_vector_expression(const std::string &expr) {
        size_t index = 0;
        while (index < expr.size() && isspace(expr[index])) ++index;

        if (expr[index] == '[' && index + 1 < expr.size() && expr[index + 1] == '[') {
            return false;  // Это матрица
        }

        return VectorParser::search(expr);
    }


    [[nodiscard]]  bool _M_is_matrix_expression(const std::string &expr) {
        size_t index = 0;
        while (index < expr.size() && isspace(expr[index])) ++index;

        // Проверяем, начинается ли строка с '['
        if (expr[index] == '[' && (index + 1 == expr.size() || expr[index + 1] != '[')) {
            return false;  // Это вектор
        }
        return MatrixParser::search(expr);
    }

    [[nodiscard]]  bool _M_is_rational_expression(const std::string &expr) {
        return RationalParser::search(expr);
    }

    static std::string _M_trim_leading_spaces(const std::string& input) {
        const size_t start = input.find_first_not_of(' ');
        return (start == std::string::npos) ? "" : input.substr(start);
    }

     std::shared_ptr<Variable> _M_get_oerand_value(const std::string &operand)
    {
        if (std::regex_match(operand, std::regex(R"(\d+)")))
        {
            return std::make_shared<Variable>(std::stoi(operand));
        }

        const auto it = _M_variables.find(operand);
        if (it == _M_variables.end())
        {
            throw UnknownVariable("Variable not found: " + operand);
        }

        auto var = std::dynamic_pointer_cast<Variable>(it->second);
        if (!var)
        {
            throw InvalidExpression("Operand is not a variable: " + operand);
        }

        return var;
    }
    bool _M_is_number(const std::string& s) {
        const std::regex numberRegex(R"(^[-+]?[0-9]*\.?[0-9]+$)");
        return std::regex_match(s, numberRegex);
    }
    // Замена переменных их значениями
    std::string _M_replace_variables(const std::string& expression) {
        bool containsVariables = false;
        for (const auto& [name, value] : _M_variables) {
            if (const std::string varPattern = R"(\b)" + name + R"(\b)"; std::regex_search(expression, std::regex(varPattern))) {
                containsVariables = true;
                break;
            }
        }

        if (!containsVariables) {
            return expression;
        }

        std::string result = expression;
        for (const auto& [name, value] : _M_variables) {
            const std::string varName = name;
            const std::string varValue = value->toString();
            const std::string varPattern = R"(\b)" + varName + R"(\b)";
            result = std::regex_replace(result, std::regex(varPattern), varValue);
        }
        return result;
    }

    template <typename T>
    T _M_compute_operation(T lhs, T rhs, const std::string& oper) {
        if (oper == "+") return lhs + rhs;
        if (oper == "-") return lhs - rhs;
        if (oper == "*") return lhs * rhs;
        if (oper == "/") {
            if (rhs == 0) throw std::runtime_error("Division by zero");
            return lhs / rhs;
        }
        throw std::invalid_argument("Unsupported operator: " + oper);
    }
    static bool _M_contains_function_call(const std::string& expression) {
        size_t i = 0;
        while (i < expression.size()) {
            // Пропускаем пробелы
            while (i < expression.size() && std::isspace(expression[i])) {
                ++i;
            }

            // Проверяем на функции в множестве
            for (const auto& func : functions) {
                if (expression.substr(i, func.size()) == func) {
                    i += func.size(); // Пропускаем имя функции
                    while (i < expression.size() && std::isspace(expression[i])) {
                        ++i;
                    }
                    if (i < expression.size() && expression[i] == '(') {
                        return true; // Нашли вызов функции
                    }
                }
            }

            ++i; // Переходим к следующему символу
        }
        return false;
    }
    static bool _M_assignment_with_function(const std::string& expression) {
        // Множество всех поддерживаемых функций
        static const std::unordered_set<std::string> functions = {"sin", "cos", "transpose", "tan", "log", "exp", "sqrt"};

        size_t i = 0;
        while (i < expression.size()) {
            // Пропускаем пробелы
            while (i < expression.size() && std::isspace(expression[i])) {
                ++i;
            }

            // Проверяем на присваивание (переменная = функция)
            size_t start = i;
            while (i < expression.size() && std::isalnum(expression[i])) {
                ++i; // Ищем имя переменной
            }

            std::string lhs = expression.substr(start, i - start); // Получаем переменную

            // Пропускаем возможные пробелы и символ '='
            while (i < expression.size() && std::isspace(expression[i])) {
                ++i;
            }
            if (i < expression.size() && expression[i] == '=') {
                ++i; // Пропускаем '='

                while (i < expression.size() && std::isspace(expression[i])) {
                    ++i;
                }

                // Проверяем наличие функции (sin, cos, transpose)
                for (const auto& func : functions) {
                    if (expression.substr(i, func.size()) == func) {
                        i += func.size(); // Пропускаем имя функции
                        while (i < expression.size() && std::isspace(expression[i])) {
                            ++i;
                        }
                        if (i < expression.size() && expression[i] == '(') {
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
