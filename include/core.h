#ifndef CORE_H_
#define CORE_H_

#include <type_traits>
#include <concepts>
#include <cstdint>
#include <iostream>
/// @brief This concept macro is used to check if a type is allowed.
template<typename T>
concept AllowedTypes =
    std::is_same_v<T, int>      ||
    std::is_same_v<T, float>    ||
    std::is_same_v<T, double>;

enum class Type {
    INT = 0x00,
    DOUBLE,
    FLOAT,
    OTHER,
};

enum class CustomType {
    Variable=0x10,
    RATIONAL,
    VECTOR,
    MATRIX,
    // ARRAY,
    // MAP
};



#endif /* CORE_H_ */