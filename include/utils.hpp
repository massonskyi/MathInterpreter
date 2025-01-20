#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

template <typename T>
using uncostT = std::remove_const_t<std::decay_t<T>>;

#endif /* UTILS_HPP */