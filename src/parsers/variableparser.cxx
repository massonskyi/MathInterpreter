#include "../../include/parsers/variableparser.h"


VariableParser::value_type
VariableParser::parse(const std::string& expr, size_t& index){
    auto _M_var = Variable();
    while(index < expr.size() && isdigit(expr[index])) {
        _M_var = _M_var * 10 + (expr[index] - '0');
        ++index;
    };
    return _M_var;
}

bool VariableParser::search(const std::string& expr, size_t& index) {

    if (index < expr.size() && isdigit(expr[index])) {
        while (index < expr.size() && isdigit(expr[index])) {
            ++index;
        }
        return true;
    }
    return false;
}