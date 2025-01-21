#include  "../include/function/base.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "../include/types/variable.hpp"
#include "../include/types/vector.hpp"
#include "../include/types/matrix.hpp"
#include "../include/types/rational.hpp"

std::string get_function_name(const FunctionType func_type) {
    if (func_type == FunctionType::Sin) {
        return "_M_sin";
    }
    else if (func_type == FunctionType::Cos) {
        return "_M_cos";
    }
    else if (func_type == FunctionType::Transpose) {
        return "t";
    }
}
FunctionType get_function_type(const std::string& func_name) {
    if (func_name == "sin") {
        return FunctionType::Sin;
    } else if (func_name == "cos") {
        return FunctionType::Cos;
    } else if (func_name == "T") {
        return FunctionType::Transpose;
    } else {
        return FunctionType::Undefined;
    }
}


Variable _M_sin(Variable& x) {
    if(const auto type_v = x.getType(); type_v == "INT") {
        return Variable(std::sin(x.getValue<int>()));
    }
    else if(type_v == "FLOAT") {
        return Variable(std::sin(x.getValue<float>()));
    }
    else if(type_v == "FLOAT") {
        return Variable(std::sin(x.getValue<double>()));
    }
    else {
        throw std::invalid_argument("Unsupported numeric type");
    }
}

///@brief _M_cos function for variable
Variable _M_cos(Variable& x) {
    if(const auto type_v = x.getType(); type_v == "INT") {
        return Variable(std::sin(x.getValue<int>()));
    }
    else if(type_v == "FLOAT") {
        return Variable(std::sin(x.getValue<float>()));
    }
    else if(type_v == "FLOAT") {
        return Variable(std::sin(x.getValue<double>()));
    }
    else {
        throw std::invalid_argument("Unsupported numeric type");
    }
}

///@brief _M_sin function for vector
Vector _M_sin(Vector& x) {
    Vector res;
    std::for_each(x.begin(), x.end(),[&res](Variable& var_) {
        res.push_back(_M_sin(var_));
    });
    return res;

}

///@brief _M_cos function for vector
Vector _M_cos(Vector& x) {
    Vector res;
    std::for_each(x.begin(), x.end(),[&res](Variable& var_) {
        res.push_back(_M_cos(var_));
    });
    return res;
}

///@brief _M_sin function for matrix
Matrix _M_sin(Matrix& x) {
    Matrix mat;
    std::for_each(x.begin(), x.end(),[&mat](Vector& var_) {
        mat.push_back(_M_sin(var_));
    });
    return mat;
}

///@brief _M_cos function for matrix
Matrix _M_cos( Matrix& x) {
    Matrix mat;
    std::for_each(x.begin(), x.end(),[&mat](Vector& var_) {
        mat.push_back(_M_cos(var_));
    });
    return mat;
}

///@brief _M_sin function for rational
Rational _M_sin(const Rational& x) {
    auto var = x.getNum() / x.getDen();
    return Rational(_M_sin(var));
}

///@brief _M_cos function for rational
Rational _M_cos( Rational& x) {
    auto var = x.getNum() / x.getDen();
    return Rational(_M_cos(var));
}