#include <iostream>
#include "include/variable.hpp"
// #include "include/rational.hpp"
// #include "include/vector.hpp"
// #include "include/matrix.hpp"
#include "include/rational.hpp"
#include "include/utils.hpp"
int main(int argc, char** argv) {
    Variable var (2);
    Rational rat (var);
    Rational rat2 (Variable(10), Variable(25));
    std::cout<< rat2 + rat <<std::endl;
    // var += 6;
    // std::cout << (var + 2).getName()<<(var + 2).getTypeName() << std::endl;
    return 0;
}