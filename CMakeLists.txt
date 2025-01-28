cmake_minimum_required(VERSION 3.16)
project(MathInterpreter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Paths to your prebuilt Google Test libraries
set(GTEST_ROOT "C:/gtest") # Replace with the actual path to your GTest root directory
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/include")
set(GTEST_LIB_DIR "${GTEST_ROOT}/lib") # Path to your compiled GTest libraries

# Include and link directories for Google Test
include_directories(${GTEST_INCLUDE_DIR})
link_directories(${GTEST_LIB_DIR})


add_executable(MathInterpreter 
        main.cxx
        include/base/abstractcontainertype.hxx
        include/base/abstractobject.hxx
        include/base/abstractsimpletype.hxx
        include/core.tpp
        include/types/variable.tpp
        include/types/rational.tpp
        include/types/vector.tpp
        include/types/matrix.tpp
        include/interpreter.tpp

        src/variable.cxx
        src/rational.cxx
        include/parsers/regexmanager.hxx
        include/parsers/variableparser.hxx
        include/parsers/vectorparser.hxx
        include/parsers/matrixparser.hxx
        include/parsers/rationalparser.hxx
        include/parsers/expressionparser.tpp
        include/function/types.hxx
        include/function/base.hxx
        include/function/binaryexecuter.tpp
        include/exceptions/exceptions.hxx
        src/base.cxx
        lib/cxxopts-3.2.0/include/cxxopts.hpp
        src/binaryexecute.cxx
        include/types/types.hxx
        include/utils.tpp
        include/function/typedetector.hxx
        src/utils.cxx
        src/vector.cxx)

# Add tests
enable_testing()

# file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
# if(TEST_SOURCES)
#     add_executable(MathInterpreterTests ${TEST_SOURCES})
#     target_include_directories(MathInterpreterTests PRIVATE include)
#     target_link_libraries(MathInterpreterTests
#         PRIVATE
#         include/variable.hpp
#         ${GTEST_LIB_DIR}/libgtest.a
#         ${GTEST_LIB_DIR}/libgtest_main.a
#         pthread
#     )
#     add_test(NAME MathInterpreterTests COMMAND MathInterpreterTests)
# endif()

