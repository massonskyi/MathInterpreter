#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <any>

#include "abstractobject.h"
#include "matrix.hpp"
#include "variable.hpp"
#include "vector.hpp"
#include "rational.hpp"
#include "utils.hpp"
#include "data.h"

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


class Interpreter final
{
public:
    Interpreter()  {
        variables.emplace("pi", std::make_shared<Variable>(3.14159265358979323846));
        variables.emplace("e", std::make_shared<Variable>(2.71828182845904523536));

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
                if (containsAnySymbol(line, OPERATORS))
                {
                    if (std::string op = findContainsSymbol(line, OPERATORS); !op.empty())
                    {
                        executeCommand(line, op);
                    }
                    else
                    {
                        throw InvalidCommand("Operator is undefined");
                    }
                }
                else
                {
                    printVariable(line);
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
                if (containsAnySymbol(line, OPERATORS))
                {
                    if (std::string op = findContainsSymbol(line, OPERATORS); !op.empty())
                    {
                        executeCommand(line, op);
                    }
                    else
                    {
                        printVariable(line);
                    }
                }
                else
                {
                    printVariable(line);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

private:
    using value_type = std::shared_ptr<AbstractObject>;
    std::unordered_map<std::string, value_type> variables {};

    template<isValidType T>
    std::shared_ptr<T> parseExpression(const std::string &exp, const std::string &op)
    {

        std::smatch match;

        // Parse based on type
        if constexpr (std::is_same_v<T, Variable>)
        {
            const auto expression = removeWhitespaces(exp);
            return parseVariableExpression(expression, op);
        }
        else if constexpr (std::is_same_v<T, Vector>)
        {
            return parseVectorExpression(exp, op);
        }
        else if constexpr (std::is_same_v<T, Matrix>)
        {
            return parseMatrixExpression(exp, op);
        }
        else if constexpr (std::is_same_v<T, Rational>)
        {
            return parseRationalExpression(exp, op);
        }

        throw InvalidExpression("Unsupported type for expression: " + exp);
    }

    template<isValidType T>
    T &getVariableFromVariant(AbstractObject &var, const std::string &varName)
    {
        if (auto value = dynamic_cast<T *>(&var); value != nullptr)
        {
            return *value;
        }
        else
        {
            throw std::runtime_error("Variable " + varName + " is not of the expected type.");
        }
    }

    void executeCommand(const std::string &command, const std::string &op)
    {
        std::istringstream stream(command);
        std::string variableName, equalsSign, expression;

        stream >> variableName >> equalsSign;
        std::getline(stream, expression);

        if (expression.empty())
        {
            throw InvalidExpression("Expression cannot be empty");
        }
        expression = trimLeadingSpaces(expression);
        // Determine the type based on the expression format
        if (isVectorExpression(expression))
        {
            variables[variableName] = parseExpression<Vector>(expression, op);
        }
        else if (isMatrixExpression(expression))
        {
            variables[variableName] = parseExpression<Matrix>(expression, op);
        }
        else if (isRationalExpression(expression))
        {
            variables[variableName] = parseExpression<Rational>(expression, op);
        }
        else
        {
            variables[variableName] = parseExpression<Variable>(expression, op);
        }
    }


    Vector parseVector(const std::string &expression) {
        Vector result{};

        // Регулярное выражение для извлечения чисел из строки вектора
        const std::regex vectorRegex(R"(\[\s*(\d+\s*(,\s*\d+\s*)*)\])");

        // Проверка совпадения строки с регулярным выражением
        if (std::smatch match; std::regex_match(expression, match, vectorRegex)) {
            const std::string numbersStr = match[1].str();

            // Убираем запятые и преобразуем строку в поток
            std::string sanitizedNumbers;
            std::regex_replace(std::back_inserter(sanitizedNumbers),
                               numbersStr.begin(), numbersStr.end(),
                               std::regex(","), " ");

            std::istringstream stream(sanitizedNumbers);

            // Копируем числа в вектор
            try {
                // Чтение чисел из потока и добавление их в вектор
                Variable num;
                while (stream >> num) {
                    result.push_back(num);
                }
            } catch (const std::exception &e) {
                throw std::runtime_error("Ошибка при разборе чисел: " + std::string(e.what()));
            }
        } else {
            throw std::runtime_error("Invalid vector expression: " + expression);
        }

        return result;
    }

     std::string removeWhitespaces(const std::string &str)
    {
        std::string result;
        ranges::remove_copy_if(str, std::back_inserter(result), ::isspace);
        return result;
    }
     Matrix parseMatrix(const std::string &expression)
    {
        Matrix result;

        // Регулярное выражение для извлечения чисел из строки матрицы
        std::regex matrixRegex(R"(\[\s*\[\s*(\d+(\s+\d+)*)\s*\](\s*\[\s*(\d+(\s+\d+)*)\s*\])*\s*\])");

        if (std::smatch match; std::regex_match(expression, match, matrixRegex))
        {
            std::string matrixStr = match[0].str();
            std::regex rowRegex(R"(\[\s*(\d+(\s+\d+)*)\s*\])");
            auto rows_begin = std::sregex_iterator(matrixStr.begin(), matrixStr.end(), rowRegex);
            auto rows_end = std::sregex_iterator();

            for (std::sregex_iterator i = rows_begin; i != rows_end; ++i)
            {
                const std::smatch &rowMatch = *i;
                std::string rowStr = rowMatch[1].str();
                std::istringstream stream(rowStr);
                Vector row;
                std::copy(std::istream_iterator<Variable>(stream),
                          std::istream_iterator<Variable>(),
                          std::back_inserter(row));
                result.push_back(row);
            }
        }
        else
        {
            throw std::runtime_error("Invalid matrix expression: " + expression);
        }

        return result;
    }
    [[nodiscard]]  std::shared_ptr<Rational> parseRationalExpression(const std::string &expression, const std::string &op) {
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

            const auto lhsRat = getRationalOperand(lhs);
            const auto rhsRat = getRationalOperand(rhs);

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

     std::shared_ptr<Rational> getRationalOperand(const std::string &operand) {
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
        const auto it = variables.find(operand);
        if (it == variables.end()) {
            throw UnknownVariable("Variable not found: " + operand);
        }

        auto rat = std::dynamic_pointer_cast<Rational>(it->second);
        if (!rat) {
            throw InvalidExpression("Operand is not a rational number: " + operand);
        }

        return rat;
    }

     std::shared_ptr<Matrix> parseMatrixExpression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Matrix literal
        if (std::regex_match(expression, match, std::regex(R"(\[\s*\[\s*\d+(\s+\d+)*\s*\](\s*\[\s*\d+(\s+\d+)*\s*\])*\s*\])")))
        {
            return std::make_shared<Matrix>(parseMatrix(expression));
        }

        // Matrix operations
        if (std::regex_match(expression, match, std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))")))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            const auto lhsMat = std::dynamic_pointer_cast<Matrix>(variables[lhs]);
            const auto rhsMat = std::dynamic_pointer_cast<Matrix>(variables[rhs]);

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

     std::shared_ptr<Variable> parseVariableExpression(const std::string &expression, const std::string &op)
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

            const auto lhsVal = getOperandValue(lhs);
            const auto rhsVal = getOperandValue(rhs);

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

     std::shared_ptr<Vector> parseVectorExpression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Vector literal
        if (std::regex_match(expression, match, std::regex(R"(^\[\s*(\d+\s*,\s*)*\d+\s*\]$)")))
        {
            return std::make_shared<Vector>(parseVector(expression));
        }

        // Vector operations
        if (std::regex_match(expression, match, std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))")))
        {
            const std::string lhs = match[1];
            const std::string oper = match[2];
            const std::string rhs = match[3];

            const auto lhsVec = std::dynamic_pointer_cast<Vector>(variables[lhs]);
            const auto rhsVec = std::dynamic_pointer_cast<Vector>(variables[rhs]);

            if (!lhsVec || !rhsVec)
            {
                throw InvalidExpression("Invalid vector operands");
            }

            if (oper == "+")
                return std::make_shared<Vector>(*lhsVec + *rhsVec);
            if (oper == "-")
                return std::make_shared<Vector>(*lhsVec - *rhsVec);
            // Add other vector operations as needed
        }

        throw InvalidExpression("Invalid vector expression: " + expression);
    }
     void printVariable(const std::string &variableName)
    {
        const auto it = variables.find(variableName);
        if (it == variables.end())
        {
            throw UnknownVariable("Variable not found: " + variableName);
        }

        std::cout << *it->second << std::endl;
    }

     bool containsAnySymbol(const std::string &str, const std::string &symbols)
    {
        for (const char ch : symbols)
        {
            if (ch != ' ' && str.find(ch) != std::string::npos)
            {
                return true;
            }
        }
        return false;
    }

     std::string findContainsSymbol(const std::string &str, const std::string &symbols)
    {
        for (const char ch : symbols)
        {
            if (ch != ' ' && str.find(ch) != std::string::npos)
            {
                return std::string(1, ch);
            }
        }
        return "";
    }

    // Helper methods to determine expression type
    [[nodiscard]]  bool isVectorExpression(const std::string &expr) {
        return std::regex_match(removeWhitespaces(expr), std::regex(R"(\[\d+(\s*,\s*\d+)*\])"));
    }

    [[nodiscard]]  bool isMatrixExpression(const std::string &expr) {
        return std::regex_match(removeWhitespaces(expr), std::regex(R"(\[\s*\[\d+(\s*,\s*\d+)*\](\s*,\s*\[\d+(\s*,\s*\d+)*\])*\])"));
    }

    [[nodiscard]]  bool isRationalExpression(const std::string &expr) {
        return std::regex_match(removeWhitespaces(expr), std::regex(R"(\d+\/\d+)"));
    }
    static std::string trimLeadingSpaces(const std::string& input) {
        // Найти первый символ, который не является пробелом
        const size_t start = input.find_first_not_of(' ');
        // Вернуть строку без начальных пробелов
        return (start == std::string::npos) ? "" : input.substr(start);
    }
     std::shared_ptr<Variable> getOperandValue(const std::string &operand)
    {
        if (std::regex_match(operand, std::regex(R"(\d+)")))
        {
            return std::make_shared<Variable>(std::stoi(operand));
        }

        const auto it = variables.find(operand);
        if (it == variables.end())
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
};
#endif /* INTERPRETER_H */
