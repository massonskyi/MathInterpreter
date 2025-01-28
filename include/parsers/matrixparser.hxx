#ifndef MATRIXPARSER_HPP
#define MATRIXPARSER_HPP

#include "vectorparser.hxx"
#include "../types/matrix.tpp"
#include "../types/vector.tpp"
#include "../types/variable.tpp"

class MatrixParser final {
public:
    static Matrix parse(const std::string& expr, size_t& index) {
        Matrix _M_matrix;

        while (index < expr.size() && isspace(expr[index])) ++index;
        if (expr[index] != '[') {
            throw std::runtime_error("Expected '[' at the beginning of matrix.");
        }
        ++index;


        while(index < expr.size() - 1) {
            while (index < expr.size() && isspace(expr[index])) ++index;
            if (expr[index] == '[') {
                Vector row = VectorParser::parse(expr, index);
                _M_matrix.push_back(row);
            }
            while(index < expr.size() && isspace(expr[index])) ++index;
            if(expr[index] == ',') ++index;
        };

        if(expr[index] != ']') {
            throw std::runtime_error("Expected ']' at the end of matrix.");
        };

        ++index;

        return _M_matrix;
    };

    static bool search(const std::string& expr) {
        size_t index = 0;

        while (index < expr.size() && isspace(expr[index])) ++index;

        if (expr[index] != '[') return false;
        ++index;

        bool rowStarted = false;
        while (index < expr.size()) {
            while (index < expr.size() && isspace(expr[index])) ++index;
            if (expr[index] == '[') {
                rowStarted = true;
                VectorParser::parse(expr, index);
            }
            while (index < expr.size() && isspace(expr[index])) ++index;
            if (expr[index] == ',') {
                ++index;
            }
            if (expr[index] == ']') {
                break;
            }
        }

        while (index < expr.size() && isspace(expr[index])) ++index;
        return expr[index] == ']' && rowStarted;
    }
};
#endif //MATRIXPARSER_HPP
