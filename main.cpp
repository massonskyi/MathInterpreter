#include <iostream>
#include "include/variable.hpp"
#include "include/rational.hpp"
#include "include/vector.hpp"
#include "include/matrix.hpp"
#include "include/interpreter.h"
int main(int argc, char** argv) {
    Interpreter interpreter;
    interpreter.processConsole();
    return 0;
}