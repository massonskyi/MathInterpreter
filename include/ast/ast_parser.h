#ifndef AST_PARSER_h
#define AST_PARSER_h

#include "ast.h"
#include <string>
#include <memory>
#include <cctype>
#include <optional>
#include <set>
#include <utility>
class ASTParser {
public:
    explicit ASTParser(ASTContext context) : context(std::move(context)) {}

    std::shared_ptr<ASTNode> parse(const std::string& expr) {
        size_t pos = 0;
        return parse_expression(expr, pos);
    }

private:
    ASTContext context;

    // Парсинг выражения (сложение и вычитание)
    std::shared_ptr<ASTNode> parse_expression(const std::string& expr, size_t& pos) {
        auto left = parse_term(expr, pos);
        while (pos < expr.size()) {
            skip_whitespace(expr, pos);
            if (auto op = parse_operator(expr, pos)) {
                auto right = parse_term(expr, pos);
                left = std::make_shared<BinaryOpNode>(*op, std::move(left), std::move(right));
            } else {
                break;
            }
        }
        return left;
    }

    // Парсинг термина (умножение и деление)
    std::shared_ptr<ASTNode> parse_term(const std::string& expr, size_t& pos) {
        auto left = parse_factor(expr, pos);
        while (pos < expr.size()) {
            skip_whitespace(expr, pos);
            if (auto op = parse_operator(expr, pos, {'*', '/'})) {
                auto right = parse_factor(expr, pos);
                left = std::make_shared<BinaryOpNode>(*op, std::move(left), std::move(right));
            } else {
                break;
            }
        }
        return left;
    }

    // Парсинг фактора (числа, переменные, вызовы функций, скобки)
    std::shared_ptr<ASTNode> parse_factor(const std::string& expr, size_t& pos) {
        skip_whitespace(expr, pos);
        if (expr[pos] == '(') {
            pos++; // Пропускаем '('
            auto node = parse_expression(expr, pos);
            skip_whitespace(expr, pos);
            if (expr[pos] != ')') {
                throw std::runtime_error("Expected closing parenthesis");
            }
            pos++; // Пропускаем ')'
            return node;
        } else if (std::isdigit(expr[pos]) || expr[pos] == '.') {
            return parse_number(expr, pos);
        } else if (std::isalpha(expr[pos])) {
            return parse_variable_or_function(expr, pos);
        } else {
            throw std::runtime_error("Unexpected character in expression");
        }
    }

    // Парсинг числа
    static std::shared_ptr<ASTNode> parse_number(const std::string& expr, size_t& pos) {
        size_t start = pos;
        while (pos < expr.size() && (std::isdigit(expr[pos]) || expr[pos] == '.')) {
            pos++;
        }
        double value = std::stod(expr.substr(start, pos - start));
        return std::make_shared<NumberNode>(value);
    }

    // Парсинг переменной или вызова функции
    std::shared_ptr<ASTNode> parse_variable_or_function(const std::string& expr, size_t& pos) {
        size_t start = pos;
        while (pos < expr.size() && (std::isalnum(expr[pos]) || expr[pos] == '_')) {
            pos++;
        }
        std::string name = expr.substr(start, pos - start);

        skip_whitespace(expr, pos);
        if (pos < expr.size() && expr[pos] == '(') {
            // Это вызов функции
            pos++; // Пропускаем '('
            std::vector<std::shared_ptr<ASTNode>> args;
            while (pos < expr.size() && expr[pos] != ')') {
                args.push_back(parse_expression(expr, pos));
                skip_whitespace(expr, pos);
                if (expr[pos] == ',') {
                    pos++; // Пропускаем ','
                }
            }
            if (expr[pos] != ')') {
                throw std::runtime_error("Expected closing parenthesis");
            }
            pos++; // Пропускаем ')'
            return std::make_shared<FunctionCallNode>(name, std::move(args));
        } else {
            // Это переменная
            return std::make_shared<VariableNode>(name, context);
        }
    }

    // Парсинг оператора
    static std::optional<std::string> parse_operator(const std::string& expr, size_t& pos, const std::set<char>& allowed_ops = {'+', '-', '*', '/'}) {
        skip_whitespace(expr, pos);
        if (pos < expr.size() && allowed_ops.count(expr[pos])) {
            return std::string(1, expr[pos++]);
        }
        return std::nullopt;
    }

    // Пропуск пробелов
    static void skip_whitespace(const std::string& expr, size_t& pos) {
        while (pos < expr.size() && std::isspace(expr[pos])) {
            pos++;
        }
    }
};
#endif // AST_PARSER_h