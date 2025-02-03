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
        skip_whitespace(expr, pos);

        // Check for function definition
        if (expr.substr(pos, 2) == "fn") {
            return parse_function_definition(expr, pos);
        }
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
        }
        else if (expr[pos] == '[' && expr[pos + 1] != '[') {
            // Обработка векторов
            return parse_vector(expr, pos);
        }
        else if (expr[pos] == '[' && expr[pos + 1] == '[') {
            return parse_matrix(expr, pos); // Обработка матриц
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
            return std::make_shared<FunctionCallNode>(name, std::move(args),context);
        } else {
            // Это переменная
            return std::make_shared<VariableNode>(name, context);
        }
    }
    // Парсинг вектора
    std::shared_ptr<ASTNode> parse_vector(const std::string& expr, size_t& pos) {
        pos++; // Пропускаем '['
        std::vector<std::shared_ptr<ASTNode>> elements;

        while (pos < expr.size() && expr[pos] != ']') {
            skip_whitespace(expr, pos);

            // Парсим элемент вектора (может быть числом, переменной или выражением)
            elements.push_back(parse_expression(expr, pos));

            skip_whitespace(expr, pos);
            if (expr[pos] == ',') {
                pos++; // Пропускаем запятую
            }
        }

        if (pos >= expr.size() || expr[pos] != ']') {
            throw std::runtime_error("Expected closing bracket for vector");
        }
        pos++; // Пропускаем ']'

        // Создаем узел AST для вектора
        return std::make_shared<VectorNode>(std::move(elements));
    }

    // Парсинг матрицы
    std::shared_ptr<ASTNode> parse_matrix(const std::string& expr, size_t& pos) {
        pos += 1; // Пропускаем '['
        std::vector<std::shared_ptr<ASTNode>> rows;

        while (pos < expr.size() && expr[pos] != ']') {
            skip_whitespace(expr, pos);

            // Парсим строку матрицы (вектор)
            rows.push_back(parse_vector(expr, pos));

            skip_whitespace(expr, pos);
            if (expr[pos] == ',') {
                pos++; // Пропускаем запятую
            }
        }

        if (pos >= expr.size() || expr.substr(pos - 1, 2) != "]]") {
            throw std::runtime_error("Expected closing brackets for matrix");
        }
        pos += 1; // Пропускаем ']]'

        // Создаем узел AST для матрицы
        return std::make_shared<MatrixNode>(std::move(rows));
    }
    // Парсинг оператора
    static std::optional<std::string> parse_operator(const std::string& expr, size_t& pos, const std::set<char>& allowed_ops = {'+', '-', '*', '/'}) {
        skip_whitespace(expr, pos);
        if (pos < expr.size() && allowed_ops.count(expr[pos])) {
            return std::string(1, expr[pos++]);
        }
        return std::nullopt;
    }

    std::unique_ptr<ASTNode> parse_function_definition(const std::string& expr, size_t& pos) {
        skip_whitespace(expr, pos);
        if (expr.substr(pos, 2) != "fn") {
            throw std::runtime_error("Expected 'fn' keyword");
        }
        pos += 2;

        skip_whitespace(expr, pos);
        size_t name_start = pos;
        while (pos < expr.size() && std::isalnum(expr[pos])) {
            pos++;
        }
        std::string name = expr.substr(name_start, pos - name_start);

        skip_whitespace(expr, pos);
        if (expr[pos] != '(') {
            throw std::runtime_error("Expected '(' after function name");
        }
        pos++;

        std::vector<std::pair<std::string, std::string>> parameters;
        while (expr[pos] != ')') {
            skip_whitespace(expr, pos);
            if (expr.substr(pos, 3) != "let") {
                throw std::runtime_error("Expected 'let' keyword in parameter declaration");
            }
            pos += 3;

            skip_whitespace(expr, pos);
            size_t param_name_start = pos;
            while (pos < expr.size() && std::isalnum(expr[pos])) {
                pos++;
            }
            std::string param_name = expr.substr(param_name_start, pos - param_name_start);

            skip_whitespace(expr, pos);
            if (expr[pos] != ':') {
                throw std::runtime_error("Expected ':' after parameter name");
            }
            pos++;

            skip_whitespace(expr, pos);
            size_t param_type_start = pos;
            while (pos < expr.size() && std::isalnum(expr[pos])) {
                pos++;
            }
            std::string param_type = expr.substr(param_type_start, pos - param_type_start);

            parameters.emplace_back(param_name, param_type);

            skip_whitespace(expr, pos);
            if (expr[pos] == ',') {
                pos++;
            }
        }
        pos++; // Пропускаем ')'

        skip_whitespace(expr, pos);
        if (expr.substr(pos, 2) != "->") {
            throw std::runtime_error("Expected '->' after parameters");
        }
        pos += 2;

        skip_whitespace(expr, pos);
        size_t return_type_start = pos;
        while (pos < expr.size() && std::isalnum(expr[pos])) {
            pos++;
        }
        std::string return_type = expr.substr(return_type_start, pos - return_type_start);

        skip_whitespace(expr, pos);
        if (expr[pos] != '{') {
            throw std::runtime_error("Expected '{' after return type");
        }
        pos++;

        auto body = parse_expression(expr, pos);

        skip_whitespace(expr, pos);
        if (expr[pos] != '}') {
            throw std::runtime_error("Expected '}' at the end of function body");
        }
        pos++;

        return std::make_unique<FunctionDefinitionNode>(name, parameters, return_type, std::move(body), context);
    }
    // Пропуск пробелов
    static void skip_whitespace(const std::string& expr, size_t& pos) {
        while (pos < expr.size() && std::isspace(expr[pos])) {
            pos++;
        }
    }
};
#endif // AST_PARSER_h