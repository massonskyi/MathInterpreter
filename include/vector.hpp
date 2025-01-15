// #ifndef VECTOR_HPP
// #define VECTOR_HPP

// #include "core.h"
// #include "abstractcontainertype.h"
// #include "variable.hpp"
// #include <vector>

// /// @brief The Vector class is a template class that represents a vector
// /// @tparam T The type of the vector
// template <IsVariable T>
// class Vector final : public AbstractContainerType
// {
// public:
//     using AbstractContainerType::AbstractContainerType;
//     using value_type = T;
//     /// @brief Default constructor for the Vector class
//     Vector() : AbstractContainerType(extractClassName()), vector_({}) {}

//     /// @brief Constructor with size params for the Vector class
//     /// @param size The size of the vector
//     explicit Vector(size_t size) : AbstractContainerType(extractClassName()), vector_(size) {}

//     /// @brief Constructor with initializer list for the Vector class
//     /// @param list The initializer list
//     explicit Vector(std::initializer_list<T> list) : AbstractContainerType(extractClassName()), vector_(list) {}
//     /// @brief Copy constructor
//     /// @param other The other vector
//     Vector(const Vector &other) noexcept : AbstractContainerType(extractClassName()), vector_(other.vector_) {}

//     /// @brief Move constructor
//     /// @param other The other vector
//     Vector(Vector &&other) noexcept : AbstractContainerType(extractClassName()), vector_(std::move(other.vector_)) {}

//     /// @brief Destructor
//     ~Vector() override = default;

//     /// @brief  This method is used to print the object
//     /// @return The string representation of the object
//     inline string toString() const override;

//     /// @brief  This method is used to get the type of the object
//     /// @return The type of the object
//     inline string getTypeName() const override;

//     /// @brief This method adds object to the container
//     /// @param object to add be added to the container
//     inline void add(std::shared_ptr<T> object);

//     /// @brief Reserve capacity for the vector
//     /// @param new_cap The new capacity to reserve
//     inline void reserve(size_t new_cap);

//     /// @brief This method returns size of the container
//     /// @return size of the container
//     inline size_t size() const;

//     /// @brief This method returns object by index its index container
//     /// @param index of the object
//     /// @return object by index
//     inline T get(size_t index) const;

//     /// @brief This method returns object by index
//     /// @return data vector
//     inline std::vector<T> getData() const;

//     /// @brief This method returns object by index
//     /// @param index of the object
//     /// @return object by index
//     inline T operator[](size_t index) const;

//     /// @brief This method returns object by index
//     /// @param index of the object
//     /// @return object by index
//     inline T at(size_t index) const;

//     /// @brief This method returns pointer of the container
//     /// @param index of the object
//     /// @return pointer of the container
//     inline std::shared_ptr<T> ptr(size_t index) const;

//     /// @brief This method return first element of the container
//     /// @return first element of the container
//     inline std::shared_ptr<T> front() const;

//     /// @brief This method return last element of the container
//     /// @return last element of the container
//     inline std::shared_ptr<T> back() const;

//     /// @brief This method adds object to the container end of the container
//     /// @param var to add to the container
//     inline void push_back(const T &var);

//     /// @brief This method adds object to the container end of the container
//     /// @param var to add to the container
//     inline void append(const T &var);

//     /// @brief This method removes object from the container
//     /// @param index of the object
//     inline void remove(size_t index);

//     /// @brief This method removes object from the container first of the container
//     /// @param var to add to the container
//     inline void pop_front();

//     /// @brief This method removes object from the container end of the container
//     /// @param var to add to the container
//     inline void pop_back();

//     /// @brief This method clears the container
//     inline void clear();

//     /// @brief This method erases object from the container
//     /// @param index of the object
//     inline void erase(size_t index);

//     /// @brief This method inserts object to the container
//     /// @param insert index of the object
//     /// @param var to add to the container
//     inline void insert(size_t insert, const T &var);

//     /// @brief This method resizes the container
//     /// @param size of the container
//     inline void resize(size_t size);

//     /// @brief This method swaps two containers
//     /// @param other container
//     inline void swap(Vector &other) noexcept;

//     /// @brief This method returns begin iterator of the container
//     /// @return begin iterator of the container
//     std::vector<T>::iterator begin();

//     /// @brief This method returns end iterator of the container
//     /// @return end iterator of the container
//     std::vector<T>::iterator end();

//     /// @brief This method returns const begin iterator of the container
//     /// @return const begin iterator of the container
//     std::vector<T>::const_iterator cbegin() const;

//     /// @brief This method returns const end iterator of the container
//     /// @return const end iterator of the container
//     std::vector<T>::const_iterator cend() const;

//     /// @brief This method returns the value of the object
//     /// @param other Variable to copy compare
//     /// @return The value of the object
//     Vector<T> &operator=(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to move compare
//     /// @return The value of the object
//     Vector<T> &operator=(Vector<T> &&other) noexcept;

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to copy compare
//     /// @return The value of the object
//     Vector<T> &operator=(T value);

//     /// @brief This method returns the value of the object as a boolean
//     /// @param other Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator==(const Vector<T> &other) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param value Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator==(T value) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param other Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator!=(const Vector<T> &other) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param value Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator!=(T value) const;

//     /// @brief This method returns result of the add operation
//     /// @param other Variable<T> to add
//     /// @return Result of the add operation
//     Vector<T> operator+(const Vector<T> &other);

//     /// @brief This method returns result of the sub operation
//     /// @param other Variable<T> to substract
//     /// @return Result of the sub operation
//     Vector<T> operator-(const Vector<T> &other);

//     /// @brief This method returns result of the mul operation
//     /// @param other Variable<T> to multiply
//     /// @return Result of the mul operation
//     Vector<T> operator*(const Vector<T> &other);

//     /// @brief This method returns result of the div operation
//     /// @param other Variable<T> to divide
//     /// @return Result of the div operation
//     Vector<T> operator/(const Vector<T> &other);

//     /// @brief This method returns result of the mod operation
//     /// @param other Variable<T> to divide
//     /// @return Result of the mod operation
//     Vector<T> operator%(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to add
//     /// @return The value of the object
//     Vector<T> operator+(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to substract
//     /// @return The value of the object
//     Vector<T> operator-(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to multiply
//     /// @return The value of the object
//     Vector<T> operator*(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Vector<T> operator/(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Vector<T> operator%(T value);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to add
//     /// @return The value of the object
//     Vector<T> &operator+=(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to substract
//     /// @return The value of the object
//     Vector<T> &operator-=(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to multiply
//     /// @return The value of the object
//     Vector<T> &operator*=(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to divide
//     /// @return The value of the object
//     Vector<T> &operator/=(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to divide
//     /// @return The value of the object
//     Vector<T> &operator%=(const Vector<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to add
//     /// @return The value of the object
//     Vector<T> &operator+=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to substract
//     /// @return The value of the object
//     Vector<T> &operator-=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to multiply
//     /// @return The value of the object
//     Vector<T> &operator*=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Vector<T> &operator/=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Vector<T> &operator%=(T value);

//     /// @brief This method returns the value of the object
//     /// @return  The value of the object
//     Vector<T> &operator++();

//     /// @brief This method returns the value of the object
//     /// @return The value of the object
//     Vector<T> &operator--();

//     /// @brief This method returns the value of the object
//     /// @param  this the value of the object
//     /// @return The value of the object
//     Vector<T> operator++(int);

//     /// @brief This method returns the value of the object
//     /// @param  this the value of the object
//     /// @return The value of the object
//     Vector<T> operator--(int);

//     /// @brief This override method output prints the container
//     /// @param os output stream
//     /// @param vector obj to print
//     /// @return output stream
//     friend std::ostream &operator<<(std::ostream &os, const Vector &vector)
//     {
//         os << vector.extractClassName() << " {\n"; // Форматированный вывод с пробелом после имени класса
//         for (size_t i = 0; i < vector.size(); ++i)
//         {
//             os << i << ":  " << vector[i] << "\n"; // Отступ для элементов вектора
//         }
//         os << "}";
//         return os; // Возвращаем поток для цепочности вызовов
//     }

//     /// @brief This override method input reads the container
//     /// @param is input stream
//     /// @param vector obj to read
//     /// @return input stream
//     friend std::istream &operator>>(std::istream &is, Vector &vector)
//     {
//         {
//             std::string className;
//             is >> className;
//             vector.setClassName(className); // Устанавливаем имя класса

//             is >> std::ws; // Пропускаем пробелы
//             if (is.peek() != '{')
//             {
//                 is.setstate(std::ios::failbit); // Устанавливаем флаг ошибки, если формат неверный
//                 return is;
//             }
//             is.ignore(); // Пропускаем символ '{'

//             vector.clear(); // Очищаем вектор перед чтением новых данных
//             T value;
//             while (is.peek() != '}')
//             {
//                 if (!(is >> value))
//                 { // Проверяем, удалось ли прочитать элемент
//                     is.setstate(std::ios::failbit);
//                     return is;
//                 }
//                 vector.push_back(value); // Добавляем прочитанный элемент
//                 is >> std::ws;           // Пропускаем пробелы перед следующим элементом
//             }
//             is.ignore(); // Пропускаем символ '}'
//             return is;
//         }
//     }

// private:
//     static std::string extractClassName()
//     {
// #ifdef _MSC_VER
//         const char *funcSig = __FUNCSIG__;
// #else
//         const char *funcSig = __PRETTY_FUNCTION__;
// #endif
//         // Extract the class name from the function signature string
//         std::string funcSigStr(funcSig);
//         size_t start = funcSigStr.find("Vector<");
//         size_t end = funcSigStr.find(">::", start);
//         if (start != std::string::npos && end != std::string::npos)
//         {
//             return funcSigStr.substr(start, end - (start - 1));
//         }
//         return "UnknownClass";
//     }
//     std::vector<T> vector_;
// };

// template <IsVariable T>
// inline void Vector<T>::add(std::shared_ptr<T> object)
// {
//     try
//     {
//         if (!object)
//         {
//             throw std::invalid_argument("Cannot add a nullptr to the vector.");
//         }
//         vector_.push_back(*object);
//     }
//     catch (const std::exception &e)
//     {
//         // Логирование ошибки
//         std::cerr << "[Error] Failed to add object: " << e.what() << std::endl;
//         throw; // Повторное выбрасывание исключения для обработки выше
//     }
// }

// template <IsVariable T>
// inline size_t Vector<T>::size() const
// {
//     try
//     {
//         return vector_.size();
//     }
//     catch (const std::exception &e)
//     {
//         // Логирование ошибки
//         std::cerr << "[Error] Failed to get size: " << e.what() << std::endl;
//         throw; // Повторное выбрасывание исключения для обработки выше
//     }
// }

// template <IsVariable T>
// inline T Vector<T>::get(size_t index) const
// {
//     try
//     {
//         if (index >= vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         return vector_[index];
//     }
//     catch (const std::exception &e)
//     {
//         // Логирование ошибки
//         std::cerr << "[Error] Failed to get object at index " << index << ": " << e.what() << std::endl;
//         throw; // Повторное выбрасывание исключения для обработки выше
//     }
// }
// template <IsVariable T>
// inline void Vector<T>::push_back(const T &var)
// {
//     try
//     {
//         vector_.push_back(var);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] push_back: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <IsVariable T>
// inline void Vector<T>::remove(size_t index)
// {
//     try
//     {
//         if (index >= vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         vector_.erase(vector_.begin() + index);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] remove: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <IsVariable T>
// inline void Vector<T>::pop_front()
// {
//     try
//     {
//         if (vector_.empty())
//         {
//             throw std::out_of_range("Cannot pop from an empty vector.");
//         }
//         vector_.erase(vector_.begin());
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] pop_front: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <IsVariable T>
// inline T Vector<T>::operator[](size_t index) const
// {
//     try
//     {
//         if (index >= vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         return vector_[index];
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] operator[]: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline std::shared_ptr<T> Vector<T>::ptr(size_t index) const
// {
//     try
//     {
//         if (index >= vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         return std::make_shared<T>(vector_[index]);
//     }
//     catch (const std::exception &e)
//     {
//         // Логирование ошибки
//         std::cerr << "[Error] Failed to get object at index " << index << ": " << e.what() << std::endl;
//         throw; // Повторное выбрасывание исключения для обработки выше
//     }
// }
// template <IsVariable T>
// inline T Vector<T>::at(size_t index) const
// {
//     try
//     {
//         if (index >= vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         return vector_[index];
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] at: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline std::shared_ptr<T> Vector<T>::front() const
// {
//     try
//     {
//         if (vector_.empty())
//         {
//             throw std::out_of_range("Vector is empty.");
//         }
//         return std::make_shared<T>(vector_.front());
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] front: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline std::shared_ptr<T> Vector<T>::back() const
// {
//     try
//     {
//         if (vector_.empty())
//         {
//             throw std::out_of_range("Vector is empty.");
//         }
//         return std::make_shared<T>(vector_.back());
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] back: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <IsVariable T>
// inline void Vector<T>::append(const T &var)
// {
//     try
//     {
//         vector_.push_back(var);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] append: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline void Vector<T>::pop_back()
// {
//     try
//     {
//         if (vector_.empty())
//         {
//             throw std::out_of_range("Cannot pop from an empty vector.");
//         }
//         vector_.pop_back();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] pop_back: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline void Vector<T>::clear()
// {
//     try
//     {
//         vector_.clear();
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] clear: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline void Vector<T>::erase(size_t index)
// {
//     try
//     {
//         if (index >= vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         vector_.erase(vector_.begin() + index);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] erase: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline void Vector<T>::insert(size_t index, const T &var)
// {
//     try
//     {
//         if (index > vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         vector_.insert(vector_.begin() + index, var);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] insert: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <IsVariable T>
// inline void Vector<T>::resize(size_t size)
// {
//     try
//     {
//         vector_.resize(size);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] resize: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <IsVariable T>
// inline void Vector<T>::swap(Vector &other) noexcept
// {
//     try
//     {
//         vector_.swap(other.vector_);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] swap: " << e.what() << std::endl;
//         // Исключение не выбрасывается, так как метод объявлен noexcept
//     }
// }

// template <IsVariable T>
// std::vector<T>::iterator Vector<T>::begin()
// {
//     return vector_.begin();
// }
// template <IsVariable T>
// std::vector<T>::iterator Vector<T>::end()
// {
//     return vector_.end();
// }
// template <IsVariable T>
// std::vector<T>::const_iterator Vector<T>::cbegin() const
// {
//     return vector_.cbegin();
// }
// template <IsVariable T>
// std::vector<T>::const_iterator Vector<T>::cend() const
// {
//     return vector_.cend();
// }
// template <IsVariable T>
// Vector<T> &Vector<T>::operator=(const Vector<T> &other)
// {
//     if (this == &other)
//     {
//         return *this; // Присваивание самому себе, ничего не делаем
//     }

//     try
//     {
//         vector_ = other.vector_; // Копирование содержимого из другого вектора
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] Copy assignment: " << e.what() << std::endl;
//         throw; // Пробрасываем исключение, если произошла ошибка
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
// {
//     if (this == &other)
//     {
//         return *this; // Присваивание самому себе
//     }

//     try
//     {
//         vector_ = std::move(other.vector_); // Перемещаем содержимое другого объекта
//         // После перемещения вектор other находится в неопределенном, но валидном состоянии
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] Move assignment: " << e.what() << std::endl;
//         throw; // Пробрасываем исключение, если произошла ошибка
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator=(T value)
// {
//     try
//     {
//         reserve(size() + 1);
//         append(value);

//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] Assignment with value: " << e.what() << std::endl;
//         throw; // Пробрасываем исключение, если произошла ошибка
//     }

//     return *this;
// }

// template <IsVariable T>
// bool Vector<T>::operator==(const Vector<T> &other) const
// {
//     // Проверяем, что размеры векторов одинаковы
//     if (this->size() != other.size())
//     {
//         return false; // Если размеры разные, векторы не равны
//     }

//     // Сравниваем элементы векторов
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         if (this->get(i) != other.get(i))
//         {
//             return false; // Если хотя бы один элемент не совпадает, векторы не равны
//         }
//     }

//     return true; // Все элементы совпадают
// }

// template <IsVariable T>
// bool Vector<T>::operator==(T value) const
// {
//     if (this->size() == 0)
//     {
//         return false; // Пустой вектор не может быть равен значению
//     }

//     // Сравниваем первый элемент вектора с заданным значением
//     return (this->get(0) == value);
// }

// template <IsVariable T>
// bool Vector<T>::operator!=(const Vector<T> &other) const
// {
//     return !(*this == other);
// }

// template <IsVariable T>
// bool Vector<T>::operator!=(T value) const
// {
//     return !(*this == value); // Если вектор не равен значению, возвращаем true
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator+(const Vector<T> &other)
// {
//     // Проверка на одинаковые размеры
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for addition.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) + other.get(i)); // Поэлементное сложение
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator-(const Vector<T> &other)
// {
//     // Проверка на одинаковые размеры
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for subtraction.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) - other.get(i)); // Поэлементное вычитание
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator*(const Vector<T> &other)
// {
//     // Проверка на одинаковые размеры
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for multiplication.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) * other.get(i)); // Поэлементное умножение
//     }

//     return result;
// }
// template <IsVariable T>
// void Vector<T>::reserve(size_t new_cap)
// {
//     vector_.reserve(new_cap);
// }
// template <IsVariable T>
// Vector<T> Vector<T>::operator/(const Vector<T> &other)
// {
//     // Проверка на одинаковые размеры
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for division.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         if (other.get(i) == 0)
//         {
//             throw std::invalid_argument("Division by zero.");
//         }
//         result.push_back(this->get(i) / other.get(i)); // Поэлементное деление
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator%(const Vector<T> &other)
// {
//     // Проверка на одинаковые размеры
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for modulo.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         if (other.get(i) == 0)
//         {
//             throw std::invalid_argument("Modulo by zero.");
//         }
//         result.push_back(this->get(i) % other.get(i)); // Поэлементное взятие остатка
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator+(T value)
// {
//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) + value); // Поэлементное сложение с числом
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator-(T value)
// {
//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) - value); // Поэлементное вычитание с числом
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator*(T value)
// {
//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) * value); // Поэлементное умножение на число
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator/(T value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Division by zero.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) / value); // Поэлементное деление на число
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator%(T value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Modulo by zero.");
//     }

//     Vector<T> result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) % value); // Поэлементное взятие остатка от деления на число
//     }

//     return result;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator+=(const Vector<T> &other)
// {
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for addition.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] += other.get(i); // Поэлементное сложение
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator-=(const Vector<T> &other)
// {
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for subtraction.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] -= other.get(i); // Поэлементное вычитание
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator*=(const Vector<T> &other)
// {
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for multiplication.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] *= other.get(i); // Поэлементное умножение
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator/=(const Vector<T> &other)
// {
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for division.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         if (other.get(i) == 0)
//         {
//             throw std::invalid_argument("Division by zero.");
//         }
//         this->vector_[i] /= other.get(i); // Поэлементное деление
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator%=(const Vector<T> &other)
// {
//     if (this->size() != other.size())
//     {
//         throw std::invalid_argument("Vectors must have the same size for modulo.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         if (other.get(i) == 0)
//         {
//             throw std::invalid_argument("Modulo by zero.");
//         }
//         this->vector_[i] %= other.get(i); // Поэлементное взятие остатка
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator+=(T value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] += value; // Поэлементное сложение
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator-=(T value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] -= value; // Поэлементное вычитание
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator*=(T value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] *= value; // Поэлементное умножение
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator/=(T value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Division by zero.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] /= value; // Поэлементное деление
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator%=(T value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Modulo by zero.");
//     }

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] %= value; // Поэлементное взятие остатка
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator++()
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         ++this->vector_[i]; // Поэлементное инкрементирование
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> &Vector<T>::operator--()
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         --this->vector_[i]; // Поэлементное декрементирование
//     }

//     return *this;
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator++(int)
// {
//     Vector<T> temp = *this; // Создаем копию текущего объекта

//     // После создания копии увеличиваем каждый элемент
//     ++(*this);

//     return temp; // Возвращаем исходный объект до изменения
// }

// template <IsVariable T>
// Vector<T> Vector<T>::operator--(int)
// {
//     Vector<T> temp = *this; // Создаем копию текущего объекта

//     // После создания копии уменьшаем каждый элемент
//     --(*this);

//     return temp; // Возвращаем исходный объект до изменения
// }
// template <IsVariable T>
// inline std::string Vector<T>::toString() const
// {
//     std::stringstream ss;
//     ss << "Vector of " << typeid(T).name() << " with size " << this->size() << ": [";

//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         if (i != 0)
//             ss << ", ";
//         ss << this->vector_[i];
//     }

//     ss << "]";
//     return ss.str(); // Возвращаем строковое представление объекта
// }

// template <IsVariable T>
// inline std::string Vector<T>::getTypeName() const
// {
//     return typeid(*this).name(); // Возвращаем строку, представляющую тип объекта
// }

// template <IsVariable T>
// inline std::vector<T> Vector<T>::getData() const
// {
//     return this->vector_;
// }
// #endif /* VECTOR_HPP */
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "core.h"
#include "abstractcontainertype.h"
#include "variable.hpp"
#include <vector>

/// @brief The Vector class represents a vector of integers
class Vector final : public AbstractContainerType
{
public:
    using AbstractContainerType::AbstractContainerType;
    using value_type = int;

    /// @brief Default constructor for the Vector class
    Vector() : AbstractContainerType(extractClassName()), vector_({}) {}

    /// @brief Constructor with size params for the Vector class
    /// @param size The size of the vector
    explicit Vector(size_t size) : AbstractContainerType(extractClassName()), vector_(size) {}

    /// @brief Constructor with initializer list for the Vector class
    /// @param list The initializer list
    explicit Vector(std::initializer_list<int> list) : AbstractContainerType(extractClassName()), vector_(list) {}

    /// @brief Copy constructor
    /// @param other The other vector
    Vector(const Vector &other) noexcept : AbstractContainerType(extractClassName()), vector_(other.vector_) {}

    /// @brief Move constructor
    /// @param other The other vector
    Vector(Vector &&other) noexcept : AbstractContainerType(extractClassName()), vector_(std::move(other.vector_)) {}

    /// @brief Destructor
    ~Vector() override = default;

    /// @brief This method is used to print the object
    /// @return The string representation of the object
    inline std::string toString() const override;

    /// @brief This method is used to get the type of the object
    /// @return The type of the object
    inline std::string getTypeName() const override;

    /// @brief This method adds an object to the container
    /// @param object to be added to the container
    inline void add(int object);

    /// @brief Reserve capacity for the vector
    /// @param new_cap The new capacity to reserve
    inline void reserve(size_t new_cap);

    /// @brief This method returns the size of the container
    /// @return size of the container
    inline size_t size() const;

    /// @brief This method returns the object by its index in the container
    /// @param index of the object
    /// @return object by index
    inline int get(size_t index) const;

    /// @brief This method returns the data vector
    /// @return data vector
    inline std::vector<int> getData() const;

    /// @brief This method returns the object by its index
    /// @param index of the object
    /// @return object by index
    inline int operator[](size_t index) const;

    /// @brief This method returns the object by its index
    /// @param index of the object
    /// @return object by index
    inline int at(size_t index) const;

    /// @brief This method returns a pointer to the object in the container
    /// @param index of the object
    /// @return pointer to the object
    inline std::shared_ptr<int> ptr(size_t index) const;

    /// @brief This method returns the first element of the container
    /// @return first element of the container
    inline std::shared_ptr<int> front() const;

    /// @brief This method returns the last element of the container
    /// @return last element of the container
    inline std::shared_ptr<int> back() const;

    /// @brief This method adds an object to the end of the container
    /// @param var to add to the container
    inline void push_back(const int &var);

    /// @brief This method adds an object to the end of the container
    /// @param var to add to the container
    inline void append(const int &var);

    /// @brief This method removes an object from the container
    /// @param index of the object
    inline void remove(size_t index);

    /// @brief This method removes the first object from the container
    inline void pop_front();

    /// @brief This method removes the last object from the container
    inline void pop_back();

    /// @brief This method clears the container
    inline void clear();

    /// @brief This method erases an object from the container
    /// @param index of the object
    inline void erase(size_t index);

    /// @brief This method inserts an object into the container
    /// @param insert index of the object
    /// @param var to add to the container
    inline void insert(size_t insert, const int &var);

    /// @brief This method resizes the container
    /// @param size of the container
    inline void resize(size_t size);

    /// @brief This method swaps two containers
    /// @param other container
    inline void swap(Vector &other) noexcept;

    /// @brief This method returns the begin iterator of the container
    /// @return begin iterator of the container
    std::vector<int>::iterator begin();

    /// @brief This method returns the end iterator of the container
    /// @return end iterator of the container
    std::vector<int>::iterator end();

private:
    std::vector<int> vector_;
};

#endif // VECTOR_HPP
