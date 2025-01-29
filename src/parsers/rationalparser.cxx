#include "../../include/parsers/rationalparser.hxx"
#include "../../include/parsers/variableparser.hxx"

RationalParser::value_type
RationalParser::parse(const std::string& expr, size_t& index) {
    const auto _M_num = VariableParser::parse(expr, index);
    while(index < expr.size() && isspace(expr[index])) {
        ++index;
    }
    if(expr[index] != '/') {
        throw std::runtime_error("Expected '/' in rational number.");
    }
    ++index;
    const auto _M_den = VariableParser::parse(expr, index);
    return Rational(_M_num, _M_den);
}


// Статический метод для проверки, является ли строка рациональным числом
bool RationalParser::search(const std::string& expr) {
    size_t index = 0;

    // Пропускаем начальные пробелы
    while (index < expr.size() && isspace(expr[index])) ++index;

    // Проверка на первый числитель (целое число)
    if (!VariableParser::search(expr, index)) return false;

    // Пропускаем пробелы после числителя
    while (index < expr.size() && isspace(expr[index])) ++index;

    // Проверка на наличие символа '/'
    if (expr[index] != '/') return false;
    ++index;

    // Пропускаем пробелы после '/'
    while (index < expr.size() && isspace(expr[index])) ++index;

    // Проверка на знаменатель (целое число)
    if (!VariableParser::search(expr, index)) return false;

    // Пропускаем пробелы после знаменателя
    while (index < expr.size() && isspace(expr[index])) ++index;

    // Проверка на конец строки
    return index == expr.size();
}