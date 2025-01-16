#include <iostream>
#include "include/variable.hpp"
// #include "include/rational.hpp"
// #include "include/vector.hpp"
// #include "include/matrix.hpp"
#include "include/rational.hpp"
#include "include/utils.hpp"
#include "include/vector.hpp"

int main(int argc, char** argv) {
    Variable var;
    var.setValue(55);
    std::cout<<var<<std::endl;
    Vector vec(5);
    for (int i = 0; i < 5; i++) {
        vec[i].setValue((i + 1));
    }
    vec.print();
    // var += 6;
    // std::cout << (var + 2).getName()<<(var + 2).getTypeName() << std::endl;
    return 0;
}