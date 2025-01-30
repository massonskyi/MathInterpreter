#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../base/abstractcontainertype.hxx"
#include "variable.hxx"
#include <vector>

/// @brief The Vector class represents a vector of integers
class Vector final : public AbstractContainerType
{
public:
    using value_type = Variable;
    /// @brief Default constructor for the Vector class
    Vector() : AbstractContainerType(extractClassName()), vector_({}) {}

    /// @brief Constructor with size params for the Vector class
    /// @param size The size of the vector
    explicit Vector(const size_t size) : AbstractContainerType(extractClassName()), vector_(size, Variable()) {}
    /// @brief Constructor with initializer list for the Vector class
    /// @param list The initializer list
    Vector(const std::initializer_list<Variable> list) : AbstractContainerType(extractClassName())
    {
        for (const auto &elem : list)
        {
            vector_.emplace_back(elem);
        }
    }

    /// @brief Constructor with initializer list for the Vector class
    /// @param list The initializer list
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    Vector(std::initializer_list<T> list) : AbstractContainerType(extractClassName())
    {
        for (const auto &elem : list)
        {
            vector_.emplace_back(Variable(elem));
        }
    }

    /// @brief Copy constructor
    /// @param other The other vector
    Vector(const Vector &other) noexcept : AbstractContainerType(extractClassName()), vector_(other.vector_) {}

    /// @brief Move constructor
    /// @param other The other vector
    Vector(Vector &&other) noexcept : AbstractContainerType(extractClassName()), vector_(std::move(other.vector_)) {}

    /// @brief Destructor
    ~Vector() override = default;

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
     [[nodiscard]] string toString() const override
    {
        std::stringstream ss;
        ss << "[";

        for (size_t i = 0; i < size(); ++i)
        {
            if (i != 0)
                ss << ", ";
            ss << this->vector_[i];
        }

        ss << "]";
        return ss.str(); // Возвращаем строковое представление объекта
    }
    // Виртуальный метод для вывода
    void print(std::ostream &os) const override
    {
        std::cout << *this << std::endl;
    }
    /// @brief This method adds object to the container
    /// @param object to add be added to the container
     void add(const std::shared_ptr<Variable>& object)
    {
        try
        {
            if (!object)
            {
                throw std::invalid_argument("Cannot add a nullptr to the vector.");
            }
            vector_.push_back(*object);
        }
        catch (const std::exception &e)
        {
            // Логирование ошибки
            std::cerr << "[Error] Failed to add object: " << e.what() << std::endl;
            throw; // Повторное выбрасывание исключения для обработки выше
        }
    }
    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
     [[nodiscard]] string getTypeName() const override
    {
        return typeid(*this).name(); // Возвращаем строку, представляющую тип объекта
    }

    /// @brief Reserve capacity for the vector
    /// @param new_cap The new capacity to reserve
     void reserve(const size_t new_cap)
    {
        vector_.reserve(new_cap);
    }

    /// @brief This method returns size of the container
    /// @return size of the container
     [[nodiscard]] size_t size() const
    {
        try
        {
            return vector_.size();
        }
        catch (const std::exception &e)
        {
            // Логирование ошибки
            std::cerr << "[Error] Failed to get size: " << e.what() << std::endl;
            throw; // Повторное выбрасывание исключения для обработки выше
        }
    }
    /// @brief This method returns object by index its index container
    /// @param index of the object
    /// @return object by index
     [[nodiscard]] AbstractObject get() const override
    {
        throw std::runtime_error("Not implemented");
    }
    
    /// @brief This method returns object by index its index container
    /// @param index of the object
    /// @return object by index
     [[nodiscard]] Variable get(const size_t index) const
    {
        try
        {
            if (index >= vector_.size())
            {
                throw std::out_of_range("Index is out of bounds.");
            }
            return vector_.at(index);
        }
        catch (const std::exception &e)
        {
            // Логирование ошибки
            std::cerr << "[Error] Failed to get object at index " << index << ": " << e.what() << std::endl;
            throw; // Повторное выбрасывание исключения для обработки выше
        }
    }

    /// @brief This method returns object by index
    /// @return data vector
     [[nodiscard]] std::vector<Variable> getData() const
    {
        return vector_;
    }
    /// @brief This method return false if the container is empty
    /// @return data vector
     [[nodiscard]] bool empty() const
    {
        return vector_.empty();
    }
    /// @brief This method returns object by index
    /// @param index of the object
    /// @return object by index
     Variable &operator[](const size_t index)
    {
        return vector_[index];
    }
    /// @brief This method returns object by index
    /// @param index of the object
    /// @return object by index
    const Variable &operator[](const size_t index) const
    {
        return vector_[index];
    }
    /// @brief This method returns object by index
    /// @param index of the object
    /// @return object by index
     [[nodiscard]] Variable at(const size_t index) const
    {
        return vector_.at(index);
    }

    /// @brief This method returns pointer of the container
    /// @param index of the object
    /// @return pointer of the container
     [[nodiscard]] std::shared_ptr<Variable> ptr(const size_t index) const
    {
        try
        {
            if (index >= vector_.size())
            {
                throw std::out_of_range("Index is out of bounds.");
            }
            return std::make_shared<Variable>(vector_[index]);
        }
        catch (const std::exception &e)
        {
            // Логирование ошибки
            std::cerr << "[Error] Failed to get object at index " << index << ": " << e.what() << std::endl;
            throw; // Повторное выбрасывание исключения для обработки выше
        }
    }

    /// @brief This method return first element of the container
    /// @return first element of the container
     [[nodiscard]] std::shared_ptr<Variable> front() const
    {
        try
        {
            if (vector_.empty())
            {
                throw std::out_of_range("Vector is empty.");
            }
            return std::make_shared<Variable>(vector_.front());
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] front: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method return last element of the container
    /// @return last element of the container
     [[nodiscard]] std::shared_ptr<Variable> back() const
    {
        try
        {
            if (vector_.empty())
            {
                throw std::out_of_range("Vector is empty.");
            }
            return std::make_shared<Variable>(vector_.back());
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] back: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method adds object to the container end of the container
    /// @param var to add to the container
     void push_back(const Variable &var)
    {
        try
        {
            vector_.push_back(var);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] push_back: " << e.what() << std::endl;
            throw;
        }
    }
    /// @brief This method adds object to the container end of the container
    /// @param var to add to the container
    template <AllowedTypes _Tp>
     void push_back(const _Tp &var)
    {
        try
        {
            vector_.push_back(Variable(var));
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] push_back: " << e.what() << std::endl;
            throw;
        }
    }
    /// @brief This method adds object to the container end of the container
    /// @param var to add to the container
     void append(const Variable &var)
    {
        try
        {
            vector_.push_back(var);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] append: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method adds object to the container end of the container
    /// @param var to add to the container
    template <AllowedTypes _Tp>
     void append(const _Tp &var)
    {
        try
        {
            vector_.push_back(Variable(var));
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] append: " << e.what() << std::endl;
            throw;
        }
    }
    /// @brief This method removes object from the container
    /// @param index of the object
     void remove(const size_t index)
    {
        try
        {
            if (index >= vector_.size())
            {
                throw std::out_of_range("Index is out of bounds.");
            }
            vector_.erase(vector_.begin() + index);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] remove: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method removes object from the container first of the container
    /// @param var to add to the container
     void pop_front()
    {
        try
        {
            if (vector_.empty())
            {
                throw std::out_of_range("Cannot pop from an empty vector.");
            }
            vector_.erase(vector_.begin());
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] pop_front: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method removes object from the container end of the container
    /// @param var to add to the container
     void pop_back()
    {
        try
        {
            if (vector_.empty())
            {
                throw std::out_of_range("Cannot pop from an empty vector.");
            }
            vector_.pop_back();
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] pop_back: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method clears the container
     void clear()
    {
        try
        {
            vector_.clear();
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] clear: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method erases object from the container
    /// @param index of the object
     void erase(const size_t index)
    {
        try
        {
            if (index >= vector_.size())
            {
                throw std::out_of_range("Index is out of bounds.");
            }
            vector_.erase(vector_.begin() + index);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] erase: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method inserts object to the container
    /// @param index of the object to insert
    /// @param var to add to the container
     void insert(size_t index, const Variable &var)
    {
        try
        {
            if (index > vector_.size())
            {
                throw std::out_of_range("Index is out of bounds.");
            }
            vector_.insert(vector_.begin() + index, var);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] insert: " << e.what() << std::endl;
            throw;
        }
    }
    /// @brief This method inserts object to the container
    /// @param index index of the object
    /// @param var to add to the container
    template <AllowedTypes _Tp>
     void insert(const size_t index, const _Tp &var)
    {
        try
        {
            if (index > vector_.size())
            {
                throw std::out_of_range("Index is out of bounds.");
            }
            vector_.insert(vector_.begin() + index, Variable(var));
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] insert: " << e.what() << std::endl;
            throw;
        }
    }
    /// @brief This method resizes the container
    /// @param size of the container
     void resize(const size_t size)
    {
        try
        {
            vector_.resize(size);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] resize: " << e.what() << std::endl;
            throw;
        }
    }

    /// @brief This method swaps two containers
    /// @param other container
     void swap(Vector &other) noexcept
    {
        try
        {
            vector_.swap(other.vector_);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] swap: " << e.what() << std::endl;
            // Исключение не выбрасывается, так как метод объявлен noexcept
        }
    }
    /// @brief This method swaps two containers
    /// @param other container
     void swap(std::vector<Variable> &other) noexcept
    {
        try
        {
            vector_.swap(other);
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] swap: " << e.what() << std::endl;
            // Исключение не выбрасывается, так как метод объявлен noexcept
        }
    }

    /// @brief This method returns begin iterator of the container
    /// @return begin iterator of the container
    std::vector<Variable>::iterator begin() noexcept
    {
        return vector_.begin();
    }

    /// @brief This method returns end iterator of the container
    /// @return end iterator of the container
    std::vector<Variable>::iterator end() noexcept
    {
        return vector_.end();
    }

    /// @brief This method returns const begin iterator of the container
    /// @return const begin iterator of the container
    [[nodiscard]] std::vector<Variable>::const_iterator cbegin() const noexcept
    {
        return vector_.cbegin();
    }

    /// @brief This method returns const end iterator of the container
    /// @return const end iterator of the container
    [[nodiscard]] std::vector<Variable>::const_iterator cend() const noexcept
    {
        return vector_.cend();
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to copy compare
    /// @return The value of the object
    Vector &operator=(const Vector &other)
    {
        if (this == &other)
        {
            return *this; // Присваивание самому себе, ничего не делаем
        }

        try
        {
            vector_ = other.vector_; // Копирование содержимого из другого вектора
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] Copy assignment: " << e.what() << std::endl;
            throw; // Пробрасываем исключение, если произошла ошибка
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to move compare
    /// @return The value of the object
    Vector &operator=(Vector &&other) noexcept
    {
        if (this == &other)
        {
            return *this; // Присваивание самому себе
        }

        try
        {
            vector_ = std::move(other.vector_); // Перемещаем содержимое другого объекта
            // После перемещения вектор other находится в неопределенном, но валидном состоянии
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] Move assignment: " << e.what() << std::endl;
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to copy compare
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector &operator=(_Tp value)
    {
        try
        {
            reserve(size() + 1);
            if (std::is_same_v<_Tp, Variable>)
                append(value);
            else
                append(Variable(value));

            return *this;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Error] Assignment with value: " << e.what() << std::endl;
            throw; // Пробрасываем исключение, если произошла ошибка
        }

        return *this;
    }

    /// @brief This method returns the value of the object as a boolean
    /// @param other Variable to compare
    /// @return The value of the object as a boolean
    bool operator==(const Vector &other) const
    {
        // Проверяем, что размеры векторов одинаковы
        if (size() != other.size())
        {
            return false; // Если размеры разные, векторы не равны
        }

        // Сравниваем элементы векторов
        for (size_t i = 0; i < size(); ++i)
        {
            if (get(i) != other.get(i))
            {
                return false; // Если хотя бы один элемент не совпадает, векторы не равны
            }
        }

        return true; // Все элементы совпадают
    }

    /// @brief This method returns the value of the object as a boolean
    /// @param other Variable to compare
    /// @return The value of the object as a boolean
    bool operator!=(const Vector &other) const
    {
        return !(*this == other);
    }

    /// @brief This method returns result of the add operation
    /// @param other Variable to add
    /// @return Result of the add operation
    Vector operator+(const Vector &other)
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for addition.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) + other.get(i)); // Поэлементное сложение
        }

        return result;
    }
    /// @brief This method returns result of the add operation
    /// @param other Variable to add
    /// @return Result of the add operation
    Vector operator+(Variable& other)
    {
        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) + other); // Поэлементное сложение
        }

        return result;
    }
    /// @brief This method returns result of the add operation
    /// @param other Variable to add
    /// @return Result of the add operation
    Vector operator+(Variable& other) const
    {
        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) + other); // Поэлементное сложение
        }

        return result;
    }
    /// @brief This method returns result of the add operation
    /// @param other Variable to add
    /// @return Result of the add operation
    Vector operator+(const Vector &other) const
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for addition.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) + other.get(i)); // Поэлементное сложение
        }

        return result;
    }

    /// @brief This method returns result of the sub operation
    /// @param other Variable to substract
    /// @return Result of the sub operation
    Vector operator-(const Vector &other)
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for subtraction.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) - other.get(i)); // Поэлементное вычитание
        }

        return result;
    }
    /// @brief This method returns result of the add operation
    /// @param other Variable to add
    /// @return Result of the add operation
        Vector operator-( Variable& other)
        {
            Vector result;
            for (size_t i = 0; i < this->size(); ++i)
            {
                result.push_back(this->get(i) - other); // Поэлементное сложение
            }

            return result;
    }
    /// @brief This method returns result of the add operation
    /// @param other Variable to add
    /// @return Result of the add operation
    Vector operator-(Variable& other)const
    {
        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) - other); // Поэлементное сложение
        }

        return result;
    }
    /// @brief This method returns result of the sub operation
    /// @param other Variable to substract
    /// @return Result of the sub operation
    Vector operator-(const Vector &other) const
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for subtraction.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) - other.get(i)); // Поэлементное вычитание
        }

        return result;
    }
    /// @brief This method returns result of the mul operation
    /// @param other Variable to multiply
    /// @return Result of the mul operation
    Vector operator*(const Vector &other)
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for multiplication.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) * other.get(i)); // Поэлементное умножение
        }

        return result;
    }
    /// @brief This method returns result of the mul operation
    /// @param other Variable to multiply
    /// @return Result of the mul operation
    Vector operator*(const Vector &other) const
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for multiplication.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) * other.get(i)); // Поэлементное умножение
        }

        return result;
    }
    /// @brief This method returns result of the mul operation
    /// @param other Variable to multiply
    /// @return Result of the mul operation
    Vector operator*(Variable other)
    {


        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) * other); // Поэлементное умножение
        }

        return result;
    }
    /// @brief This method returns result of the mul operation
    /// @param other Variable to multiply
    /// @return Result of the mul operation
    Vector operator*(Variable other)const
    {


        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) * other); // Поэлементное умножение
        }

        return result;
    }
    /// @brief This method returns result of the div operation
    /// @param other Variable to divide
    /// @return Result of the div operation
    Vector operator/(const Vector &other)
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for division.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other.get(i) == 0)
            {
                throw std::invalid_argument("Division by zero.");
            }
            result.push_back(this->get(i) / other.get(i)); // Поэлементное деление
        }

        return result;
    }

    /// @brief This method returns result of the mul operation
    /// @param other Variable to multiply
    /// @return Result of the mul operation
    Vector operator/(Variable other)
    {


        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other == 0)
            {
                throw std::invalid_argument("Division by zero.");
            }
            result.push_back(this->get(i) / other);
        }

        return result;
    }
    /// @brief This method returns result of the mul operation
    /// @param other Variable to multiply
    /// @return Result of the mul operation
    Vector operator/(Variable other)const
    {


        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other == 0)
            {
                throw std::invalid_argument("Division by zero.");
            }
            result.push_back(this->get(i) / other);
        }

        return result;
    }
    /// @brief This method returns result of the div operation
    /// @param other Variable to divide
    /// @return Result of the div operation
    Vector operator/(const Vector &other) const
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for division.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other.get(i) == 0)
            {
                throw std::invalid_argument("Division by zero.");
            }
            result.push_back(this->get(i) / other.get(i)); // Поэлементное деление
        }

        return result;
    }
    /// @brief This method returns result of the mod operation
    /// @param other Variable to divide
    /// @return Result of the mod operation
    Vector operator%(const Vector &other)
    {
        // Проверка на одинаковые размеры
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for modulo.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other.get(i) == 0)
            {
                throw std::invalid_argument("Modulo by zero.");
            }
            result.push_back(this->get(i) % other.get(i)); // Поэлементное взятие остатка
        }

        return result;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to add
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector operator+(_Tp value)
    {
        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) + value); // Поэлементное сложение с числом
        }

        return result;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to substract
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector operator-(_Tp value)
    {
        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) - value); // Поэлементное вычитание с числом
        }

        return result;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to multiply
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector operator*(_Tp value)
    {
        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) * value); // Поэлементное умножение на число
        }

        return result;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector operator/(_Tp value)
    {
        if (value == 0)
        {
            throw std::invalid_argument("Division by zero.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) / value); // Поэлементное деление на число
        }

        return result;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector operator%(_Tp value)
    {
        if (value == 0)
        {
            throw std::invalid_argument("Modulo by zero.");
        }

        Vector result;
        for (size_t i = 0; i < this->size(); ++i)
        {
            result.push_back(this->get(i) % value); // Поэлементное взятие остатка от деления на число
        }

        return result;
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to add
    /// @return The value of the object
    Vector &operator+=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for addition.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] += other.get(i); // Поэлементное сложение
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to substract
    /// @return The value of the object
    Vector &operator-=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for subtraction.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] -= other.get(i); // Поэлементное вычитание
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to multiply
    /// @return The value of the object
    Vector &operator*=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for multiplication.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] *= other.get(i); // Поэлементное умножение
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to divide
    /// @return The value of the object
    Vector &operator/=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for division.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other.get(i) == 0)
            {
                throw std::invalid_argument("Division by zero.");
            }
            this->vector_[i] /= other.get(i); // Поэлементное деление
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param other Variable to divide
    /// @return The value of the object
    Vector &operator%=(const Vector &other)
    {
        if (this->size() != other.size())
        {
            throw std::invalid_argument("Vectors must have the same size for modulo.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            if (other.get(i) == 0)
            {
                throw std::invalid_argument("Modulo by zero.");
            }
            this->vector_[i] %= other.get(i); // Поэлементное взятие остатка
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to add
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector &operator+=(_Tp value)
    {
        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] += value; // Поэлементное сложение
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to substract
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector &operator-=(_Tp value)
    {
        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] -= value; // Поэлементное вычитание
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to multiply
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector &operator*=(_Tp value)
    {
        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] *= value; // Поэлементное умножение
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector &operator/=(_Tp value)
    {
        if (value == 0)
        {
            throw std::invalid_argument("Division by zero.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] /= value; // Поэлементное деление
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param value Variable to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Vector &operator%=(_Tp value)
    {
        if (value == 0)
        {
            throw std::invalid_argument("Modulo by zero.");
        }

        for (size_t i = 0; i < this->size(); ++i)
        {
            this->vector_[i] %= value; // Поэлементное взятие остатка
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @return  The value of the object
    Vector &operator++()
    {
        for (size_t i = 0; i < this->size(); ++i)
        {
            ++this->vector_[i]; // Поэлементное инкрементирование
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @return The value of the object
    Vector &operator--()
    {
        for (size_t i = 0; i < this->size(); ++i)
        {
            --this->vector_[i]; // Поэлементное декрементирование
        }

        return *this;
    }

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Vector operator++(int)
    {
        Vector temp = *this; // Создаем копию текущего объекта

        // После создания копии увеличиваем каждый элемент
        ++(*this);

        return temp; // Возвращаем исходный объект до изменения
    }

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Vector operator--(int)
    {
        Vector temp = *this; // Создаем копию текущего объекта

        // После создания копии уменьшаем каждый элемент
        --(*this);

        return temp; // Возвращаем исходный объект до изменения
    }

    /// @brief This override method output prints the container
    /// @param os output stream
    /// @param vector obj to print
    /// @return output stream
    friend std::ostream &operator<<(std::ostream &os, const Vector &vector)
    {
        os << extractClassName() << " {\n"; // Форматированный вывод с пробелом после имени класса
        for (size_t i = 0; i < vector.size(); ++i)
        {
            os << i << ":  " << vector[i] << "\n"; // Отступ для элементов вектора
        }
        os << "}";
        return os; // Возвращаем поток для цепочности вызовов
    }

    /// @brief This override method input reads the container
    /// @param is input stream
    /// @param vector obj to read
    /// @return input stream
    friend std::istream &operator>>(std::istream &is, Vector &vector)
    {
        {
            std::string className;
            is >> className;

            is >> std::ws; // Пропускаем пробелы
            if (is.peek() != '{')
            {
                is.setstate(std::ios::failbit); // Устанавливаем флаг ошибки, если формат неверный
                return is;
            }
            is.ignore(); // Пропускаем символ '{'

            vector.clear(); // Очищаем вектор перед чтением новых данных
            Variable value;
            while (is.peek() != '}')
            {
                if (!(is >> value))
                { // Проверяем, удалось ли прочитать элемент
                    is.setstate(std::ios::failbit);
                    return is;
                }
                vector.push_back(value); // Добавляем прочитанный элемент
                is >> std::ws;           // Пропускаем пробелы перед следующим элементом
            }
            is.ignore(); // Пропускаем символ '}'
            return is;
        }
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
        size_t start = funcSigStr.find("Vecto");
        size_t end = funcSigStr.find("r", start);
        if (start != std::string::npos && end != std::string::npos)
        {
            return funcSigStr.substr(start, end - (start - 1));
        }
        return "UnknownClass";
    }
    std::vector<Variable> vector_;
};

Vector operator+(Vector vec, const Variable& other);
Vector operator-(Vector vec, const Variable& other);
#endif /* VECTOR_HPP */