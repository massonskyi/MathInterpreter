#ifndef VARIABLEPARSER_HPP
#define VARIABLEPARSER_HPP
#ifdef __GNUG__
#include <bits/ranges_algo.h>
#else
#include <ranges>
#endif
#include "../types/variable.hpp"


class VariableParser final{
public:
    static Variable parse(const std::string& expr, size_t& index){
        auto _M_var = Variable();
        while(index < expr.size() && isdigit(expr[index])) {
            _M_var = _M_var * 10 + (expr[index] - '0');
            ++index;
        };
        return _M_var;
    }

    static bool search(const std::string& expr, size_t& index) {
        if (index < expr.size() && isdigit(expr[index])) {
            while (index < expr.size() && isdigit(expr[index])) {
                ++index;
            }
            return true;
        }
        return false;
    }
private:

};
#endif //VARIABLEPARSER_HPP
