#ifndef LAMBDAINTERPRETER_H
#define LAMBDAINTERPRETER_H
#include "../ast/ast.h"

// Реализация функции sin
auto sin_function = [](std::vector<ASTValue>& args) -> ASTValue {
    if (args.size() != 1) {
        throw std::runtime_error("Function 'sin' expects 1 argument");
    }
    return std::visit([](auto&& arg) -> ASTValue {
        return _M_sin(arg); // Вызов соответствующей реализации _M_sin
    }, args[0]);
};

// Реализация функции cos
auto cos_function = [](std::vector<ASTValue>& args) -> ASTValue {
    if (args.size() != 1) {
        throw std::runtime_error("Function 'cos' expects 1 argument");
    }
    return std::visit([](auto&& arg) -> ASTValue {
        return _M_cos(arg); // Вызов соответствующей реализации _M_cos
    }, args[0]);
};

#endif // LAMBDAINTERPRETER_H