// #include "../include/matrix.hpp"

// template <>
// Matrix Vector::operator+ <Vector>(Vector value)
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