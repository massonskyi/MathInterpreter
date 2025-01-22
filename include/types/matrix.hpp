#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../core.h"
#include "vector.hpp"

#include <vector>
#include <stdexcept>
#include <sstream>

/// @brief Matrix is a class that represents a matrix
class Matrix final : public AbstractContainerType
{
public:
    using AbstractContainerType::AbstractContainerType;

    // Constructors
    Matrix(): AbstractContainerType(extractClassName()), data_({}) {}

    explicit Matrix(const size_t rows, const size_t cols)
        : AbstractContainerType(extractClassName()), data_(rows, Vector(cols)) {}

    Matrix(const std::initializer_list<Vector> list)
        : AbstractContainerType(extractClassName()), data_(list)
    {
        if (!list.size() == 0)
        {
            const size_t cols = list.begin()->size();
            for (const auto &row : list)
            {
                if (row.size() != cols)
                {
                    throw std::invalid_argument("All rows must have the same size");
                }
            }
        }
    }

    // Copy and move constructors
    Matrix(const Matrix &other) noexcept
        : AbstractContainerType(extractClassName()), data_(other.data_) {}

    Matrix(Matrix &&other) noexcept
        : AbstractContainerType(extractClassName()), data_(std::move(other.data_)) {}

    /// @brief Destructor for the Matrix class
    ~Matrix() = default;
    // Виртуальный метод для вывода
    void print(std::ostream &os) const override
    {
        std::cout << *this << std::endl;
    }
    /// @brief This method returns object by index its index container
    /// @param index of the object
    /// @return object by index
     [[nodiscard]] AbstractObject get() const override
    {
        throw std::runtime_error("Not implemented");
    }

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
     [[nodiscard]] string toString() const override
    {
        std::stringstream ss;
        ss << "[";

        for (size_t i = 0; i < rows(); ++i)
        {
            ss << "[";
            for (size_t j = 0; j < cols(); ++j)
            {
                ss << data_.at(i).at(j);
                if (j != cols() - 1)
                    ss << ", ";
            }
            if (i !=  rows() - 1)
                ss << "],";
            else {
                ss << "]";
            }
        }

        ss << "]";
        return ss.str(); // Возвращаем строковое представление объекта
    }

    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
     string getTypeName() const override
    {
        return typeid(*this).name(); // Возвращаем строку, представляющую тип объекта
    }

    // Size operations
     size_t rows() const { return data_.size(); }
     size_t cols() const { 
         return data_.empty() ? 0 : data_[0].size(); 
     }

    // Access operations
     Vector &operator[](size_t index) { return data_[index]; }
     const Vector &operator[](size_t index) const { return data_[index]; }

     Vector &at(size_t index) { return data_.at(index); }
     const Vector &at(size_t index) const { return data_.at(index); }

     Variable get(size_t row, size_t col) const
    {
        return data_.at(row).get(col);
    }

    // Modifiers
     void push_back(const Vector &row)
    {
        if (!data_.empty() && row.size() != cols())
        {
            throw std::invalid_argument("Row size doesn't match matrix columns");
        }
        data_.push_back(row);
    }

     void pop_back()
    {
        if (data_.empty())
        {
            throw std::out_of_range("Matrix is empty");
        }
        data_.pop_back();
    }

     void clear()
    {
        data_.clear();
    }

     void resize(size_t rows, size_t cols)
    {
        data_.resize(rows, Vector(cols));
        for (auto &row : data_)
        {
            row.resize(cols);
        }
    }

    // Matrix operations
    Matrix transpose() const
    {
        if (data_.empty())
            return Matrix();

        Matrix result(cols(), rows());
        for (size_t i = 0; i < rows(); ++i)
        {
            for (size_t j = 0; j < cols(); ++j)
            {
                result[j][i] = data_[i].get(j);
            }
        }
        return result;
    }
    /// @brief This method swaps two containers
    /// @param other container
     void swap(Matrix &other) noexcept
    {
        try
        {
            data_.swap(other.data_);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] swap: " << e.what() << std::endl;
            // Исключение не выбрасывается, так как метод объявлен noexcept
        }
    }
    /// @brief This method returns begin iterator of the container
    /// @return begin iterator of the container
    std::vector<Vector>::iterator begin() noexcept
    {
        return data_.begin();
    }

    /// @brief This method returns end iterator of the container
    /// @return end iterator of the container
    std::vector<Vector>::iterator end() noexcept
    {
        return data_.end();
    }

    /// @brief This method returns const begin iterator of the container
    /// @return const begin iterator of the container
    std::vector<Vector>::const_iterator cbegin() const noexcept
    {
        return data_.cbegin();
    }

    /// @brief This method returns const end iterator of the container
    /// @return const end iterator of the container
    std::vector<Vector>::const_iterator cend() const noexcept
    {
        return data_.cend();
    }
    // Operators
    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            data_ = other.data_;
        }
        return *this;
    }

    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this != &other)
        {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    bool operator==(const Matrix &other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }

    // Arithmetic operators
    Matrix operator+(const Matrix &other)const
    {
        if (rows() != other.rows() || cols() != other.cols())
        {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] =  data_[i] + other[i];
        }
        return result;
    }
    Matrix operator+(const Vector& other) const
    {
        if (cols() != other.size())
        {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] + other;
        }
        return result;
    }
    Matrix operator+(Variable& other)
    {
        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] + other;
        }
        return result;
    }
    Matrix operator-(const Matrix &other) const
    {
        if (rows() != other.rows() || cols() != other.cols())
        {
            throw std::invalid_argument("Matrix dimensions must match for subtraction");
        }

        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] - other[i];
        }
        return result;
    }
    Matrix operator-(const Vector& other) const
    {
        if (cols() != other.size())
        {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] - other;
        }
        return result;
    }
    Matrix operator-(Variable& other)
    {
        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] - other;
        }
        return result;
    }
    Matrix operator*(const Matrix &other) const
    {
        if (cols() != other.rows())
        {
            throw std::invalid_argument("Invalid dimensions for matrix multiplication");
        }

        Matrix result(rows(), other.cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            for (size_t j = 0; j < other.cols(); ++j)
            {
                Variable sum(0);
                for (size_t k = 0; k < cols(); ++k)
                {
                    sum += data_[i].get(k) * other[k].get(j);
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    Matrix operator*(const Vector& other) const
    {
        if (cols() != other.size())
        {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }
        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] * other;
        }
        return result;
    }

    Matrix operator*(Variable& other)
    {
        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] * other;
        }
        return result;
    }

    Matrix operator/(const Matrix& mat) const {
        if (rows() != mat.rows() || cols() != mat.cols())
        {
            throw std::invalid_argument("Vector size must match matrix columns for division");
        }

        // Check for division by zero in vector
        for (size_t i = 0; i < mat.rows(); ++i)
        {
            for (size_t j = 0; j < mat.cols(); ++j) {
                if (mat.get(i, j) == 0)
                {
                    throw std::invalid_argument("Division by zero in vector");
                }
            }
        }

        Matrix result = *this;
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] /= mat[i];
        }
        return result;
    }

    Matrix operator/(const Vector& vec) const
    {
        if (cols() != vec.size())
        {
            throw std::invalid_argument("Vector size must match matrix columns for division");
        }

        // Check for division by zero in vector
        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (vec.get(i) == 0)
            {
                throw std::invalid_argument("Division by zero in vector");
            }
        }

        Matrix result = *this;
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] /= vec;
        }
        return result;
    }

    Matrix operator/(Variable& other)
    {
        Matrix result(rows(), cols());
        for (size_t i = 0; i < rows(); ++i)
        {
            result[i] = data_[i] / other;
        }
        return result;
    }
    // Scalar operations
    template <AllowedTypes T>
    Matrix operator*(const T &scalar) const
    {
        Matrix result = *this;
        for (auto &row : result.data_)
        {
            row *= scalar;
        }
        return result;
    }

    template <AllowedTypes T>
    Matrix operator/(const T &scalar) const
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Division by zero");
        }
        Matrix result = *this;
        for (auto &row : result.data_)
        {
            row /= scalar;
        }
        return result;
    }

    // Compound assignment operators
    Matrix &operator+=(const Matrix &other)
    {
        *this = *this + other;
        return *this;
    }

    Matrix &operator-=(const Matrix &other)
    {
        *this = *this - other;
        return *this;
    }

    template <AllowedTypes T>
    Matrix &operator*=(const T &scalar)
    {
        for (auto &row : data_)
        {
            row *= scalar;
        }
        return *this;
    }

    template <AllowedTypes T>
    Matrix &operator/=(const T &scalar)
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Division by zero");
        }
        for (auto &row : data_)
        {
            row /= scalar;
        }
        return *this;
    }
 
    // Compound assignment with Vector
    Matrix &operator+=(const Vector &vec)
    {
        if (cols() != vec.size())
        {
            throw std::invalid_argument("Vector size must match matrix columns");
        }

        for (size_t i = 0; i < rows(); ++i)
        {
            data_[i] += vec;
        }
        return *this;
    }

    Matrix &operator-=(const Vector &vec)
    {
        if (cols() != vec.size())
        {
            throw std::invalid_argument("Vector size must match matrix columns");
        }

        for (size_t i = 0; i < rows(); ++i)
        {
            data_[i] -= vec;
        }
        return *this;
    }

    Matrix &operator*=(const Vector &vec)
    {
        if (cols() != vec.size())
        {
            throw std::invalid_argument("Vector size must match matrix columns");
        }

        for (size_t i = 0; i < rows(); ++i)
        {
            data_[i] *= vec;
        }
        return *this;
    }

    Matrix &operator/=(const Vector &vec)
    {
        if (cols() != vec.size())
        {
            throw std::invalid_argument("Vector size must match matrix columns");
        }

        // Check for division by zero in vector
        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (vec.get(i) == 0)
            {
                throw std::invalid_argument("Division by zero in vector");
            }
        }

        for (size_t i = 0; i < rows(); ++i)
        {
            data_[i] /= vec;
        }
        return *this;
    }

    // Scalar operations
    template <AllowedTypes T>
    Matrix operator+(const T &scalar) const
    {
        Matrix result = *this;
        for (auto &row : result.data_)
        {
            row += scalar;
        }
        return result;
    }

    template <AllowedTypes T>
    Matrix operator-(const T &scalar) const
    {
        Matrix result = *this;
        for (auto &row : result.data_)
        {
            row -= scalar;
        }
        return result;
    }

    // Already exists from previous code
    // template<AllowedTypes T>
    // Matrix operator*(const T& scalar) const

    // Already exists from previous code
    // template<AllowedTypes T>
    // Matrix operator/(const T& scalar) const

    // Additional compound assignment operators for scalar operations
    template <AllowedTypes T>
    Matrix &operator+=(const T &scalar)
    {
        for (auto &row : data_)
        {
            row += scalar;
        }
        return *this;
    }

    template <AllowedTypes T>
    Matrix &operator-=(const T &scalar)
    {
        for (auto &row : data_)
        {
            row -= scalar;
        }
        return *this;
    }

    // Already exists from previous code
    // template<AllowedTypes T>
    // Matrix& operator*=(const T& scalar)

    // Already exists from previous code
    // template<AllowedTypes T>
    // Matrix& operator/=(const T& scalar)

    // Friend operators for commutative operations
    template <AllowedTypes T>
    friend Matrix operator+(const T &scalar, const Matrix &matrix)
    {
        return matrix + scalar;
    }

    template <AllowedTypes T>
    friend Matrix operator*(const T &scalar, const Matrix &matrix)
    {
        return matrix * scalar;
    }

    friend Matrix operator+(const Vector &vec, const Matrix &matrix)
    {
        return matrix + vec;
    }

    friend Matrix operator*(const Vector &vec, const Matrix &matrix)
    {
        return matrix * vec;
    }
    // Stream operators
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        os << extractClassName() << " " << matrix.rows() << "x" << matrix.cols() << " {\n";
        for (size_t i = 0; i < matrix.rows(); ++i)
        {
            os << "[";
            for (size_t j = 0; j < matrix.cols(); ++j)
            {
                os << matrix.at(i)[j];
                if (j != matrix.cols() - 1)
                    os << ", ";
            }
            os << "],\n";
        }
        os << "}";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Matrix &matrix)
    {
        std::string className;
        is >> className;

        size_t rows, cols;
        char x;
        is >> rows >> x >> cols;

        is >> std::ws;
        if (is.peek() != '{')
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        is.ignore();

        matrix.clear();
        matrix.resize(rows, cols);

        for (size_t i = 0; i < rows; ++i)
        {
            Vector row(cols);
            if (!(is >> row))
            {
                is.setstate(std::ios::failbit);
                return is;
            }
            matrix[i] = row;
        }

        is >> std::ws;
        if (is.peek() == '}')
        {
            is.ignore();
        }

        return is;
    }

private:
    static std::string extractClassName()
    {
#ifdef _MSC_VER
        const char *funcSig = __FUNCSIG__;
#else
        const char *funcSig = __PRETTY_FUNCTION__;
#endif
        // Extract the class name from the function signature string
        std::string funcSigStr(funcSig);
        size_t start = funcSigStr.find("Matri");
        size_t end = funcSigStr.find("x", start);
        if (start != std::string::npos && end != std::string::npos)
        {
            return funcSigStr.substr(start, end - (start - 1));
        }
        return "UnknownClass";
    }
    std::vector<Vector> data_;
};

#endif /* MATRIX_HPP */
