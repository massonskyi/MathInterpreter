#ifndef BINARYEXECUTER_HPP_
#define BINARYEXECUTER_HPP_

#include <string>
#include <memory>
#include <regex>

#include "../utils.hxx"
#include "../types/matrix.hxx"
#include "../types/rational.hxx"
#include "../types/variable.hxx"
#include "../types/vector.hxx"

#include "../exceptions/exceptions.hxx"

#include "expressionparser.hxx"


using value_type = std::shared_ptr<AbstractObject>;
using vector_ptr = std::shared_ptr<Vector>;
using variable_ptr = std::shared_ptr<Variable>;
using matrix_ptr = std::shared_ptr<Matrix>;
using rational_ptr = std::shared_ptr<Rational>;

using stack_map = std::unordered_map<std::string, value_type>;
// Concept for allowed object types
template <typename T>
concept AllowedType = std::is_same_v<T, Vector> ||
                      std::is_same_v<T, Matrix> ||
                      std::is_same_v<T, Rational> ||
                      std::is_same_v<T, Variable>;

// Concept for allowed pointer types
template <typename T>
concept AllowedPtrType = std::is_same_v<T, std::shared_ptr<Vector>> ||
                         std::is_same_v<T, std::shared_ptr<Matrix>> ||
                         std::is_same_v<T, std::shared_ptr<Rational>> ||
                         std::is_same_v<T, std::shared_ptr<Variable>>;

/// @brief Class for executing binary operations
class BinaryExecute final
{
public:
    /// @brief Simple calculation method for only numbers and variables
    /// @tparam ReturnType This avalaible types are: Vector, Matrix, Rational, Variable
    /// @param lhs first operand
    /// @param rhsPtr second operand
    /// @param expression calculation expression for binary operation ( avalaible latter )
    /// @param oper operator
    /// @return result calculation
    value_type calculate(const std::string &expression, std::unordered_map<std::string, value_type>& variables)
    {

        auto x = _M_expression_parser.evaluate(expression, variables);
        return std::visit([](auto& res) -> value_type {
                using T = std::decay_t<decltype(res)>;
                if constexpr (std::is_same_v<T, double> || std::is_same_v<T, Variable>){
                    return make_object_ptr<T>(res);
                }
                else if constexpr (std::is_same_v<T, Vector>){
                    return make_object_ptr<T>(res);
                } else if constexpr (std::is_same_v<T, Matrix>){
                    return make_object_ptr<T>(res);
                }else if constexpr (std::is_same_v<T, Rational>){
                    return make_object_ptr<T>(res);
                }
        }, x);
    }

    /// @brief This method replace variables in the expression with their values 
    /// @param expression Expression to replace variables in 
    /// @param variables Stack of variables 
    /// @return Replaced expression
    std::string replace_variables(const std::string &expression, const stack_map& variables)
    {
        bool containsVariables = false;
        for (const auto &[name, value] : variables)
        {
            if (const std::string varPattern = R"(\b)" + name + R"(\b)"; std::regex_search(expression, std::regex(varPattern)))
            {
                containsVariables = true;
                break;
            }
        }

        if (!containsVariables)
        {
            return expression;
        }

        std::string result = expression;
        for (const auto &[name, value] : variables)
        {
            const std::string varName = name;
            const std::string varValue = value->toString();
            const std::string varPattern = R"(\b)" + varName + R"(\b)";
            result = std::regex_replace(result, std::regex(varPattern), varValue);
        }
        return result;
    }

private:
    ExpressionEvaluator _M_expression_parser;

    /// @brief Parses the expression and returns the result
    /// @param expression Expression to parse 
    /// @return Result of the expression parsing
    std::vector<std::string> _M_getting_tokens(const std::string &expression)
    {
        std::vector<std::string> tokens;
        std::string current_token;

        for (char c : expression)
        {
            if (std::isdigit(c) || std::isalpha(c))
            {
                current_token += c;
            }
            else if (std::ispunct(c))
            {
                // Добавляем текущий токен, если он не пустой
                if (!current_token.empty())
                {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
                // Добавляем оператор как отдельный токен
                tokens.push_back(std::string(1, c));
            }
        }

        // Добавляем последний токен, если есть
        if (!current_token.empty())
        {
            tokens.push_back(current_token);
        }

        return tokens;
    }

    /// @brief Parses a string and returns a list of tokens
    /// @param expression The expression 
    /// @return the expression list of tokens 
    std::vector<std::string> _M_extract_variables(const std::string &expression)
    {
        std::vector<std::string> variables;
        std::string current_var;

        for (char c : expression)
        {
            // Проверяем, является ли символ буквой или цифрой
            if (std::isalpha(c) || std::isdigit(c))
            {
                current_var += c;
            }
            else
            {
                // Если текущая переменная не пуста, добавляем ее в список
                if (!current_var.empty())
                {
                    // Проверяем, начинается ли переменная с буквы
                    // и нет ли уже такой переменной в списке
                    if (std::isalpha(current_var[0]) &&
                        std::find(variables.begin(), variables.end(), current_var) == variables.end())
                    {
                        variables.push_back(current_var);
                    }
                    current_var.clear();
                }
            }
        }

        // Добавляем последнюю переменную, если она осталась
        if (!current_var.empty())
        {
            if (std::isalpha(current_var[0]) &&
                std::find(variables.begin(), variables.end(), current_var) == variables.end())
            {
                variables.push_back(current_var);
            }
        }

        return variables;
    }
};

#endif /* BINARYEXECUTER_HPP_ */
