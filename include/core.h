#ifndef CORE_H_
#define CORE_H_

#include <type_traits>
#include <concepts>
#include <cstdint>

/// @brief This concept macro is used to check if a type is allowed.
template<typename T>
concept AllowedTypes =
    std::is_same_v<T, uint8_t>  ||
    std::is_same_v<T, int8_t>   ||
    std::is_same_v<T, uint16_t> ||
    std::is_same_v<T, int16_t>  ||
    std::is_same_v<T, uint32_t> ||
    std::is_same_v<T, int32_t>  ||
    std::is_same_v<T, uint64_t> ||
    std::is_same_v<T, int64_t>  ||
    std::is_same_v<T, int>      ||
    std::is_same_v<T, float>    ||
    std::is_same_v<T, double>;

template<AllowedTypes T>
class Variable;

template <typename T>
concept IsVariable = requires {
    typename T::value_type;
    requires std::is_same_v<T, Variable<typename T::value_type>>;
};

enum class Type {
    INT = 0x00,
    DOUBLE,
    FLOAT,
    OTHER
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