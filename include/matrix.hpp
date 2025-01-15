#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "core.h"
#include "vector.hpp"

template <typename T>
class Matrix final : public AbstractContainerType
{
public:
    using AbstractContainerType::AbstractContainerType;

    /// @brief Default constructor for the Matrix class
    Matrix() : AbstractContainerType(extractClassName()){
        data_.resize(0);
        rows_ = 0;
        cols_ = 0;

    }

    /// @brief Constructor with size params for the Matrix class
    /// @param rows The number of rows
    /// @param cols The number of columns
    Matrix(size_t rows, size_t cols)
        : AbstractContainerType(extractClassName()) {
            data_.resize(rows);
            for (size_t i = 0; i < rows; ++i)
            {
                data_[i].resize(cols);
            }
            rows_ = rows;
            cols_ = cols;
        }

    /// @brief Constructor with given size for a square matrix
    /// @param size The size of the vector
    Matrix(size_t size)
        : AbstractContainerType(extractClassName()) {
            data_.resize(size);
            for (size_t i = 0; i < size; ++i)
            {
                data_[i].resize(size);
            }
            rows_ = size;
            cols_ = size;

        }

    /// @brief Constructor with an existing vector
    /// @param data The vector
    /// @param rows The number of rows
    /// @param cols The number of columns
    Matrix(const std::vector<T> &data, size_t rows, size_t cols)
        : AbstractContainerType(extractClassName()), rows_(rows), cols_(cols)
    {
        data_.resize(rows);
        for (size_t i = 0; i < rows; ++i)
        {
            data_[i].resize(cols);
            for (size_t j = 0; j < cols; ++j)
            {
                data_[i][j] = data[i * cols + j];
            }
        }
    }

    /// @brief Copy constructor
    /// @param matrix The matrix to copy
    Matrix(const Matrix &matrix)
        : AbstractContainerType(extractClassName()), data_(matrix.data_), rows_(matrix.rows_), cols_(matrix.cols_) {}

    /// @brief Move constructor
    /// @param matrix The matrix to copy
    Matrix(Matrix &&matrix) noexcept
        : AbstractContainerType(extractClassName()), data_(std::move(matrix.data_)), rows_(matrix.rows_), cols_(matrix.cols_) {}

    // Destructor
    ~Matrix() = default;

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
    inline std::string toString() const override;

    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
    inline std::string getTypeName() const override;

    /// @brief Return the number of rows
    /// @return The number of rows
    inline size_t rowsCount() const;

    /// @brief Return the number of columns
    /// @return The number of columns
    inline size_t colsCount() const;

    /// @brief This method adds object to the container
    /// @param object to add be added to the container
    template<typename U>
    inline void add(std::shared_ptr<U> object);

    /// @brief This method returns size of the container
    /// @return size of the container
    inline size_t size() const;

    /// @brief This method returns object by index its index container
    /// @param index of the object
    /// @return object by index
    inline Vector<T> get(size_t index) const;

    /// @brief This method returns object by index
    /// @param index of the object
    /// @return object by index
    inline Vector<T> operator[](size_t index) const;

    /// @brief This method returns object by index
    /// @param index of the object
    /// @return object by index
    inline Vector<T> at(size_t index) const;

    /// @brief This method returns pointer of the container
    /// @param index of the object
    /// @return pointer of the container
    inline std::shared_ptr<T> ptr(size_t index) const;

    /// @brief This method return first element of the container
    /// @return first element of the container
    inline std::shared_ptr<T> front() const;

    /// @brief This method return last element of the container
    /// @return last element of the container
    inline std::shared_ptr<T> back() const;

    /// @brief This method adds object to the container end of the container
    /// @param var to add to the container
    template<typename U>
    inline void push_back(const U &var);

    /// @brief This method adds object to the container end of the container
    /// @param var to add to the container
    template<typename U>
    inline void append(const U &var);

    /// @brief This method removes object from the container
    /// @param index of the object
    inline void remove(size_t index);

    /// @brief This method removes object from the container first of the container
    /// @param var to add to the container
    inline void pop_front();

    /// @brief This method removes object from the container end of the container
    /// @param var to add to the container
    inline void pop_back();

    /// @brief This method clears the container
    inline void clear();

    /// @brief This method erases object from the container
    /// @param index of the object
    inline void erase(size_t index);

    /// @brief This method inserts object to the container
    /// @param insert index of the object
    /// @param var to add to the container
    template<typename U>
    inline void insert(size_t insert, const U &var);

    /// @brief This method resizes the container
    /// @param size of the container
    inline void resize(size_t size);

    /// @brief This method swaps two containers
    /// @param other container
    inline void swap(Matrix &other) noexcept;

    /// @brief This method returns begin iterator of the container
    /// @return begin iterator of the container
    std::vector<T>::iterator begin();

    /// @brief This method returns end iterator of the container
    /// @return end iterator of the container
    std::vector<T>::iterator end();

    /// @brief This method returns const begin iterator of the container
    /// @return const begin iterator of the container
    std::vector<T>::const_iterator cbegin() const;

    /// @brief This method returns const end iterator of the container
    /// @return const end iterator of the container
    std::vector<T>::const_iterator cend() const;

    /// @brief This method returns the value of the object
    /// @param other Variable to copy compare
    /// @return The value of the object
    Matrix<T> &operator=(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Variable<T> to move compare
    /// @return The value of the object
    Matrix<T> &operator=(Matrix<T> &&other) noexcept;

    // /// @brief This method returns the value of the object
    // /// @param other Variable<T> to copy compare
    // /// @return The value of the object
    // template<typename U>
    // Matrix<T> &operator=(Vector<U> value);

    /// @brief This method returns the value of the object as a boolean
    /// @param other Variable<T> to compare
    /// @return The value of the object as a boolean
    bool operator==(const Matrix<T> &other) const;

    /// @brief This method returns the value of the object as a boolean
    /// @param other Variable<T> to compare
    /// @return The value of the object as a boolean
    bool operator!=(const Matrix<T> &other) const;

    /// @brief This method returns result of the add operation
    /// @param other Variable<T> to add
    /// @return Result of the add operation
    Matrix<T> operator+(const Matrix<T> &other);

    /// @brief This method returns result of the sub operation
    /// @param other Variable<T> to substract
    /// @return Result of the sub operation
    Matrix<T> operator-(const Matrix<T> &other);

    /// @brief This method returns result of the mul operation
    /// @param other Variable<T> to multiply
    /// @return Result of the mul operation
    Matrix<T> operator*(const Matrix<T> &other);

    /// @brief This method returns result of the div operation
    /// @param other Variable<T> to divide
    /// @return Result of the div operation
    Matrix<T> operator/(const Matrix<T> &other);

    /// @brief This method returns result of the mod operation
    /// @param other Variable<T> to divide
    /// @return Result of the mod operation
    Matrix<T> operator%(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to add
    /// @return The value of the object
    template<typename U>
    Matrix<T> operator+(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to substract
    /// @return The value of the object
    template<typename U>
    Matrix<T> operator-(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to multiply
    /// @return The value of the object
    template<typename U>
    Matrix<T> operator*(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to divide
    /// @return The value of the object
   template<typename U>
    Matrix<T> operator/(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to divide
    /// @return The value of the object
   template<typename U>
    Matrix<T> operator%(U value);

    /// @brief This method returns the value of the object
    /// @param other Variable<T> to add
    /// @return The value of the object
    Matrix<T> &operator+=(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Variable<T> to substract
    /// @return The value of the object
    Matrix<T> &operator-=(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Variable<T> to multiply
    /// @return The value of the object
    Matrix<T> &operator*=(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Variable<T> to divide
    /// @return The value of the object
    Matrix<T> &operator/=(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Variable<T> to divide
    /// @return The value of the object
    Matrix<T> &operator%=(const Matrix<T> &other);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to add
    /// @return The value of the object
   template<typename U>
    Matrix<T> &operator+=(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to substract
    /// @return The value of the object
   template<typename U>
    Matrix<T> &operator-=(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to multiply
    /// @return The value of the object
   template<typename U>
    Matrix<T> &operator*=(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to divide
    /// @return The value of the object
   template<typename U>
    Matrix<T> &operator/=(U value);

    /// @brief This method returns the value of the object
    /// @param value Variable<T> to divide
    /// @return The value of the object
   template<typename U>
    Matrix<T> &operator%=(U value);

    /// @brief This method returns the value of the object
    /// @return  The value of the object
    Matrix<T> &operator++();

    /// @brief This method returns the value of the object
    /// @return The value of the object
    Matrix<T> &operator--();

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Matrix<T> operator++(int);

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Matrix<T> operator--(int);

    /// @brief This override method output prints the container
    /// @param os output stream
    /// @param vector obj to print
    /// @return output stream
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
    {
        os << matrix.extractClassName() << " {\n";
        for (size_t i = 0; i < matrix.colsCount(); ++i)
        {
            os << "{\n";
            for (size_t j = 0; j < matrix.rowsCount(); ++j)
                os << i << ":  " << matrix[i][j] << "\n";
            os << "}";
        }
        os << "}";
        return os;
    }

    /// @brief This override method input reads the container
    /// @param is input stream
    /// @param vector obj to read
    /// @return input stream
    friend std::istream &operator>>(std::istream &is, Matrix<T> &matrix)
    {
        std::string className;
        is >> className;
        matrix.setClassName(className);

        is >> std::ws;
        if (is.peek() != '{')
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        is.ignore();

        matrix.clear();
        T value;
        while (is.peek() != '}')
        {
            if (!(is >> value))
            {
                is.setstate(std::ios::failbit);
                return is;
            }
            matrix.push_back(value);
            is >> std::ws;
        }
        is.ignore();
        return is;
    }
protected:
    template<typename U>
    Vector<T> convert_vector(const U& vec) {
        Vector<T> result;
        for (size_t i = 0; i < vec.size(); ++i)
            result.push_back(vec[i].getValue());

        return result;
    }
private:
    static std::string extractClassName()
    {
#ifdef _MSC_VER
        const char *funcSig = __FUNCSIG__;
#else
        const char *funcSig = __PRETTY_FUNCTION__;
#endif
        std::string funcSigStr(funcSig);
        size_t start = funcSigStr.find("Matrix<");
        size_t end = funcSigStr.find(">::", start);
        if (start != std::string::npos && end != std::string::npos)
        {
            return funcSigStr.substr(start, end - start);
        }
        return "UnknownClass";
    }

    Vector<Vector<T>> data_;
    size_t rows_;
    size_t cols_;
};

template <typename T>
inline std::string Matrix<T>::toString() const
{
    std::ostringstream oss;
    oss << "Matrix<" << getTypeName() << "> {\n";
    for (size_t i = 0; i < rows_; ++i)
    {
        oss << "  Row " << i + 1 << ": [";
        for (size_t j = 0; j < cols_; ++j)
        {
            oss << data_[i * cols_ + j];
            if (j < cols_ - 1)
            {
                oss << ", "; // Для разделения элементов в строке
            }
        }
        oss << "]\n";
    }
    oss << "}";
    return oss.str();
}

template <typename T>
inline std::string Matrix<T>::getTypeName() const
{
    return extractClassName(); // Воспользуемся существующей функцией для получения имени типа
}

template <typename T>
inline size_t Matrix<T>::rowsCount() const
{
    return rows_; // Возвращаем количество строк
}

template <typename T>
inline size_t Matrix<T>::colsCount() const
{
    return cols_; // Возвращаем количество столбцов
}

template <typename T>
template <typename U>
inline void Matrix<T>::add(std::shared_ptr<U> object)
{
    // Assuming that data_ is a vector-like container
    data_.push_back(*object); // Dereference the shared_ptr and add the object to the matrix
}

// Возвращает общее количество элементов в матрице
template <typename T>
inline size_t Matrix<T>::size() const
{
    return rows_ * cols_; // Общее количество элементов = строки * столбцы
}

// Возвращает объект по индексу (доступ к элементу)
template <typename T>
inline Vector<T> Matrix<T>::get(size_t index) const
{
    if (index >= size()) // Check for out-of-bounds index
    {
        throw std::out_of_range("Index out of range");
    }

    // Return the element from the correct level of the container
    return data_.at(index); // If data_ is a std::vector<Vector<Variable<int>>>
}

// Оператор индексации, аналогичный get()
template <typename T>
inline Vector<T> Matrix<T>::operator[](size_t index) const
{
    return data_[index]; // Просто переадресовываем вызов get()
}

// Возвращает элемент по индексу с дополнительной проверкой
template <typename T>
inline Vector<T> Matrix<T>::at(size_t index) const
{
    if (index >= size()) // Проверка на выход за пределы
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index]; // Возвращаем элемент по индексу
}

// Получаем указатель на элемент по индексу
template <typename T>
inline std::shared_ptr<T> Matrix<T>::ptr(size_t index) const
{
    if (index >= size()) // Проверка на выход за пределы
    {
        throw std::out_of_range("Index out of range");
    }
    return std::make_shared<T>(data_[index]); // Возвращаем shared_ptr на элемент
}

// Возвращаем указатель на первый элемент матрицы
template <typename T>
inline std::shared_ptr<T> Matrix<T>::front() const
{
    if (size() == 0) // Проверка на пустую матрицу
    {
        throw std::out_of_range("Matrix is empty");
    }
    return std::make_shared<T>(data_[0]); // Возвращаем shared_ptr на первый элемент
}

// Возвращаем указатель на последний элемент матрицы
template <typename T>
inline std::shared_ptr<T> Matrix<T>::back() const
{
    if (size() == 0) // Проверка на пустую матрицу
    {
        throw std::out_of_range("Matrix is empty");
    }
    return std::make_shared<T>(data_[size() - 1]); // Возвращаем shared_ptr на последний элемент
}

// Добавить элемент в конец матрицы
template <typename T>
template <typename U>
inline void Matrix<T>::push_back(const U& var)
{
    data_.push_back(convert_vector(var)); // Добавляем элемент в конец вектора
}

// Аналогично push_back, добавляем элемент в конец
template <typename T>
template <typename U>
inline void Matrix<T>::append(const U &var)
{
    push_back(var); // Можно просто вызвать push_back, так как они идентичны
}

// Удалить элемент по индексу
template <typename T>
inline void Matrix<T>::remove(size_t index)
{
    if (index >= size()) // Проверка на выход за пределы
    {
        throw std::out_of_range("Index out of range");
    }
    data_.erase(data_.begin() + index); // Удаляем элемент из вектора
}

// Удалить первый элемент
template <typename T>
inline void Matrix<T>::pop_front()
{
    if (size() == 0) // Проверка на пустую матрицу
    {
        throw std::out_of_range("Matrix is empty");
    }
    data_.erase(data_.begin()); // Удаляем первый элемент
}

// Удалить последний элемент
template <typename T>
inline void Matrix<T>::pop_back()
{
    if (size() == 0) // Проверка на пустую матрицу
    {
        throw std::out_of_range("Matrix is empty");
    }
    data_.pop_back(); // Удаляем последний элемент
}

// Очищает матрицу (удаляет все элементы)
template <typename T>
inline void Matrix<T>::clear()
{
    data_.clear(); // Очищаем все элементы вектора
}

// Удаляет элемент по индексу
template <typename T>
inline void Matrix<T>::erase(size_t index)
{
    if (index >= size()) // Проверка на выход за пределы
    {
        throw std::out_of_range("Index out of range");
    }
    data_.erase(data_.begin() + index); // Удаляем элемент на указанной позиции
}

// Вставляет элемент на указанную позицию
template <typename T>
template <typename U>
inline void Matrix<T>::insert(size_t index, const U &var)
{
    if (index > size()) // Проверка, чтобы индекс не выходил за пределы
    {
        throw std::out_of_range("Index out of range");
    }
    data_.insert(data_.begin() + index, var); // Вставляем элемент на указанную позицию
}

// Изменяет размер матрицы
template <typename T>
inline void Matrix<T>::resize(size_t size)
{
    if (size < this->size()) // Если новый размер меньше текущего, обрезаем элементы
    {
        data_.resize(size);
    }
    else if (size > this->size()) // Если новый размер больше, добавляем пустые элементы
    {
        data_.resize(size, T()); // Заполняем новыми значениями по умолчанию (T())
    }
}

template <typename T>
inline void Matrix<T>::swap(Matrix &other) noexcept
{
    if (this != &other) // Проверка на самосравнение
    {
        data_.swap(other.data_); // Меняем данные между матрицами
    }
}

// Получение итератора на начало данных (для обычного доступа)
template <typename T>
inline typename std::vector<T>::iterator Matrix<T>::begin()
{
    return data_.begin(); // Возвращаем итератор на первый элемент
}

// Получение итератора на конец данных (для обычного доступа)
template <typename T>
inline typename std::vector<T>::iterator Matrix<T>::end()
{
    return data_.end(); // Возвращаем итератор на конец данных
}

// Получение константного итератора на начало данных (для константного доступа)
template <typename T>
inline typename std::vector<T>::const_iterator Matrix<T>::cbegin() const
{
    return data_.cbegin(); // Возвращаем константный итератор на первый элемент
}

// Константный итератор на конец данных (для константного доступа)
template <typename T>
inline typename std::vector<T>::const_iterator Matrix<T>::cend() const
{
    return data_.cend(); // Возвращаем константный итератор на элемент, следующий за последним
}

// Оператор присваивания для копирования
template <typename T>
inline Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
{
    if (this != &other) // Проверка на самосравнение
    {
        data_ = other.data_; // Копируем данные из другой матрицы
    }
    return *this; // Возвращаем ссылку на текущий объект
}

// Оператор присваивания для перемещения
template <typename T>
inline Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept
{
    if (this != &other) // Проверка на самосравнение
    {
        data_ = std::move(other.data_); // Перемещаем данные из другой матрицы
        other.data_.clear();            // Очистка данных в перемещаемой матрице
    }
    return *this; // Возвращаем ссылку на текущий объект
}


// Оператор сравнения для матриц
template <typename T>
inline bool Matrix<T>::operator==(const Matrix<T> &other) const
{
    // Сравниваем размеры (строки и столбцы) матриц
    if (this->rowsCount() != other.rowsCount() || this->colsCount() != other.colsCount())
    {
        return false; // Если размеры разные, то матрицы точно разные
    }

    // Сравниваем каждый элемент матриц
    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < this->colsCount(); ++j)
        {
            if (data_[i][j] != other.data_[i][j]) // Сравниваем элементы по индексам
            {
                return false; // Если хоть один элемент отличается, матрицы разные
            }
        }
    }
    return true; // Все элементы совпали, матрицы равны
}

// Оператор сравнения для матрицы и одного значения
// Оператор неравенства для матриц
template <typename T>
inline bool Matrix<T>::operator!=(const Matrix<T> &other) const
{
    return !(*this == other); // Если матрицы не равны, то они не равны
}

// Оператор сложения матриц
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other)
{
    // Проверяем, что размеры матриц совпадают
    if (this->rowsCount() != other.rowsCount() || this->colsCount() != other.colsCount())
    {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix<T> result(*this); // Создаем новый объект для результата
    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < this->colsCount(); ++j)
        {
            result.data_[i][j] += other.data_[i][j]; // Сложение элементов
        }
    }
    return result;
}

// Оператор вычитания матриц
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other)
{
    // Проверяем, что размеры матриц совпадают
    if (this->rowsCount() != other.rowsCount() || this->colsCount() != other.colsCount())
    {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }

    Matrix<T> result(*this); // Создаем новый объект для результата
    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < this->colsCount(); ++j)
        {
            result.data_[i][j] -= other.data_[i][j]; // Вычитание элементов
        }
    }
    return result;
}

// Оператор умножения матриц
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other)
{
    // Проверяем, что количество столбцов первой матрицы совпадает с количеством строк второй
    if (this->colsCount() != other.rowsCount())
    {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }

    Matrix<T> result;
    result.resize(this->rowsCount(), other.colsCount()); // Размерность результата

    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < other.colsCount(); ++j)
        {
            result.data_[i][j] = 0; // Инициализируем элемент для сложения
            for (size_t k = 0; k < this->colsCount(); ++k)
            {
                result.data_[i][j] += this->data_[i][k] * other.data_[k][j]; // Сложение произведений
            }
        }
    }
    return result;
}

// Оператор деления матриц (определим как деление поэлементно, если необходимо)
template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T> &other)
{
    // Проверяем, что размеры матриц совпадают
    if (this->rowsCount() != other.rowsCount() || this->colsCount() != other.colsCount())
    {
        throw std::invalid_argument("Matrix dimensions must match for division");
    }

    Matrix<T> result(*this); // Создаем новый объект для результата
    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < this->colsCount(); ++j)
        {
            if (other.data_[i][j] == 0)
            {
                throw std::invalid_argument("Division by zero");
            }
            result.data_[i][j] /= other.data_[i][j]; // Деление элементов поэлементно
        }
    }
    return result;
}

// Оператор взятия остатка от деления матриц (поэлементно)
template <typename T>
Matrix<T> Matrix<T>::operator%(const Matrix<T> &other)
{
    // Проверяем, что размеры матриц совпадают
    if (this->rowsCount() != other.rowsCount() || this->colsCount() != other.colsCount())
    {
        throw std::invalid_argument("Matrix dimensions must match for modulo operation");
    }

    Matrix<T> result(*this); // Создаем новый объект для результата
    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < this->colsCount(); ++j)
        {
            if (other.data_[i][j] == 0)
            {
                throw std::invalid_argument("Modulo by zero");
            }
            result.data_[i][j] = std::fmod(this->data_[i][j], other.data_[i][j]); // Остаток от деления элементов
        }
    }
    return result;
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::operator+(U value)
{
    Matrix<T> result = *this;
    for (auto &element : result.data_)
    {
        element += value;
    }
    return result;
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::operator-(U value)
{
    Matrix<T> result = *this;
    for (auto &element : result.data_)
    {
        element -= value;
    }
    return result;
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::operator*(U value)
{
    Matrix<T> result = *this;
    for (auto &element : result.data_)
    {
        element *= value;
    }
    return result;
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::operator/(U value)
{
    if (value == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    Matrix<T> result = *this;
    for (auto &element : result.data_)
    {
        element /= value;
    }
    return result;
}

template <typename T>
template <typename U>
Matrix<T> Matrix<T>::operator%(U value)
{
    Matrix<T> result = *this;
    for (auto &element : result.data_)
    {
        element %= value;
    }
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
{
    if (this->size() != other.size())
    {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] += other.data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other)
{
    if (this->size() != other.size())
    {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }

    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] -= other.data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other)
{
    if (this->colsCount() != other.rowsCount())
    {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }

    Matrix<T> result(this->rowsCount(), other.colsCount());
    for (size_t i = 0; i < this->rowsCount(); ++i)
    {
        for (size_t j = 0; j < other.colsCount(); ++j)
        {
            result.data_[i * other.colsCount() + j] = 0;
            for (size_t k = 0; k < this->colsCount(); ++k)
            {
                result.data_[i * other.colsCount() + j] += this->data_[i * this->colsCount() + k] * other.data_[k * other.colsCount() + j];
            }
        }
    }
    *this = std::move(result);
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const Matrix<T> &other)
{
    // Division for matrices is less common. It usually implies element-wise division or a special inverse operation.
    // Assuming element-wise division here.
    if (this->size() != other.size())
    {
        throw std::invalid_argument("Matrix dimensions must match for division");
    }

    for (size_t i = 0; i < this->size(); ++i)
    {
        if (other.data_[i] == 0)
        {
            throw std::invalid_argument("Division by zero");
        }
        this->data_[i] /= other.data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator%=(const Matrix<T> &other)
{
    if (this->size() != other.size())
    {
        throw std::invalid_argument("Matrix dimensions must match for modulo operation");
    }

    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] %= other.data_[i];
    }
    return *this;
}

template <typename T>
template <typename U>
Matrix<T> &Matrix<T>::operator+=(U value)
{
    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] += value;
    }
    return *this;
}

template <typename T>
template <typename U>
Matrix<T> &Matrix<T>::operator-=(U value)
{
    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] -= value;
    }
    return *this;
}

template <typename T>
template <typename U>
Matrix<T> &Matrix<T>::operator*=(U value)
{
    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] *= value;
    }
    return *this;
}

template <typename T>
template <typename U>
Matrix<T> &Matrix<T>::operator/=(U value)
{
    if (value == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] /= value;
    }
    return *this;
}

template <typename T>
template <typename U>
Matrix<T> &Matrix<T>::operator%=(U value)
{
    if (value == 0)
    {
        throw std::invalid_argument("Modulo by zero");
    }
    for (size_t i = 0; i < this->size(); ++i)
    {
        this->data_[i] %= value;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator++()
{
    // Pre-increment: Increment each element of the matrix
    for (size_t i = 0; i < this->size(); ++i)
    {
        ++this->data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator--()
{
    // Pre-decrement: Decrement each element of the matrix
    for (size_t i = 0; i < this->size(); ++i)
    {
        --this->data_[i];
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator++(int)
{
    // Post-increment: Create a copy of the matrix, then increment the original matrix
    Matrix<T> temp = *this;
    for (size_t i = 0; i < this->size(); ++i)
    {
        ++this->data_[i];
    }
    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator--(int)
{
    // Post-decrement: Create a copy of the matrix, then decrement the original matrix
    Matrix<T> temp = *this;
    for (size_t i = 0; i < this->size(); ++i)
    {
        --this->data_[i];
    }
    return temp;
};
#endif /* MATRIX_HPP */