#ifndef DATA_HXX_
#define DATA_HXX_
#include <string>
#include <vector>

/// @brief This is all avalaible reserved words
const std::vector<std::string> RESERVED = {
    "+ - * / % += -= *= /= %= = == != fn",
    " let if else for for_each loop match using "
};

enum class Operator{
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

#endif /* DATA_HXX_ */