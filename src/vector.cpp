// #include "../include/types/vector.hpp"
// template <>
// Vector::Vector<int>(std::initializer_list<int> list) : AbstractContainerType(extractClassName()) {
//     for (const auto& elem : list) {
//         vector_.emplace_back(Variable(elem));
//     }
// }

// template <>
// Vector::Vector<float>(std::initializer_list<float> list) : AbstractContainerType(extractClassName()) {
//     for (const auto& elem : list) {
//         vector_.emplace_back(Variable(elem));
//     }
// }

// template <>
// Vector::Vector<double>(std::initializer_list<double> list) : AbstractContainerType(extractClassName()) {
//     for (const auto& elem : list) {
//         vector_.emplace_back(Variable(elem));
//     }
// }
// template <>
// inline void Vector::push_back<int>(const int &var)
// {
//     try
//     {
//         vector_.push_back(Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] push_back: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::push_back<float>(const float &var)
// {
//     try
//     {
//         vector_.push_back(Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] push_back: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::push_back<double>(const double &var)
// {
//     try
//     {
//         vector_.push_back(Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] push_back: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::append<int>(const int &var)
// {
//     try
//     {
//         vector_.push_back(Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] append: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::append<float>(const float &var)
// {
//     try
//     {
//         vector_.push_back(Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] append: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::append<double>(const double &var)
// {
//     try
//     {
//         vector_.push_back(Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] append: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::insert<int>(size_t index, const int &var)
// {
//     try
//     {
//         if (index > vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         vector_.insert(vector_.begin() + index, Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] insert: " << e.what() << std::endl;
//         throw;
//     }
// }
// template <>
// inline void Vector::insert<float>(size_t index, const float &var)
// {
//     try
//     {
//         if (index > vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         vector_.insert(vector_.begin() + index, Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] insert: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// inline void Vector::insert<double>(size_t index, const double &var)
// {
//     try
//     {
//         if (index > vector_.size())
//         {
//             throw std::out_of_range("Index is out of bounds.");
//         }
//         vector_.insert(vector_.begin() + index, Variable(var));
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] insert: " << e.what() << std::endl;
//         throw;
//     }
// }

// template <>
// Vector &Vector::operator= <int>(int value)
// {
//     try
//     {
//         reserve(size() + 1);
//         append(Variable(value));

//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] Assignment with value: " << e.what() << std::endl;
//         throw; // Пробрасываем исключение, если произошла ошибка
//     }

//     return *this;
// }

// template <>
// Vector &Vector::operator= <float>(float value)
// {
//     try
//     {
//         reserve(size() + 1);
//         append(Variable(value));

//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] Assignment with value: " << e.what() << std::endl;
//         throw; // Пробрасываем исключение, если произошла ошибка
//     }

//     return *this;
// }

// template <>
// Vector &Vector::operator= <double>(double value)
// {
//     try
//     {
//         reserve(size() + 1);
//         append(Variable(value));

//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "[Error] Assignment with value: " << e.what() << std::endl;
//         throw; // Пробрасываем исключение, если произошла ошибка
//     }

//     return *this;
// }

// template <>
// Vector Vector::operator+ <int>(int value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) + value); // Поэлементное сложение с числом
//     }

//     return result;
// }

// template <>
// Vector Vector::operator+ <float>(float value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) + value); // Поэлементное сложение с числом
//     }

//     return result;
// }

// template <>
// Vector Vector::operator+ <double>(double value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) + value); // Поэлементное сложение с числом
//     }

//     return result;
// }

// template <>
// Vector Vector::operator- <int>(int value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) - value); // Поэлементное вычитание с числом
//     }

//     return result;
// }
// template <>
// Vector Vector::operator- <float>(float value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) - value); // Поэлементное вычитание с числом
//     }

//     return result;
// }

// template <>
// Vector Vector::operator- <double>(double value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) - value); // Поэлементное вычитание с числом
//     }

//     return result;
// }

// template <>
// Vector Vector::operator* <int>(int value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) * value); // Поэлементное умножение на число
//     }

//     return result;
// }
// template <>
// Vector Vector::operator* <float>(float value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) * value); // Поэлементное умножение на число
//     }

//     return result;
// }
// template <>
// Vector Vector::operator* <double>(double value)
// {
//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) * value); // Поэлементное умножение на число
//     }

//     return result;
// }

// template <>
// Vector Vector::operator/ <int>(int value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Division by zero.");
//     }

//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) / value); // Поэлементное деление на число
//     }

//     return result;
// }

// template <>
// Vector Vector::operator/ <float>(float value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Division by zero.");
//     }

//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) / value); // Поэлементное деление на число
//     }

//     return result;
// }
// template <>
// Vector Vector::operator/ <double>(double value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Division by zero.");
//     }

//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) / value); // Поэлементное деление на число
//     }

//     return result;
// }
// template <>
// Vector Vector::operator% <int>(int value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Modulo by zero.");
//     }

//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) % value); // Поэлементное взятие остатка от деления на число
//     }

//     return result;
// }
// template <>
// Vector Vector::operator% <float>(float value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Modulo by zero.");
//     }

//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) % value); // Поэлементное взятие остатка от деления на число
//     }

//     return result;
// }
// template <>
// Vector Vector::operator% <double>(double value)
// {
//     if (value == 0)
//     {
//         throw std::invalid_argument("Modulo by zero.");
//     }

//     Vector result;
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         result.push_back(this->get(i) % value); // Поэлементное взятие остатка от деления на число
//     }

//     return result;
// }

// template <>
// Vector &Vector::operator+= <int>(int value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] += value; // Поэлементное сложение
//     }

//     return *this;
// }
// template <>
// Vector &Vector::operator+= <float>(float value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] += value; // Поэлементное сложение
//     }

//     return *this;
// }
// template <>
// Vector &Vector::operator+= <double>(double value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] += value; // Поэлементное сложение
//     }

//     return *this;
// }

// template <>
// Vector &Vector::operator-= <int>(int value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] -= value; // Поэлементное вычитание
//     }

//     return *this;
// }
// template <>
// Vector &Vector::operator-= <float>(float value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] -= value; // Поэлементное вычитание
//     }

//     return *this;
// }
// template <>
// Vector &Vector::operator-= <double>(double value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] -= value; // Поэлементное вычитание
//     }

//     return *this;
// }

// template <>
// Vector &Vector::operator*= <int>(int value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] *= value; // Поэлементное умножение
//     }

//     return *this;
// }
// template <>
// Vector &Vector::operator*= <float>(float value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] *= value; // Поэлементное умножение
//     }

//     return *this;
// }
// template <>
// Vector &Vector::operator*= <double>(double value)
// {
//     for (size_t i = 0; i < this->size(); ++i)
//     {
//         this->vector_[i] *= value; // Поэлементное умножение
//     }

//     return *this;
// }

// template <>
// Vector &Vector::operator/= <int>(int value)
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
// template <>
// Vector &Vector::operator/= <float>(float value)
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
// template <>
// Vector &Vector::operator/= <double>(double value)
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

// template <>
// Vector &Vector::operator%= <int>(int value)
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
// template <>
// Vector &Vector::operator%= <float>(float value)
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

// template <>
// Vector &Vector::operator%= <double>(double value)
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