#ifndef UTILS_HPP
#define UTILS_HPP

#include "core.h"


std::ostream& operator<<(std::ostream& os, Type type) {
    switch (type) {
        case Type::INT:
            os << "INT";
            break;
        case Type::DOUBLE:
            os << "DOUBLE";
            break;
        case Type::FLOAT:
            os << "FLOAT";
            break;
        case Type::OTHER:
            os << "OTHER";
            break;
        default:
            os << "Unknown Type";  // Handling any future or undefined types
            break;
    }
    return os;
}
#endif /* UTILS_HPP */