#ifndef BINARYEXECUTER_HPP_
#define BINARYEXECUTER_HPP_

#include <string>
#include <memory>
#include <regex>

#include "../utils.h++"
#include "../parsers/expressionparser.hpp"
#include "../types/matrix.hpp"
#include "../types/rational.hpp"
#include "../types/variable.hpp"
#include "../types/vector.hpp"

#include "../exceptions/exceptions.hpp"

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
    /// @brief Calculation expression for binary operation
    /// @tparam ReturnType This avalaible types are: Vector, Matrix, Rational, Variable
    /// @param lhs first operand
    /// @param rhsPtr second operand
    /// @param expression calculation expression for binary operation ( avalaible latter )
    /// @param oper operator
    /// @return result calculation
    template <AllowedPtrType ReturnType>
    ReturnType calculate(
        const std::string &lhs,
        const value_type &rhsPtr,
        const std::string &expression,
        const std::string &oper)
    {
        Variable lhsValue(std::stod(lhs));

        // Helper macro to reduce repetitive code (preprocessor used sparingly)
#define HANDLE_TYPED_OPERATION(TypeName, makeFunc)                                                               \
    if (auto lhsTyped = std::dynamic_pointer_cast<TypeName>(rhsPtr))                                             \
    {                                                                                                            \
        if (oper == "+")                                                                                         \
            return std::dynamic_pointer_cast<typename ReturnType::element_type>(makeFunc(*lhsTyped + lhsValue)); \
        if (oper == "-")                                                                                         \
            return std::dynamic_pointer_cast<typename ReturnType::element_type>(makeFunc(*lhsTyped - lhsValue)); \
        if (oper == "*")                                                                                         \
            return std::dynamic_pointer_cast<typename ReturnType::element_type>(makeFunc(*lhsTyped * lhsValue)); \
        if (oper == "/")                                                                                         \
            return std::dynamic_pointer_cast<typename ReturnType::element_type>(makeFunc(*lhsTyped / lhsValue)); \
    }

        HANDLE_TYPED_OPERATION(Vector, make_vector_ptr)
        HANDLE_TYPED_OPERATION(Matrix, make_matrix_ptr)
        HANDLE_TYPED_OPERATION(Rational, make_rational_ptr)
        HANDLE_TYPED_OPERATION(Variable, make_variable_ptr)

#undef HANDLE_TYPED_OPERATION

        throw InvalidExpression("Incompatible types for operation");
    }

    /// @brief Overload calculation expression for binary operation
    /// @tparam ReturnType This avalaible types are: Vector, Matrix, Rational, Variable
    /// @param lhs first operand
    /// @param rhsPtr second operand
    /// @param expression calculation expression for binary operation ( avalaible latter )
    /// @param oper operator
    /// @return result calculation
    template <AllowedPtrType ReturnType>
    ReturnType calculate(
        const value_type &lhsPtr,
        const std::string &rhs,
        const std::string &expression,
        const std::string &oper)
    {
        return calculate<ReturnType>(rhs, lhsPtr, expression, oper);
    }

    /// @brief Overload calculation expression for binary operation
    /// @tparam ReturnType This avalaible types are: Vector, Matrix, Rational, Variable
    /// @param lhs first operand
    /// @param rhsPtr second operand
    /// @param expression calculation expression for binary operation ( avalaible latter )
    /// @param oper operator
    /// @return result calculation
    template <AllowedPtrType ReturnType>
    ReturnType calculate(
        const value_type &lhsPtr,
        const value_type &rhsPtr,
        const std::string &expression,
        const std::string &oper)
    {
        // Complex multi-type multiplication logic
#define HANDLE_MULTI_TYPE(LhsType, RhsType, makeFunc)                                                             \
    if (auto lhsTyped = std::dynamic_pointer_cast<LhsType>(lhsPtr))                                               \
    {                                                                                                             \
        if (auto rhsTyped = std::dynamic_pointer_cast<RhsType>(rhsPtr))                                           \
        {                                                                                                         \
            return std::dynamic_pointer_cast<typename ReturnType::element_type>(makeFunc(*lhsTyped * *rhsTyped)); \
        }                                                                                                         \
    }

        HANDLE_MULTI_TYPE(Vector, Vector, make_vector_ptr)
        HANDLE_MULTI_TYPE(Vector, Matrix, make_matrix_ptr)
        HANDLE_MULTI_TYPE(Matrix, Vector, make_matrix_ptr)
        HANDLE_MULTI_TYPE(Matrix, Matrix, make_matrix_ptr)
        HANDLE_MULTI_TYPE(Rational, Rational, make_rational_ptr)
        HANDLE_MULTI_TYPE(Variable, Variable, make_variable_ptr)

#undef HANDLE_MULTI_TYPE

        throw InvalidExpression("Incompatible types for multiplication");
    }

    /// @brief Simple calculation method for only numbers and variables
    /// @tparam ReturnType This avalaible types are: Vector, Matrix, Rational, Variable
    /// @param lhs first operand
    /// @param rhsPtr second operand
    /// @param expression calculation expression for binary operation ( avalaible latter )
    /// @param oper operator
    /// @return result calculation
    variable_ptr calculate(const std::string &expression)
    {
        return make_variable_ptr(Variable(_M_expression_parser.evaluate(expression)));
    }

    // Замена переменных их значениями
    std::string replace_variables(const std::string &expression, stack_map variables)
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
