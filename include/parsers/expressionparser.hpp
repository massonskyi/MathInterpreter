#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP

#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>
#include <variant>
#include <memory>
#include <cctype>
#include <stdexcept>
#include <iostream>

#include "../types/variable.hpp"
#include "../types/vector.hpp"
#include "../types/matrix.hpp"
#include "../types/rational.hpp"


// Variant to hold different types of operands
using OperandValue = std::variant<Variable, Vector, Matrix, Rational>;

class ExpressionEvaluator final {
public:
    struct TokenInfo {
        std::string token;
        bool is_operator;
        bool is_variable;

        TokenInfo(std::string t, bool op = false, bool var = false)
                : token(std::move(t)), is_operator(op), is_variable(var) {}
    };

    /// @brief Evaluates an arithmetic expression with variables
    OperandValue evaluate(const std::string& expression,
                          const std::unordered_map<std::string, std::shared_ptr<AbstractObject>>& variables) {
        std::vector<TokenInfo> tokens = tokenize_with_variables(expression);
        std::vector<std::pair<std::string, bool>> rpn = convert_to_rpn(tokens);
        return _M_evaluate_rpn(rpn, variables);
    }

private:
    std::unordered_map<std::string, int> _M_precedence = {
            {"+", 1}, {"-", 1},
            {"*", 2}, {"/", 2},
            {"[", 0}, {"]", 0},  // Добавлены для индексации векторов/матриц
            {"(", 0}, {")", 0}
    };

    std::vector<TokenInfo> tokenize_with_variables(const std::string& expression) {
        std::vector<TokenInfo> tokens;
        std::string current;

        for (size_t i = 0; i < expression.length(); ++i) {
            char ch = expression[i];

            if (std::isalpha(ch)) {  // Обработка переменных
                if (!current.empty()) {
                    tokens.emplace_back(current);
                    current.clear();
                }
                std::string var;
                while (i < expression.length() &&
                       (std::isalnum(expression[i]) || expression[i] == '_')) {
                    var += expression[i++];
                }
                i--;
                tokens.emplace_back(var, false, true);
            }
            else if (std::isdigit(ch) || ch == '.') {  // Обработка чисел
                current += ch;
            }
            else if (_M_is_operator(std::string(1, ch))) {  // Обработка операторов
                if (!current.empty()) {
                    tokens.emplace_back(current);
                    current.clear();
                }
                tokens.emplace_back(std::string(1, ch), true);
            }
            else if (ch == '(' || ch == ')') {  // Обработка скобок
                if (!current.empty()) {
                    tokens.emplace_back(current);
                    current.clear();
                }
                tokens.emplace_back(std::string(1, ch), true);
            }
            else if (ch == '[' || ch == ']') {  // Обработка квадратных скобок
                if (!current.empty()) {
                    tokens.emplace_back(current);
                    current.clear();
                }
                tokens.emplace_back(std::string(1, ch), true);
            }
            else if (ch == ',') {  // Обработка запятых
                if (!current.empty()) {
                    tokens.emplace_back(current);
                    current.clear();
                }
                tokens.emplace_back(std::string(1, ch), true);
            }
            else if (std::isspace(ch)) {  // Пропуск пробельных символов
                if (!current.empty()) {
                    tokens.emplace_back(current);
                    current.clear();
                }
            }
        }

        if (!current.empty()) {
            tokens.emplace_back(current);
        }

        return tokens;
    }

    std::vector<std::pair<std::string, bool>> convert_to_rpn(
            const std::vector<TokenInfo>& tokens
    ) {
        std::vector<std::pair<std::string, bool>> output;
        std::stack<std::string> operators;

        for (const auto& token : tokens) {
            if (!token.is_operator) {  // Число или переменная
                output.emplace_back(token.token, false);
            }
            else if (token.token == "(") {
                operators.push(token.token);
            }
            else if (token.token == ")") {
                while (!operators.empty() && operators.top() != "(") {
                    output.emplace_back(operators.top(), true);
                    operators.pop();
                }
                if (!operators.empty()) operators.pop();  // Удаляем "("
            }
            else if (token.token == "[") {  // Начало индексации
                operators.push(token.token);
            }
            else if (token.token == "]") {  // Конец индексации
                while (!operators.empty() && operators.top() != "[") {
                    output.emplace_back(operators.top(), true);
                    operators.pop();
                }
                if (!operators.empty()) operators.pop();  // Удаляем "["
                output.emplace_back("[]", true);  // Специальный оператор для индексации
            }
            else {  // Обычный оператор
                while (!operators.empty() && operators.top() != "(" &&
                       _M_precedence[operators.top()] >= _M_precedence[token.token]) {
                    output.emplace_back(operators.top(), true);
                    operators.pop();
                }
                operators.push(token.token);
            }
        }

        while (!operators.empty()) {
            output.emplace_back(operators.top(), true);
            operators.pop();
        }

        return output;
    }

    OperandValue _M_evaluate_rpn(
            const std::vector<std::pair<std::string, bool>>& rpn,
            const std::unordered_map<std::string, std::shared_ptr<AbstractObject>>& variables
    ) {
        std::stack<OperandValue> values;

        for (const auto& token : rpn) {
            if (!token.second) {  // Если это не оператор
                if (auto var_it = variables.find(token.first); var_it != variables.end()) {
                    if (auto var_ptr = dynamic_pointer_cast<Variable>(var_it->second); var_ptr != nullptr) {
                        values.emplace(*var_ptr);
                    }
                    else if (auto rat_ptr = dynamic_pointer_cast<Rational>(var_it->second); rat_ptr != nullptr) {
                        values.emplace(*rat_ptr);
                    }else if (auto vec_ptr = dynamic_pointer_cast<Vector>(var_it->second); vec_ptr != nullptr) {
                        values.emplace(*vec_ptr);
                    }else if (auto mat_ptr = dynamic_pointer_cast<Matrix>(var_it->second); mat_ptr != nullptr) {
                        values.emplace(*mat_ptr);
                    }
                } else {
                    try {
                        values.emplace(Variable(std::stod(token.first)));
                    } catch (const std::exception& e) {
                        throw std::runtime_error("Unknown variable or invalid number: " + token.first);
                    }
                }
            } else {  // Если это оператор
                if (token.first == "[]") {  // Специальная обработка индексации
                    auto index = values.top(); values.pop();
                    auto container = values.top(); values.pop();
                    values.push(_M_apply_indexing(container, index));
                } else {  // Обычный бинарный оператор
                    auto right = values.top(); values.pop();
                    auto left = values.top(); values.pop();
                    values.push(_M_apply_operator(token.first, left, right));
                }
            }
        }

        if (values.empty()) {
            throw std::runtime_error("Expression evaluation resulted in no value");
        }
        return values.top();
    }
    template<typename TargetType, typename SourceType>
    std::shared_ptr<TargetType> try_dynamic_cast(const std::shared_ptr<SourceType>& source) {
        return std::dynamic_pointer_cast<TargetType>(source);
    }

    std::shared_ptr<AbstractObject> cast_to_concrete(
            const std::shared_ptr<AbstractObject>& obj)
    {
        if (auto var = try_dynamic_cast<Variable>(obj)) return var;
        if (auto rat = try_dynamic_cast<Rational>(obj)) return rat;
        if (auto vec = try_dynamic_cast<Vector>(obj)) return vec;
        if (auto mat = try_dynamic_cast<Matrix>(obj)) return mat;

        return nullptr;
    }
    OperandValue _M_apply_operator(const std::string& op,
                                   const OperandValue& left,
                                   const OperandValue& right) {
        return std::visit([&](auto&& lhs, auto&& rhs) -> OperandValue {
            using L = std::decay_t<decltype(lhs)>;
            using R = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<L, Variable> && std::is_same_v<R, Variable>) {
                if (op == "+") return lhs + rhs;
                if (op == "-") return lhs - rhs;
                if (op == "*") return lhs * rhs;
                if (op == "/") {
                    if (rhs == 0) throw std::runtime_error("Division by zero");
                    return lhs / rhs;
                }
            }
            else if constexpr (std::is_same_v<L, Vector> || std::is_same_v<R, Vector>) {
                return _M_apply_vector_operation(op, lhs, rhs);
            }
            else if constexpr (std::is_same_v<L, Matrix> || std::is_same_v<R, Matrix>) {
                return _M_apply_matrix_operation(op, lhs, rhs);
            }

            throw std::runtime_error("Unsupported operation " + op +
                                     " between the given types");
        }, left, right);
    }
    OperandValue _M_apply_indexing(const OperandValue& container, const OperandValue& index) {
        return std::visit([this](auto&& cont, auto&& idx) -> OperandValue {
            using C = std::decay_t<decltype(cont)>;
            using I = std::decay_t<decltype(idx)>;

            if constexpr (std::is_same_v<C, Vector>) {
                if constexpr (std::is_same_v<I, double>) {
                    auto i = static_cast<size_t>(idx);
                    if (i >= cont.size()) {
                        throw std::out_of_range("Vector index out of range");
                    }
                    return cont[i];
                }
            }
            else if constexpr (std::is_same_v<C, Matrix>) {
                // Для матрицы ожидаем что idx это pair<double, double>
                if constexpr (std::is_same_v<I, std::pair<double, double>>) {
                    auto row = static_cast<size_t>(idx.first);
                    auto col = static_cast<size_t>(idx.second);
                    if (row >= cont.rows() || col >= cont.cols()) {
                        throw std::out_of_range("Matrix indices out of range");
                    }
                    return cont(row, col);  // Предполагаем что у Matrix есть метод operator()(row, col)
                } else {
                    throw std::runtime_error("Matrix indexing requires two indices");
                }
            }
            else if constexpr (std::is_same_v<C, Variable>) {
                return _M_apply_indexing(cont, idx);
            }

            throw std::runtime_error("Invalid indexing operation");
        }, container, index);
    }

    OperandValue _M_apply_vector_operation(const std::string& op,
                                           const OperandValue& left,
                                           const OperandValue& right) {
        return std::visit([&](auto&& lhs, auto&& rhs) -> OperandValue {
            using L = std::decay_t<decltype(lhs)>;
            using R = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<L, Vector>) {
                if constexpr (std::is_same_v<R, Vector>) {
                    // Вектор-вектор операции
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                    if (op == "*") return lhs * rhs;  // Скалярное произведение
                    if (op == "/") return lhs / rhs;  // Скалярное произведение
                }
                else if constexpr (std::is_same_v<R, Variable>) {
                    // Вектор-скаляр операции
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                }
            }
            else if constexpr (std::is_same_v<R, Vector> && std::is_same_v<L, Variable>) {
                // Скаляр-вектор операции
                if (op == "*") return rhs * lhs;
                if (op == "/") return rhs / lhs;
                if (op == "+") return rhs + lhs;
                if (op == "-") return rhs - lhs;
            }

            throw std::runtime_error("Unsupported vector operation");
        }, left, right);
    }

    OperandValue _M_apply_matrix_operation(const std::string& op,
                                           const OperandValue& left,
                                           const OperandValue& right) {
        return std::visit([&](auto&& lhs, auto&& rhs) -> OperandValue {
            using L = std::decay_t<decltype(lhs)>;
            using R = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<L, Matrix>) {
                if constexpr (std::is_same_v<R, Matrix>) {
                    // Матрица-матрица операции
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                }
                else if constexpr (std::is_same_v<R, Vector>) {
                    // Матрица-вектор операции
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;

                }
                else if constexpr (std::is_same_v<R, Variable>) {
                    // Матрица-скаляр операции
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                }
            }
            else if constexpr (std::is_same_v<R, Matrix> && std::is_same_v<L, double>) {
                // Скаляр-матрица операции
                if (op == "*") return rhs * lhs;
            }

            throw std::runtime_error("Unsupported matrix operation");
        }, left, right);
    }

    bool _M_is_operator(const std::string& token) {
        return _M_precedence.find(token) != _M_precedence.end();
    }
};

#endif /* EXPRESSION_PARSER_HPP */