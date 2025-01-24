#ifndef EXPRESSION_PARSER_HPP
#define EXPRESSION_PARSER_HPP
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <stdexcept>
#include <iostream>

/// @brief This class parses an arithmetic expression and evaluates it the result
class ExpressionEvaluator final {
public:
    /// @brief This method is evaluate an arithmetic expression and returns the result
    /// @param expression arithmetic expression
    /// @return result of the expression
    double evaluate(const std::string& expression) {
        // Tokenize the expression to ensure proper spacing
        std::string tokenized_expr = _M_tokenize_expression(expression);

        // Convert to RPN
        std::vector<std::pair<std::string, bool>> rpn = extract(tokenized_expr);

        // Evaluate the RPN expression
        return _M_evaluate_rpn(rpn);
    }

    /// @brief This method tokenizes an arithmetic expression
    /// @param expression arithmetical expression
    /// @return tokenized expression
    std::vector<std::pair<std::string, bool>> extract(const std::string& expression) {
        std::vector<std::pair<std::string, bool>> output;
        std::stack<std::string> operators;
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            if (std::isdigit(token[0]) ||
                (token[0] == '-' && token.length() > 1 && std::isdigit(token[1]))) {
                output.push_back({token, false});
            } else if (token == "(") {
                operators.push(token);
            } else if (token == ")") {
                while (!operators.empty() && operators.top() != "(") {
                    output.push_back({operators.top(), true});
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == "(") {
                    operators.pop();
                }
            } else if (_M_is_operator(token)) {
                while (!operators.empty() &&
                       operators.top() != "(" &&
                       (_M_precedence[operators.top()] > _M_precedence[token] ||
                        (_M_precedence[operators.top()] == _M_precedence[token] && _M_is_left_associative(token)))) {
                    output.push_back({operators.top(), true});
                    operators.pop();
                }
                operators.push(token);
            }
        }

        while (!operators.empty()) {
            if (operators.top() == "(") {
                throw std::runtime_error("Mismatched parentheses");
            }
            output.push_back({operators.top(), true});
            operators.pop();
        }

        return output;
    }

private:
    std::unordered_map<std::string, int> _M_precedence = {
        {"+", 1}, {"-", 1},
        {"*", 2}, {"/", 2}
    };

    /// @brief This method check token on operator
    /// @param token char token
    /// @return true if operator, false otherwise
    bool _M_is_operator(const std::string& token) {
        return _M_precedence.find(token) != _M_precedence.end();
    }

    /// @brief This method check if operator is left-associative
    /// @param token char token
    /// @return this method already returned true btw operator is left-associative
    bool _M_is_left_associative(const std::string& token) {
        return true;
    }

    /// @brief This method apply operator
    /// @param op operator
    /// @param left first operand
    /// @param right second operand
    /// @return result of applying operator
    double _M_apply_operator(const std::string& op, double left, double right) {
        if (op == "+") return left + right;
        if (op == "-") return left - right;
        if (op == "*") return left * right;
        if (op == "/") return left / right;
        throw std::runtime_error("Unknown operator");
    }

    /// @brief This method apply RPN algorithm
    /// @param rpn tokens 
    /// @return result of applying RPN algorithm
    double _M_evaluate_rpn(const std::vector<std::pair<std::string, bool>>& rpn) {
        std::stack<double> values;

        for (const auto& token : rpn) {
            if (token.second) { // If token is an operator
                double right = values.top(); values.pop();
                double left = values.top(); values.pop();
                values.push(_M_apply_operator(token.first, left, right));
            } else { // If token is a number
                values.push(std::stod(token.first));
            }
        }

        return values.top();
    }

    /// @brief This method getted tokens from expression
    /// @param expression arithmetical expression in string format
    /// @return tokens from expression
    std::string _M_tokenize_expression(const std::string& expression) {
        std::string tokenized;
        std::istringstream iss(expression);
        char ch;
        std::string current_token;

        while (iss.get(ch)) {
            if (std::isdigit(ch) || ch == '.') {
                current_token += ch;
            } else if (ch == '(' || ch == ')') {
                // If there's a number token, add it first
                if (!current_token.empty()) {
                    tokenized += current_token + " ";
                    current_token.clear();
                }
                // Add parenthesis as a separate token
                tokenized += ch;
                tokenized += " ";
            } else if (_M_is_operator(std::string(1, ch))) {
                // If there's a number token, add it first
                if (!current_token.empty()) {
                    tokenized += current_token + " ";
                    current_token.clear();
                }
                // Add operator as a separate token
                tokenized += ch;
                tokenized += " ";
            } else if (std::isspace(ch)) {
                // If there's a number token, add it before space
                if (!current_token.empty()) {
                    tokenized += current_token + " ";
                    current_token.clear();
                }
            }
        }

        // Add last token if exists
        if (!current_token.empty()) {
            tokenized += current_token;
        }

        return tokenized;
    }
};


#endif /* EXPRESSION_PARSER_HPP */