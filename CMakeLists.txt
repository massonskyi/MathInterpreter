cmake_minimum_required(VERSION 3.16)
project(MathInterpreter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
# Paths to your prebuilt Google Test libraries
set(GTEST_ROOT "C:/gtest") # Replace with the actual path to your GTest root directory
set(GTEST_INCLUDE_DIR "${GTEST_ROOT}/include")
set(GTEST_LIB_DIR "${GTEST_ROOT}/lib") # Path to your compiled GTest libraries

# Include and link directories for Google Test
include_directories(${GTEST_INCLUDE_DIR})
link_directories(${GTEST_LIB_DIR})

add_executable(MathInterpreter 
        main.cxx
        include/base/abstractcontainertype.h
        include/base/abstractobject.h
        include/base/abstractsimpletype.h
        include/core.h
        include/types/variable.h
        include/types/rational.h
        include/types/vector.h
        include/types/matrix.h
        include/interpreter.h

        src/types/variable.cxx
        src/types/rational.cxx
        src/types/matrix.cxx
        src/parsers/matrixparser.cxx
        src/parsers/rationalparser.cxx
        src/parsers/vectorparser.cxx
        src/parsers/variableparser.cxx

        include/parsers/regexmanager.h
        include/parsers/variableparser.h
        include/parsers/vectorparser.h
        include/parsers/matrixparser.h
        include/parsers/rationalparser.h
        include/function/types.h
        include/function/base.h
        include/exceptions/exceptions.h
        src/base.cxx
        lib/cxxopts-3.2.0/include/cxxopts.hpp
        include/types/types.h
        include/utils.h
        include/function/typedetector.h
        src/utils.cxx
        src/types/vector.cxx
        
        include/io/io.h
        include/io/ioreader.h
        include/io/iowriter.h
        include/validators/functionbodyvalidator.h
        include/ast/ast.h
        include/ast/ast_parser.h
        )

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

