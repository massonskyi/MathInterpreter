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

#include "data/data.hxx"
#include "base/abstractobject.hxx"
#include "exceptions/exceptions.hxx"

#include "types/matrix.tpp"
#include "types/variable.tpp"
#include "types/vector.tpp"
#include "types/rational.tpp"

#include "parsers/regexmanager.hxx"
#include "parsers/matrixparser.hxx"
#include "parsers/vectorparser.hxx"
#include "parsers/rationalparser.hxx"
#include "parsers/variableparser.hxx"
#include "parsers/expressionparser.tpp"
#include "parsers/stringvalidator.hxx"

#include "function/base.hxx"
#include "function/binaryexecuter.tpp"


class Interpreter final
{
public:
    enum class VarType { Variable, Matrix, Vector, Rational, Unknown};
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
        append_(_M_regexes, "LetDeclaration",
                std::regex(R"(^let\s+(\w+)\s*:\s*(\w+)\s*=\s*(.+)$)"));
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
                if (_M_contains_any_symbol(line, RESERVED.at(0)))
                {
                    if (std::string op = _M_find_contains_symbol(line, RESERVED.at(0)); !op.empty())
                        _M_execute_command(line, op);
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
        std::cout <<"Processing file: " << filename << std::endl;
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
                if (_M_contains_any_symbol(line, RESERVED.at(0)))
                {
                    if (std::string op = _M_find_contains_symbol(line, RESERVED.at(0)); !op.empty())
                        _M_execute_command(line, op);
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

    // Модифицируем _M_execute_command
    void
    _M_execute_command(const std::string &command, const std::string& op) {
        std::istringstream stream(command);
        std::string token;
        stream >> token;

        // Случай: создание новой переменной с let
        if (token == "let") {
            _M_handle_let_declaration(stream, op);
        }
            // Случай: присваивание существующей переменной
        else {
            _M_handle_assignment(command, op);
        }
    }

    void
    _M_handle_let_declaration(std::istringstream& stream, const std::string& op) {
        std::string full_decl;
        std::getline(stream, full_decl); // Читаем всю оставшуюся часть строки

        size_t comment_pos = full_decl.find('#');
        if (comment_pos != std::string::npos) {
            full_decl = full_decl.substr(0, comment_pos);
        }

        // Новое регулярное выражение с гибкими пробелами
        static const std::regex let_regex(
                R"(^\s*([a-zA-Z_]\w*)\s*:\s*([a-zA-Z]+)\s*=\s*(.+)\s*$)",
                std::regex::ECMAScript | std::regex::icase
        );

        std::smatch match;
        if (!std::regex_match(full_decl, match, let_regex)) {
            throw InvalidSyntax("Invalid let declaration format");
        }

        const std::string var_name = match[1].str();
        const std::string type_str = to_lower(match[2].str());
        const std::string expression = match[3].str();

        if (expression.empty()) {
            throw InvalidSyntax("Missing value in declaration");
        }

        if (_M_variables.find(var_name) != _M_variables.end()) {
            throw RedeclarationError("Variable '" + var_name + "' already exists");
        }

        VarType type = _M_parse_type(type_str);
        _M_create_variable(var_name, type, expression, op);
    }

    VarType
    _M_parse_type(const std::string& type_str) {
        static const std::unordered_map<std::string, VarType> type_map = {
                {"num", VarType::Variable},
                {"mat", VarType::Matrix},
                {"vec", VarType::Vector},
                {"rat", VarType::Rational}
        };

        auto it = type_map.find(type_str);
        if (it == type_map.end()) {
            throw InvalidTypeError("Unknown type: " + type_str);
        }
        return it->second;
    }
    void _M_create_variable(const std::string& name, VarType type, const std::string& expression, const std::string& op) {
        switch (type) {
            case VarType::Variable:
                upload_(_M_variables, name,_M_parse_expression<Variable>(expression, op));
                break;
            case VarType::Matrix:
                upload_(_M_variables, name,_M_parse_expression<Matrix>(expression, op));
                break;
            case VarType::Vector:
                upload_(_M_variables, name,_M_parse_expression<Vector>(expression, op));
                break;
            case VarType::Rational:
                upload_(_M_variables, name,_M_parse_expression<Rational>(expression, op));
                break;
            default:
                throw InvalidTypeError("Unsupported type for variable creation");
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
            throw std::runtime_error("Ошибка при разборе вектора: " + std::string(e.what()));
        }
    }
    void _M_handle_assignment(const std::string& command, const std::string& op) {
        std::istringstream stream(command);
        std::string var_name, equals;
        stream >> var_name >> equals;

        // Проверка существования переменной
        if (_M_variables.find(var_name) == _M_variables.end()) {
            throw UnknownVariable("Variable '" + var_name + "' not found. Use 'let' for declaration");
        }

        // Проверка синтаксиса
        if (equals != "=") {
            throw InvalidSyntax("Missing '=' in assignment");
        }

        std::string expression;
        std::getline(stream, expression);
        expression = _M_trim_leading_spaces(expression);

        // Получение текущего типа переменной
        auto& old_value = _M_variables[var_name];
        VarType old_type = _M_detect_value_type(old_value);

        // Парсинг и проверка типа
        value_type new_value;
        switch (old_type) {
            case VarType::Variable:
                new_value = _M_parse_expression<Variable>(expression, op);
                break;
            case VarType::Matrix:
                new_value = _M_parse_expression<Matrix>(expression, op);
                break;
            case VarType::Vector:
                new_value = _M_parse_expression<Vector>(expression, op);
                break;
            case VarType::Rational:
                new_value = _M_parse_expression<Rational>(expression, op);
            default:
                throw TypeMismatchError("Cannot reassign variable of unknown type");
        }

        // Проверка совместимости типов
        if (_M_detect_value_type(new_value) != old_type) {
            throw TypeMismatchError("Type mismatch in assignment");
        }

        _M_variables[var_name] = new_value;
    }

    VarType
    _M_detect_value_type(const value_type& value) {
        if (dynamic_cast<Variable*>(value.get())) return VarType::Variable;
        if (dynamic_cast<Matrix*>(value.get())) return VarType::Matrix;
        if (dynamic_cast<Vector*>(value.get())) return VarType::Vector;
        if (dynamic_cast<Rational*>(value.get())) return VarType::Rational;
        return VarType::Unknown;
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

    [[nodiscard]] value_type _M_parse_rational_expression(const std::string &expression, const std::string &op)
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
            return make_rational_ptr(Rational(Variable(numerator), Variable(denominator)));
        }
        else
        {
            return _M_binary_executer.calculate(expression, _M_variables);
        }
    }

    value_type _M_parse_matrix_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;
        // Matrix literal
        if (std::regex_match(expression, match, _M_regexes.find("MatrixLiteral")->second))
        {
            return make_matrix_ptr(_M_parse_matrix(expression));
        }
        else
        {
            return _M_binary_executer.calculate(expression, _M_variables);
        }
    }

    value_type _M_parse_vector_expression(const std::string &expression, const std::string &op)
    {
        std::smatch match;

        // Direct number assignment
        if (std::regex_match(expression, match, _M_regexes.find("VectorLiteral")->second))
        {
            return make_vector_ptr(Vector(_M_parse_vector(expression)));
        }
        else
        {
            return _M_binary_executer.calculate(expression, _M_variables);
        }
    }

    value_type _M_parse_variable_expression(const std::string& expression, const std::string& op)
    {
        std::smatch match;

        // Direct number assignment
        if (std::regex_match(expression, match, _M_regexes.find("VariableLiteral")->second))
        {
            return make_variable_ptr(Variable(std::stoi(expression)));
        }
        else
        {
            return _M_binary_executer.calculate(expression, _M_variables);
        }
    }

    void _M_print_variable(const std::string &variableName)
    {
        auto var_without_whitespace = remove_whitespaces(variableName);
        if (var_without_whitespace.empty())
        {
            return;
        }

        const auto it = _M_variables.find(var_without_whitespace);
        if (it == _M_variables.end())
        {
            throw UnknownVariable("Variable not found: " + var_without_whitespace);
        }

        std::cout << *it->second << std::endl;
    }

    void _M_print_object(const value_type &obj)
    {
        std::cout << *obj << std::endl;
    }

    bool _M_contains_any_symbol(const std::string &str, const std::vector<std::string> &symbols)
    {
        // Проходим по каждому символу строки str
        for (char ch : str) {
            // Пропускаем пробелы
            if (ch == ' ') {
                continue;
            }

            // Проверяем, содержится ли символ ch в любой из строк вектора symbols
            for (const std::string &symbol : symbols) {
                if (symbol.find(ch) != std::string::npos) {
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
