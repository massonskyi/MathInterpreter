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

#include "utils.h"
#include "data/data.h"
#include "base/abstractobject.h"
#include "exceptions/exceptions.h"

#include "types/matrix.h"
#include "types/variable.h"
#include "types/vector.h"
#include "types/rational.h"

#include "parsers/regexmanager.h"
#include "parsers/matrixparser.h"
#include "parsers/vectorparser.h"
#include "parsers/rationalparser.h"
#include "parsers/variableparser.h"

#include "parsers/functionparser.h"

#include "function/base.h"
#include "function/lambdainterpreter.h"
#include "io/ioreader.h"

#include "validators/stringvalidator.h"

#include "ast/ast.h"
#include "ast/ast_optimizer.h"
#include "ast/ast_parser.h"

class Interpreter final
{
public:
    using value_type =  std::shared_ptr<AbstractObject>;
    enum class VarType
    {
        Variable,
        Matrix,
        Vector,
        Rational,
        Unknown
    };
    Interpreter()
    {
        initialize_constants();
        initialize_functions();
        initialize_regexp();
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

            if (line.rfind("fn", 0) == 0)
            { // Check if the line starts with "fn"
                std::string multiLineInput = line;
                while (multiLineInput.find(';') == std::string::npos)
                {
                    std::cout << "...\t"; // Indicate continuation
                    std::getline(std::cin, line);
                    multiLineInput += "\n" + line; // Append the new line
                }
                line = multiLineInput;
            }
            if (!M_validator.validate(line))
            {
                M_validator.printErrors();
                continue;
            }
            try
            {
                // line = "x = 2";
                if (_M_contains_any_symbol(line, RESERVED.at(0)))
                {
                    if (std::string op = _M_find_contains_symbol(line, RESERVED.at(0)); !op.empty())
                        M_execute_command(line, op);
                }
                else if (_M_contains_function_call(line))
                    M_function_execute(line);
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
        std::vector<std::string> lines;

        IOReader reader(filename);
        if (auto valid = reader.isValid(); valid && *valid)
        {
            if (auto data = reader.read())
            {
                for (const auto &str : *data)
                {
                    lines.push_back(str);
                }
            }
        }

        bool inBlockComment = false;

        for (auto &line : lines)
        {
            if (line.find("//") == 0 || line.find("#") == 0)
            {
                continue;
            }

            // Пропускаем строки, которые содержат блочные комментарии /* ... */
            size_t startComment = line.find("/*");
            size_t endComment = line.find("*/");

            if (startComment != std::string::npos)
            {
                inBlockComment = true;
            }

            if (inBlockComment)
            {
                if (endComment != std::string::npos)
                {
                    inBlockComment = false;
                    line = line.substr(endComment + 2); // Удаляем комментарий и продолжаем обработку строки
                }
                else
                {
                    continue; // Пропускаем строку, если она внутри блочного комментария
                }
            }

            if (!M_validator.validate(line))
            {
                M_validator.printErrors();
                continue;
            }

            if (line.find("//") == std::string::npos)
                try
                {
                    if (_M_contains_any_symbol(line, RESERVED.at(0)))
                    {
                        if (std::string op = _M_find_contains_symbol(line, RESERVED.at(0)); !op.empty())
                            M_execute_command(line, op);
                    }
                    else if (_M_contains_function_call(line))
                        M_function_execute(line);
                    else
                        _M_print_variable(line);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
        }
    }

private:
    using stack_functions = std::unordered_map<std::string, FuncParser::NewFunction>;
    std::unordered_map<std::string, std::regex> M_regexes;

    ASTContext ctx;
    stack_functions M_functions{};

    StringValidator M_validator;

    void initialize_constants(){
        ctx.setVariable("pi",Variable(3.14159265358979323846));
        ctx.setVariable("e", Variable(2.71828182845904523536));
    }
    void initialize_functions() {
        // auto sin_node = std::make_shared<FunctionDefinitionNode>("sin", {}, "Variable", sin_function, ctx);
        // auto cos_node = std::make_shared<FunctionDefinitionNode>("cos", {}, "Variable", cos_function, ctx);

        // ctx.addFunction("sin", sin_node);
        // ctx.addFunction("cos", cos_node);
    }

    void initialize_regexp() {
        append_(M_regexes, "MatrixLiteral", std::regex(R"(\[\s*(\[\s*[a-zA-Z\d]+\s*(?:,\s*[a-zA-Z\d]+\s*)*\]\s*(?:,\s*\[\s*[a-zA-Z\d]+\s*(?:,\s*[a-zA-Z\d]+\s*)*\]\s*)*)\])"));
        append_(M_regexes, "VectorLiteral", std::regex(R"(^\[\s*([a-zA-Z\d]+\s*,\s*)*[a-zA-Z\d]+\s*\]$)"));
        append_(M_regexes, "RationalLiteral", std::regex(R"(^(\d+)\s*\/\s*(\d+)$)"));
        append_(M_regexes, "VariableLiteral", std::regex(R"(\d+)"));
        append_(M_regexes, "VectorOperation", std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))"));
        append_(M_regexes, "MatrixOperation", std::regex(R"((\w+)\s*([+\-*/])\s*(\w+))"));
        append_(M_regexes, "RationalOperation", std::regex(R"((\w+|(\d+\/\d+))\s*([+\-*/])\s*(\w+|(\d+\/\d+)))"));
        append_(M_regexes, "VariableOperation", std::regex(R"((\w+|d+)\s*([+\-*/])\s*(\w+|\d+))"));
        append_(M_regexes, "functionLiteral", std::regex(R"((\w+)\((.*?)\))"));
        append_(M_regexes, "LetDeclaration",
                std::regex(R"(^let\s+(\w+)\s*:\s*(\w+)\s*=\s*(.+)$)"));
    }
    ASTValue M_function_expression(const std::string &expression, const std::string &op)
    {
        if (std::smatch match; std::regex_match(expression, match, M_regexes.find("functionLiteral")->second))
        {
            const std::string func_name = match[1]; // Имя функции (например, sin, cos)
            const std::string param_str = match[2]; // Параметр для функции
            const FunctionType func_type = get_function_type(func_name);

            if (_M_is_number(param_str))
            {
                return M_function_call(std::stod(param_str), func_type);
            }

            try
            {
                // Получаем переменную из контекста
                ASTValue param = ctx.getVariable(param_str);
                return std::visit([this, func_type](const auto &var) -> ASTValue
                                  { return M_function_call(var, func_type); }, param);
            }
            catch (...)
            {
                throw std::invalid_argument("Variable not found: " + param_str);
            }
        }
        throw std::invalid_argument("Invalid function expression: " + expression);
    }

    template <AllowedTypes Tp>
    ASTValue M_function_call(Tp args, const FunctionType func_type)
    {
        if (!std::is_arithmetic_v<Tp>)
        {
            throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type));
        }

        switch (func_type)
        {
        case FunctionType::Sin:
            return Variable(std::sin(args));
        case FunctionType::Cos:
            return Variable(std::cos(args));
        case FunctionType::CreateRat:
        {
            Variable var(args);
            return Rational(var);
        }
        default:
            throw std::invalid_argument("Unknown function: " + get_function_name(func_type));
        }
    }

    static ASTValue M_function_call(const ASTValue &args, const FunctionType func_type)
    {
        return std::visit([func_type](auto arg) -> ASTValue
                          {
            using T = std::decay_t<decltype(arg)>;

            switch (func_type) {
                case FunctionType::Sin:
                    if constexpr (std::is_same_v<T, Variable>) return _M_sin(arg);
                    if constexpr (std::is_same_v<T, Vector>) return _M_sin(arg);
                    if constexpr (std::is_same_v<T, Matrix>) return _M_sin(arg);
                    if constexpr (std::is_same_v<T, Rational>) return _M_sin(arg);
                    break;

                case FunctionType::Cos:
                    if constexpr (std::is_same_v<T, Variable>) return _M_cos(arg);
                    if constexpr (std::is_same_v<T, Vector>) return _M_cos(arg);
                    if constexpr (std::is_same_v<T, Matrix>) return _M_cos(arg);
                    if constexpr (std::is_same_v<T, Rational>) return _M_cos(arg);
                    break;

                case FunctionType::CreateRat:
                    if constexpr (std::is_same_v<T, Variable>) return _M_create_rat(arg);
                    throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type));

                case FunctionType::Transpose:
                    if constexpr (std::is_same_v<T, Matrix>) return arg.transpose();
                    throw std::invalid_argument("Unsupported type for function: " + get_function_name(func_type));

                default:
                    throw std::invalid_argument("Unknown function: " + get_function_name(func_type));
            } }, args);
    }

void M_function_execute(const std::string &command)
{
    if (!_M_assignment_with_function(command))
    {
        std::istringstream stream(command);
        std::string variableName, equalsSign, expression;
        stream >> variableName >> equalsSign;
        std::getline(stream, expression);

        if (expression.empty())
        {
            throw InvalidExpression("Expression cannot be empty");
        }

        // Вычисляем выражение и сохраняем результат в переменной
        ctx.setVariable(variableName, M_function_expression(expression, equalsSign));
    }
    else
    {
        // Если это вызов функции без присваивания, просто выводим результат
        auto result = M_function_expression(command, "");
        std::visit([this](const auto &args) -> void
                   { 
                    auto var = std::make_shared<AbstractObject>(args); 
                    _M_print_object(var); 
                   }, result);
    }
}

    void M_execute_command(const std::string &command, const std::string &op)
    {
        std::istringstream stream(command);
        std::string token;
        stream >> token;
        if (token == "fn"){
            try {
                FuncParser parser;
                FuncParser::NewFunction func = parser.parse(command);

                // Создаем узел AST для функции
                std::vector<std::pair<std::string, std::string>> parameters;
                for (const auto& arg : func._args) {
                    parameters.emplace_back(arg.first, arg.second);
                }

                // Парсим тело функции в AST
                ASTParser astParser(ctx);
                auto bodyNode = astParser.parse(func._body);

                // Создаем узел FunctionDefinitionNode
                auto functionNode = std::make_unique<FunctionDefinitionNode>(
                    func._func_name,
                    parameters,
                    func._return_type,
                    std::move(bodyNode),
                    ctx
                );

                // Сохраняем функцию в контексте
                ctx.addFunction(func._func_name, std::move(functionNode));

                std::cout << "Function '" << func._func_name << "' successfully defined.\n";
            } catch (const std::exception& e) {
                std::cerr << "Error parsing function: " << e.what() << "\n";
            }
            return;
        }
        // Случай: создание новой переменной с let
        if (token == "let")
        {
            M_handle_let_declaration(stream, op);
        }
        // Случай: присваивание существующей переменной
        else
        {
            M_handle_assignment(command, op);
        }
    }

    void M_handle_let_declaration(std::istringstream &stream, const std::string &op)
    {
        std::string full_decl;
        std::getline(stream, full_decl); // Читаем всю оставшуюся часть строки
        size_t comment_pos = full_decl.find('#');
        if (comment_pos != std::string::npos)
        {
            full_decl = full_decl.substr(0, comment_pos);
        }

        // Регулярное выражение для парсинга объявления let
        static const std::regex let_regex(
            R"(^\s*([a-zA-Z_]\w*)\s*:\s*([a-zA-Z]+)\s*=\s*(.+)\s*$)",
            std::regex::ECMAScript | std::regex::icase);
        std::smatch match;

        if (!std::regex_match(full_decl, match, let_regex))
        {
            throw InvalidSyntax("Invalid let declaration format");
        }

        const std::string var_name = match[1].str();
        const std::string type_str = to_lower(match[2].str());
        std::string expression = match[3].str();

        if (expression.empty())
        {
            throw InvalidSyntax("Missing value in declaration");
        }

        // Проверка на существование переменной
        if (ctx.findVariable(var_name)) {
            throw RedeclarationError("Variable '" + var_name + "' already exists");
        }

        VarType type = M_parse_type(type_str);
        M_create_variable(var_name, type, expression, op);
    }

    VarType M_parse_type(const std::string &type_str)
    {
        static const std::unordered_map<std::string, VarType> type_map = {
            {"num", VarType::Variable},
            {"mat", VarType::Matrix},
            {"vec", VarType::Vector},
            {"rat", VarType::Rational}};

        auto it = type_map.find(type_str);
        if (it == type_map.end())
        {
            throw InvalidTypeError("Unknown type: " + type_str);
        }
        return it->second;
    }
    void M_create_variable(const std::string &name, VarType type, const std::string &expression, const std::string &op)
    {
        // Парсим выражение в AST
        ASTParser parser(ctx);
        auto ast_node = parser.parse(expression);

        // Оптимизируем AST
        // ast_node = ASTOptimizer::optimize(ast_node);

        // Вычисляем значение выражения
        ASTValue new_value;
        try
        {
            switch (type)
            {
            case VarType::Variable:
                new_value = evaluate_ast_node<Variable>(ast_node);
                break;
            case VarType::Matrix:
                new_value = evaluate_ast_node<Matrix>(ast_node);
                break;
            case VarType::Vector:
                new_value = evaluate_ast_node<Vector>(ast_node);
                break;
            case VarType::Rational:
                new_value = evaluate_ast_node<Rational>(ast_node);
                break;
            default:
                throw InvalidTypeError("Unsupported type for variable creation");
            }
        }
        catch (const std::exception &e)
        {
            throw InvalidExpression("Error evaluating expression: " + std::string(e.what()));
        }
        bool isDetectType = std::visit([this, type](auto &&value)->bool {
            auto ref = std::make_shared<AbstractObject>(value);
            return _M_detect_value_type(ref) == type;
            }, new_value);

        // Проверяем совместимость типов
        if (!isDetectType)
        {
            throw TypeMismatchError("Type mismatch in variable declaration");
        }

        ctx.setVariable(name, new_value);
    }

    void M_handle_assignment(const std::string &command, const std::string &op)
    {
        std::istringstream stream(command);
        std::string var_name, equals;
        stream >> var_name >> equals;

        // Проверка существования переменной
        if (!ctx.findVariable(var_name))
        {
            throw UnknownVariable("Variable '" + var_name + "' not found. Use 'let' for declaration");
        }

        // Проверка синтаксиса
        if (equals == "=")
        {
            std::string expression;
            std::getline(stream, expression);
            expression = _M_trim_leading_spaces(expression);

            // Получение текущего типа переменной
            ASTValue old_value = ctx.getVariable(var_name);
            VarType old_type = std::visit([this](auto &&value)->VarType {
                auto ref = std::make_shared<AbstractObject>(value);
                return _M_detect_value_type(ref);
            }, old_value);

            // Парсинг и проверка типа
            ASTParser parser(ctx);
            auto ast_node = parser.parse(expression);

            // Оптимизация AST
            // ast_node = ASTOptimizer::optimize(ast_node);

            ASTValue new_value;
            switch (old_type)
            {
            case VarType::Variable:
                new_value = evaluate_ast_node<Variable>(ast_node);
                break;
            case VarType::Matrix:
                new_value = evaluate_ast_node<Matrix>(ast_node);
                break;
            case VarType::Vector:
                new_value = evaluate_ast_node<Vector>(ast_node);
                break;
            case VarType::Rational:
                new_value = evaluate_ast_node<Rational>(ast_node);
                break;
            default:
                throw TypeMismatchError("Cannot reassign variable of unknown type");
            }
            bool isDetectType = std::visit([this, old_type](auto &&value)->bool {
                    auto ref = std::make_shared<AbstractObject>(value);
                    return _M_detect_value_type(ref) == old_type;
            }, new_value);

            // Проверка совместимости типов
            if (!isDetectType)
            {
                throw TypeMismatchError("Type mismatch in assignment");
            }
            ctx.setVariable(var_name, new_value);
        }

        else if (equals.contains("+ - / *"))
        {
            throw InvalidSyntax("Invalid assignment operation");
        }
        else
        {
            throw InvalidSyntax("Invalid assignment operation");
        }
    }
template <typename T>
ASTValue evaluate_ast_node(std::shared_ptr<ASTNode> node)
{
    return std::visit([this](auto&& arg) -> ASTValue {
        using NodeType = std::decay_t<decltype(arg)>;
        // Обработка базовых типов
        if constexpr (std::is_same_v<NodeType, Variable> || 
                      std::is_same_v<NodeType, Matrix> || 
                      std::is_same_v<NodeType, Vector> || 
                      std::is_same_v<NodeType, Rational>) 
        {
            return arg; // Возвращаем значение как есть
        }
        // Обработка вызова функции
        else if constexpr (std::is_same_v<NodeType, FunctionCallNode>)
        {
            // Извлекаем имя функции и аргументы
            const auto& funcName = arg.Name();
            const auto& args = arg.Args();

            // Вычисляем аргументы рекурсивно
            std::vector<ASTValue> evaluatedArgs;
            for (const auto& argNode : args)
            {
                evaluatedArgs.push_back(evaluate_ast_node(argNode));
            }

            // Получаем функцию из контекста
            auto func = ctx.getFunction(funcName);
            if (!func)
            {
                throw std::runtime_error("Unknown function: " + funcName);
            }

            // Выполняем функцию
            return func->evaluate(evaluatedArgs);
        }
        else
        {
            throw std::runtime_error("Unsupported AST node type");
        }
        }, node->evaluate());
    }
    VarType
    _M_detect_value_type(const value_type &value)
    {
        auto x = value.get()->getName();
        if(x == "Variable"){
            return VarType::Variable;
        }else if (x == "Matrix"){
            return VarType::Matrix;
        }else if (x == "Vector"){
            return VarType::Vector;
        }else if (x == "Rational"){
            return VarType::Rational;
        }
        return VarType::Unknown;
    }

    Matrix _M_parse_matrix(const std::string &expression)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }

    [[nodiscard]] value_type _M_parse_rational_expression(const std::string &expression, const std::string &op)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }

    value_type _M_parse_matrix_expression(const std::string &expression, const std::string &op)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }

    value_type _M_parse_vector_expression(const std::string &expression, const std::string &op)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }

    value_type _M_parse_variable_expression(const std::string &expression, const std::string &op)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }

    void _M_print_variable(const std::string &variableName)
    {
        auto var_without_whitespace = remove_whitespaces(variableName);
        if (var_without_whitespace.empty())
        {
            return;
        }

        if (!ctx.findVariable(var_without_whitespace) && !ctx.findFunction(var_without_whitespace))
        {
            throw UnknownVariable("Variable not found: " + var_without_whitespace);
        }
        if(ctx.findFunction(var_without_whitespace)){
            auto func = ctx.getFunction(var_without_whitespace);
            func->print();
            return;
        }else{
            auto var = ctx.getVariable(var_without_whitespace);
            std::visit([this](auto &&value) {
                using ValueType = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<ValueType, Variable>) {
                    _M_print_object(std::make_shared<Variable>(value));
                } else if constexpr (std::is_same_v<ValueType, Matrix>) {
                    _M_print_object(std::make_shared<Matrix>(value));
                } else if constexpr (std::is_same_v<ValueType, Vector>) {
                    _M_print_object(std::make_shared<Vector>(value));
                } else if constexpr (std::is_same_v<ValueType, Rational>) {
                    _M_print_object(std::make_shared<Rational>(value));
                }
                else {
                    throw std::runtime_error("Unsupported AST node type");
                }
             }, var);
        }
    }
    void _M_print_object(const value_type &obj)
    {
        obj->print(std::cout);
    }

    bool _M_contains_any_symbol(const std::string &str, const std::vector<std::string> &symbols)
    {
        // Проходим по каждому символу строки str
        for (char ch : str)
        {
            // Пропускаем пробелы
            if (ch == ' ')
            {
                continue;
            }

            // Проверяем, содержится ли символ ch в любой из строк вектора symbols
            for (const std::string &symbol : symbols)
            {
                if (symbol.find(ch) != std::string::npos)
                {
                    // Если символ найден, возвращаем true
                    return true;
                }
            }
        }

        // Если ни один символ не найден, возвращаем false
        return false;
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
        throw std::runtime_error("Method is deprecated in favor of");
    }

    [[nodiscard]] bool _M_is_matrix_expression(const std::string &expr)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }

    [[nodiscard]] bool _M_is_variable_expression(const std::string &expr)
    {
        throw std::runtime_error("Method is deprecated in favor of");
    }
    [[nodiscard]] bool _M_is_rational_expression(const std::string &expr)
    {
        throw std::runtime_error("Method is deprecated in favor of");
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
        throw std::runtime_error("Method is deprecated in favor of");
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
        if (expression.find("=")!= std::string::npos){
            return true;
        }
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
