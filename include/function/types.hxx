//
// Created by massonskyi on 21.01.25.
//

#ifndef FUNCTION_CORE_H
#define FUNCTION_CORE_H
#include <string>
#include <unordered_set>

///@brief Function avalaible types
enum class FunctionType {
    Sin,
    Cos,
    Transpose,
    Tan,
    Log,
    Exp,
    Sqrt,
    CreateRat,
    Undefined
};

static const std::unordered_set<std::string> functions = {"sin", "cos", "T", "tan", "log", "exp", "sqrt", "create_rat"};

#endif //FUNCTION_CORE_H
