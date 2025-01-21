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
        main.cpp
        include/base/abstractcontainertype.h
        include/base/abstractobject.h
        include/base/abstractsimpletype.h
        include/core.h
        include/types/variable.hpp
        include/types/rational.hpp
        include/types/vector.hpp
        include/types/matrix.hpp
        include/interpreter.hpp

        src/variable.cpp
        src/rational.cpp
        include/parsers/regexmanager.hpp
        include/parsers/variableparser.hpp
        include/parsers/vectorparser.hpp
        include/parsers/matrixparser.hpp
        include/parsers/rationalparser.hpp
        include/function/core.h
        include/function/base.hpp
        src/base.cpp
        lib/cxxopts-3.2.0/include/cxxopts.hpp
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

