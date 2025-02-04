//
// Created by massonskyi on 23.01.25.
//

#ifndef MATHINTERPRETER_UTILS_H
#define MATHINTERPRETER_UTILS_H
#include <type_traits>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <memory>
#include "base/abstractobject.h"

#include "types/types.h"


// Concept for allowed entity types
template<typename T>
concept EntityType = std::same_as<T, int> ||
std::same_as<T, float> ||
std::same_as<T, double> ||
std::same_as<T, std::string>;

// Type-safe smart pointer creation utilities
template<typename T>
requires std::is_base_of_v<AbstractObject, T>
auto make_object_ptr(auto&& obj) {
    return std::make_shared<T>(std::forward<decltype(obj)>(obj));
}

// Specialized pointer creation functions
inline auto make_vector_ptr(const auto& vec) {
    return std::make_shared<Vector>(vec);
}

inline auto make_matrix_ptr(const auto& mat) {
    return std::make_shared<Matrix>(mat);
}

inline auto make_rational_ptr(const auto& rat) {
    return std::make_shared<Rational>(rat);
}


inline auto make_variable_ptr(const auto& var) {
    return std::make_shared<Variable>(var);
}

// Safer insertion and assignment utilities
template<typename Container, typename Key, typename Value>
void append_(Container& obj, const Key& name, Value&& var) {
    obj.emplace(name, std::forward<Value>(var));
}

template<typename Container, typename Key, typename Value>
void upload_(Container& obj, const Key& name, Value&& var) {
    obj.setVariable(name, std::forward<Value>(var));
}

// Compile-time string conversion utilities
template<typename T>
constexpr std::string_view stringify(T&& x) {
    return std::string_view{x};
}

std::string to_lower(const std::string& s);

std::string remove_whitespaces(const std::string &str);
#endif //MATHINTERPRETER_UTILS_H
