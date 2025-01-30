#include "../../include/parsers/vectorparser.hxx"
VectorParser::value_type
VectorParser::parse(const std::string& expr, size_t& index) {
    Vector _M_vector;
    if (expr[index] != '[') {
        throw std::runtime_error("Expected '[' at the beginning of vector.");
    }
    ++index;

    while(index < expr.size() && expr[index] != ']') {
        while(index < expr.size() && isspace(expr[index])) {
            ++index;
        }

        Variable var(VariableParser::parse(expr, index));
        _M_vector.push_back(var);

        while(index < expr.size() && isspace(expr[index])) {
            ++index;
        }

        if(expr[index] == ',') {
            ++index;
        }
    }
    if (expr[index] != ']') {
        throw std::runtime_error("Expected ']' at the end of vector.");
    }

    ++index;

    return _M_vector;
}
// Статический метод для проверки, является ли строка вектором
bool VectorParser::search(const std::string& expr) {
    size_t index = 0;

    while (index < expr.size() && isspace(expr[index])) ++index;

    if (expr[index] != '[') return false;
    ++index;

    bool elementStarted = false;
    while (index < expr.size() && expr[index] != ']') {
        while (index < expr.size() && isspace(expr[index])) {
            ++index;
        }

        if (VariableParser::search(expr, index)) {
            elementStarted = true;
            VariableParser::parse(expr, index);
        }

        while (index < expr.size() && isspace(expr[index])) {
            ++index;
        }

        if (expr[index] == ',') {
            ++index;
        }
    }
    while (index < expr.size() && isspace(expr[index])) ++index;
    return expr[index] == ']' && elementStarted;
}