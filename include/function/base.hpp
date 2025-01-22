#ifndef FUNCTION_BASE_HPP
#define FUNCTION_BASE_HPP

#include "core.h"

class Variable;
class Vector;
class Matrix;
class Rational;

///@brief get function name
///@param func_type
///@return function name
std::string get_function_name(const FunctionType func_type);

///@brief get function type
///@param func_name
///@return function type
FunctionType get_function_type(const std::string& func_name);


Rational _M_create_rat(Variable& x);
///@brief _M_sin function for variable
Variable _M_sin( Variable& x);

///@brief _M_cos function for variable
Variable _M_cos( Variable& x);

///@brief _M_sin function for vector
Vector _M_sin( Vector& x);

///@brief _M_cos function for vector
Vector _M_cos( Vector& x);

///@brief _M_sin function for matrix
Matrix _M_sin( Matrix& x);

///@brief _M_cos function for matrix
Matrix _M_cos( Matrix& x);

///@brief _M_sin function for rational
Rational _M_sin(const Rational& x);

///@brief _M_cos function for rational
Rational _M_cos( Rational& x);

#endif //FUNCTION_BASE_HPP
