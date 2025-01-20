#ifndef DATA_H_
#define DATA_H_
#include <string>

const std::string OPERATORS = "+ - * / % += -= *= /= %= = == !=";

enum class _OPERATORS{
    ADD = 0x80, 
    SUB, 
    MUL, 
    DIV, 
    MOD, 
    ADD_EQUAL, 
    SUB_EQUAL, 
    MUL_EQUAL, 
    DIV_EQUAL, 
    MOD_EQUAL, 
    EQUAL, 
    NOT_EQUAL,
    NONE
};
#endif /* DATA_H_ */