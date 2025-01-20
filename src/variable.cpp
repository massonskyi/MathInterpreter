#include "../include/variable.hpp"
// Явная специализация для int
template <>
inline bool Variable::equals<int>(const int &other) const
{
    try
    {
        return std::get<int>(value_) == other;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error comparing values: " + std::string(e.what()));
    }
}

// Явная специализация для float
template <>
inline bool Variable::equals<float>(const float &other) const
{
    try
    {
        return std::get<float>(value_) == other;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error comparing values: " + std::string(e.what()));
    }
}

// Явная специализация для double
template <>
inline bool Variable::equals<double>(const double &other) const
{
    try
    {
        return std::get<double>(value_) == other;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error comparing values: " + std::string(e.what()));
    }
}
template <>
void Variable::setValue<int>(const int &other)
{
    try
    {
        value_ = std::move(other); // Устанавливаем значение в std::variant
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Unsupported type assignment");
    }
}
template <>
void Variable::setValue<float>(const float &other)
{
    try
    {
        value_ = std::move(other); // Устанавливаем значение в std::variant
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Unsupported type assignment");
    }
}
template <>
void Variable::setValue<double>(const double &other)
{
    try
    {
        value_ = std::move(other); // Устанавливаем значение в std::variant
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Unsupported type assignment");
    }
}
template <>
inline void Variable::set<int>(const int &value)
{
    try
    {
        value_ = value;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error setting int value: " + std::string(e.what()));
    }
}

// Явная специализация для float
template <>
inline void Variable::set<float>(const float &value)
{
    try
    {
        value_ = value;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error setting float value: " + std::string(e.what()));
    }
}

// Явная специализация для double
template <>
inline void Variable::set<double>(const double &value)
{
    try
    {
        value_ = value;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error setting double value: " + std::string(e.what()));
    }
}

// Явная специализация для int
template <>
inline int Variable::getValue<int>() const
{
    try
    {
        const int *valuePtr = std::get_if<int>(&value_);
        if (!valuePtr)
        {
            throw std::runtime_error("Error getting int value: Type mismatch");
        }
        return *valuePtr;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error getting int value: " + std::string(e.what()));
    }
}

// Явная специализация для float
template <>
inline float Variable::getValue<float>() const
{
    try
    {
        const float *valuePtr = std::get_if<float>(&value_);
        if (!valuePtr)
        {
            throw std::runtime_error("Error getting float value: Type mismatch");
        }
        return *valuePtr;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error getting float value: " + std::string(e.what()));
    }
}

// Явная специализация для double
template <>
inline double Variable::getValue<double>() const
{
    try
    {
        const double *valuePtr = std::get_if<double>(&value_);
        if (!valuePtr)
        {
            throw std::runtime_error("Error getting double value: Type mismatch");
        }
        return *valuePtr;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error getting double value: " + std::string(e.what()));
    }
}

// Явная специализация оператора присваивания для int
template <>
inline Variable &Variable::operator= <int>(const int &value)
{
    try
    {
        std::cout<<value<<std::endl;
        setValue(value); // Метод для установки значения
        return *this;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error assigning int value: " + std::string(e.what()) << std::endl;
        throw; // Пробрасываем исключение дальше
    }
}

// Явная специализация оператора присваивания для float
template <>
inline Variable &Variable::operator= <float>(const float &value)
{
    try
    {
        setValue(value); // Метод для установки значения
        return *this;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error assigning float value: " + std::string(e.what()) << std::endl;
        throw; // Пробрасываем исключение дальше
    }
}

// Явная специализация оператора присваивания для double
template <>
inline Variable &Variable::operator= <double>(const double &value)
{
    try
    {
        setValue(value); // Метод для установки значения
        return *this;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error assigning double value: " + std::string(e.what()) << std::endl;
        throw; // Пробрасываем исключение дальше
    }
}
// Явная специализация оператора == для int
template <>
inline bool Variable::operator== <int>(const int &other) const
{
    try
    {
        return std::get<int>(value_) == other;
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Error comparing int values: Type mismatch");
    }
}

// Явная специализация оператора == для float
template <>
inline bool Variable::operator== <float>(const float &other) const
{
    try
    {
        return std::get<float>(value_) == other;
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Error comparing float values: Type mismatch");
    }
}

// Явная специализация оператора == для double
template <>
inline bool Variable::operator== <double>(const double &other) const
{
    try
    {
        return std::get<double>(value_) == other;
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Error comparing double values: Type mismatch");
    }
}

// Явная специализация оператора != для int
template <>
inline bool Variable::operator!= <int>(const int &other) const
{
    try
    {
        return !(std::get<int>(value_) == other);
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Error comparing int values: Type mismatch");
    }
}

// Явная специализация оператора != для float
template <>
inline bool Variable::operator!= <float>(const float &other) const
{
    try
    {
        return !(std::get<float>(value_) == other);
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Error comparing float values: Type mismatch");
    }
}

// Явная специализация оператора != для double
template <>
inline bool Variable::operator!= <double>(const double &other) const
{
    try
    {
        return !(std::get<double>(value_) == other);
    }
    catch (const std::bad_variant_access &)
    {
        throw std::runtime_error("Error comparing double values: Type mismatch");
    }
}

// Оператор умножения для double
template <>
inline Variable Variable::operator* <double>(const double &other)
{
    return binaryOperation(Variable(other), std::multiplies<>());
}

// Оператор деления для int
template <>
inline Variable Variable::operator/ <int>(const int &other)
{
    if (isZero(other))
    {
        throw std::runtime_error("Division by zero");
    }
    return binaryOperation(Variable(other), std::divides<>());
}

// Оператор деления для float
template <>
inline Variable Variable::operator/ <float>(const float &other)
{
    if (isZero(other))
    {
        throw std::runtime_error("Division by zero");
    }
    return binaryOperation(Variable(other), std::divides<>());
}

// Оператор деления для double
template <>
inline Variable Variable::operator/ <double>(const double &other)
{
    if (isZero(other))
    {
        throw std::runtime_error("Division by zero");
    }
    return binaryOperation(Variable(other), std::divides<>());
}

// Оператор взятия остатка (mod) для целых чисел
template <>
inline Variable Variable::operator% <int>(const int &other)
{
    // Проверка, что оба типа являются целочисленными
    if constexpr (std::is_integral_v<int> && std::is_integral_v<decltype(this->value_)>)
    {
        if (isZero(other))
        {
            throw std::runtime_error("Modulo by zero");
        }
        return binaryOperation(Variable(other), std::modulus<>());
    }
    else
    {
        throw std::runtime_error("Modulo operation is only supported for integral types");
    }
}

// Оператор взятия остатка (mod) для float
template <>
inline Variable Variable::operator% <float>(const float &other)
{
    throw std::runtime_error("Modulo operation is only supported for integral types");
}

// Оператор взятия остатка (mod) для double
template <>
inline Variable Variable::operator% <double>(const double &other)
{
    throw std::runtime_error("Modulo operation is only supported for integral types");
}

template <>
Variable &Variable::operator+= <int>(const int &other)
{
    if constexpr (std::is_arithmetic_v<int>)
    {
        *(this) = std::get<int>(value_) + other; // Прямое добавление, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Addition is only supported for arithmetic types");
    }
    return *this;
}
template <>
Variable &Variable::operator+= <float>(const float &other)
{
    if constexpr (std::is_arithmetic_v<float>)
    {
        *(this) = std::get<float>(value_) + other; // Прямое добавление, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Addition is only supported for arithmetic types");
    }
    return *this;
}
template <>
Variable &Variable::operator+= <double>(const double &other)
{
    if constexpr (std::is_arithmetic_v<double>)
    {
        *(this) = std::get<double>(value_) + other; // Прямое добавление, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Addition is only supported for arithmetic types");
    }
    return *this;
}
// Оператор -=
template <>
Variable &Variable::operator-= <int>(const int &other)
{
    if constexpr (std::is_arithmetic_v<int>)
    {
        *(this) = std::get<int>(value_) - other; // Прямое вычитание, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Subtraction is only supported for arithmetic types");
    }
    return *this;
}
template <>
Variable &Variable::operator-= <float>(const float &other)
{
    if constexpr (std::is_arithmetic_v<float>)
    {
        *(this) = std::get<float>(value_) - other; // Прямое вычитание, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Subtraction is only supported for arithmetic types");
    }
    return *this;
}

template <>
Variable &Variable::operator-= <double>(const double &other)
{
    if constexpr (std::is_arithmetic_v<double>)
    {
        *(this) = std::get<double>(value_) - other; // Прямое вычитание, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Subtraction is only supported for arithmetic types");
    }
    return *this;
}
// Оператор *=
template <>
Variable &Variable::operator*= <int>(const int &other)
{
    if constexpr (std::is_arithmetic_v<int>)
    {
        *(this) = std::get<int>(value_) * other; // Прямое умножение, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Multiplication is only supported for arithmetic types");
    }
    return *this;
}
template <>
Variable &Variable::operator*= <float>(const float &other)
{
    if constexpr (std::is_arithmetic_v<float>)
    {
        *(this) = std::get<float>(value_) * other; // Прямое умножение, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Multiplication is only supported for arithmetic types");
    }
    return *this;
}

template <>
Variable &Variable::operator*= <double>(const double &other)
{
    if constexpr (std::is_arithmetic_v<double>)
    {
        *(this) = std::get<double>(value_) * other; // Прямое умножение, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Multiplication is only supported for arithmetic types");
    }
    return *this;
}
// Оператор /=
template <>
Variable &Variable::operator/= <int>(const int &other)
{
    if constexpr (std::is_arithmetic_v<int>)
    {
        if (isZero(other))
        {
            throw std::runtime_error("Division by zero");
        }
        *(this) = std::get<int>(value_) / other; // Прямое деление, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Division is only supported for arithmetic types");
    }
    return *this;
}
template <>
Variable &Variable::operator/= <float>(const float &other)
{
    if constexpr (std::is_arithmetic_v<float>)
    {
        if (isZero(other))
        {
            throw std::runtime_error("Division by zero");
        }
        *(this) = std::get<float>(value_) / other; // Прямое деление, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Division is only supported for arithmetic types");
    }
    return *this;
}

template <>
Variable &Variable::operator/= <double>(const double &other)
{
    if constexpr (std::is_arithmetic_v<double>)
    {
        if (isZero(other))
        {
            throw std::runtime_error("Division by zero");
        }
        *(this) = std::get<double>(value_) / other; // Прямое деление, если _Tp поддерживает арифметику
    }
    else
    {
        throw std::runtime_error("Division is only supported for arithmetic types");
    }
    return *this;
}
// Оператор %=
template <>
Variable &Variable::operator%= <int>(const int &other)
{
    if constexpr (std::is_integral_v<int>)
    {
        if (isZero(other))
        {
            throw std::runtime_error("Modulo by zero");
        }
        *(this) = std::get<int>(value_) % other; // Прямое взятие остатка, если _Tp поддерживает целочисленные типы
    }
    else
    {
        throw std::runtime_error("Modulo operation is only supported for integral types");
    }
    return *this;
}
template <>
Variable &Variable::operator%= <float>(const float &other)
{
    throw std::runtime_error("Modulo operation is only supported for integral types");
}
template <>
Variable &Variable::operator%= <double>(const double &other)
{
    throw std::runtime_error("Modulo operation is only supported for integral types");
}
