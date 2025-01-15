#include <iostream>
#include "include/variable.hpp"


int main(int argc, char** argv) {
    Variable<int> var (520);
    Variable<int> var2 (20);
    std::cout<< var + var2 << std::endl;
    std::cout<< var << std::endl;
    return 0;
}ssss