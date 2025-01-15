#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include "core.h"
#include "variable.hpp"
#include <numeric>

// Концепт, который проверяет, является ли тип T специализацией шаблона Variable<U>

/// @brief This class is Rational Rational
/// @tparam T type of the Rational
/// @details This class is Rational Rational
template <IsVariable T>
class Rational final : public AbstractObject
{
public:
    using AbstractObject::AbstractObject;
    using value_type = T;
    /// @brief Default constructor
    Rational()
        : AbstractObject(extractClassName()), num_(0), den_(1), type_(determineType(Variable<int>{0})) {};
    /// @brief Constructor with numerator and denominator
    /// @param num numerator
    /// @param den denominator
    explicit Rational(T num, T den)
        : AbstractObject(extractClassName()), num_(num), den_(den), type_(determineType(num_))
    {
        reduce();
    };

    /// @brief Constructor with numerator and default denominator
    /// @param num numerator
    explicit Rational(T num)
        : AbstractObject(extractClassName()), num_(num), den_(1), type_(determineType(num_)) {};

    /// @brief Copy constructor
    /// @param other object to copy
    Rational(const Rational<T> &other)
        : AbstractObject(extractClassName()), num_(other.num_), den_(other.den_), type_(other.type_) {};

    /// @brief Move constructor
    /// @param other object to move
    Rational(Rational<T> &&other)
        : AbstractObject(extractClassName()), num_(std::move(other.num_)), den_(std::move(other.den_)), type_(std::move(other.type_)) {};

    /// @brief Destructor
    ~Rational() = default;

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
    inline std::string toString() const override;

    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
    inline std::string getTypeName() const override;

    /// @brief This method returns the value of the object
    /// @param other Rational to copy compare
    /// @return The value of the object
    Rational<T> &operator=(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to move compare
    /// @return The value of the object
    Rational<T> &operator=(Rational<T> &&other) noexcept;

    /// @brief This method returns the value of the object as a boolean
    /// @param other Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator==(const Rational<T> &other) const;

    /// @brief This method returns the value of the object as a boolean
    /// @param value Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator==(T value) const;

    /// @brief This method returns the value of the object as a boolean
    /// @param value Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator==(const T &value) const;

    /// @brief This method returns the value of the object as a boolean
    /// @param other Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator!=(const Rational<T> &other) const;

    /// @brief This method returns the value of the object as a boolean
    /// @param value Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator!=(T value) const;

    /// @brief This method returns the value of the object as a boolean
    /// @param value Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator!=(const T &value) const;

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational<T> operator+(const Rational<T> &other);

    /// @brief This method returns result of the sub operation
    /// @param other Rational<T> to substract
    /// @return Result of the sub operation
    Rational<T> operator-(const Rational<T> &other);

    /// @brief This method returns result of the mul operation
    /// @param other Rational<T> to multiply
    /// @return Result of the mul operation
    Rational<T> operator*(const Rational<T> &other);

    /// @brief This method returns result of the div operation
    /// @param other Rational<T> to divide
    /// @return Result of the div operation
    Rational<T> operator/(const Rational<T> &other);

    /// @brief This method returns result of the mod operation
    /// @param other Rational<T> to divide
    /// @return Result of the mod operation
    Rational<T> operator%(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to add
    /// @return The value of the object
    Rational<T> operator+(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to substract
    /// @return The value of the object
    Rational<T> operator-(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to multiply
    /// @return The value of the object
    Rational<T> operator*(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    Rational<T> operator/(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    Rational<T> operator%(T value);

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to add
    /// @return The value of the object
    Rational<T> &operator+=(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to substract
    /// @return The value of the object
    Rational<T> &operator-=(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to multiply
    /// @return The value of the object
    Rational<T> &operator*=(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to divide
    /// @return The value of the object
    Rational<T> &operator/=(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to divide
    /// @return The value of the object
    Rational<T> &operator%=(const Rational<T> &other);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to add
    /// @return The value of the object
    Rational<T> &operator+=(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to substract
    /// @return The value of the object
    Rational<T> &operator-=(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to multiply
    /// @return The value of the object
    Rational<T> &operator*=(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    Rational<T> &operator/=(T value);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    Rational<T> &operator%=(T value);

    /// @brief This method returns the value of the object
    /// @return  The value of the object
    Rational<T> &operator++();

    /// @brief This method returns the value of the object
    /// @return The value of the object
    Rational<T> &operator--();

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Rational<T> operator++(int);

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Rational<T> operator--(int);

    /// @brief This friend method of operator << overloading
    /// @param out output stream
    /// @param Rational<T> the value of the object
    /// @return output stream
    friend std::ostream &operator<<(std::ostream &out, const Rational<T> &var)
    {
        try
        {
            if (!out)
            {
                return out; // Return the bad stream instead of throwing
            }

            out << var.toString();

            return out;
        }
        catch (const std::ios_base::failure &e)
        {
            throw std::runtime_error("I/O error in operator<<: " + std::string(e.what()));
        }
        catch (const std::exception &e)
        {
            out.setstate(std::ios::failbit);
            throw std::runtime_error("Unexpected error in operator<<: " + std::string(e.what()));
        }
        catch (...)
        {
            out.setstate(std::ios::failbit);
            throw std::runtime_error("Unknown error in operator<<");
        }
    }

    /// @brief This friend method of operator >> overloading
    /// @param in input stream
    /// @param Rational<T> the value of the object
    /// @return input stream
    friend std::istream &operator>>(std::istream &in, Rational<T> &var)
    {
        try
        {
            // Проверка состояния потока перед операцией
            if (!in)
            {
                throw std::ios_base::failure("Input stream is in bad state");
            }

            // Очищаем возможные ошибки потока
            in.clear();

            // Пропускаем начальные пробелы
            in >> std::ws;

            // Создаем временную переменную для безопасного чтения
            T temp;
            if (!(in >> temp))
            {
                throw std::ios_base::failure("Failed to read value");
            }

            // Присваиваем значение только если чтение прошло успешно
            var.value_ = std::move(temp);

            return in;
        }
        catch (const std::ios_base::failure &e)
        {
            throw std::runtime_error("I/O error in operator>>: " + std::string(e.what()));
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator>>: " + std::string(e.what()));
        }
    };

    /// @brief This friend method of operator == overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return true if the values are equal, false otherwise
    friend bool operator==(const T value, const Rational<T> &var)
    {
        try
        {
            return value == var.value_;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator==: " + std::string(e.what()));
        }
    }

    /// @brief This friend method of operator != overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return true if the values are not equal, false otherwise
    friend bool operator!=(const T value, const Rational<T> &var)
    {
        try
        {
            return value != var.value_;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator!=: " + std::string(e.what()));
        }
    }

    /// @brief This friend method of operator + overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return the value of the object
    friend Rational<T> operator+(const T value, const Rational<T> &var)
    {
        try
        {
            return var + value;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator+: " + std::string(e.what()));
        }
    }

    /// @brief This friend method of operator - overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return the value of the object
    friend Rational<T> operator-(const T value, const Rational<T> &var)
    {
        try
        {
            return var - value;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator-: " + std::string(e.what()));
        }
    }

    /// @brief This friend method of operator * overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return the value of the object
    friend Rational<T> operator*(const T value, const Rational<T> &var)
    {
        try
        {
            return var * value;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator*: " + std::string(e.what()));
        }
    }

    /// @brief This friend method of operator / overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return the value of the object
    friend Rational<T> operator/(const T value, const Rational<T> &var)
    {
        try
        {
            return var / value;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator/: " + std::string(e.what()));
        }
    }

    /// @brief This friend method of operator % overloading
    /// @param value the value of the object
    /// @param var the value of the object
    /// @return the value of the object
    friend Rational<T> operator%(const T value, const Rational<T> &var)
    {
        try
        {
            return var % value;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Unexpected error in operator%: " + std::string(e.what()));
        }
    }

protected:
    static constexpr Type determineType(T num_)
    {
        try
        {
            return num_.getType();
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in determineType: " + std::string(e.what()));
        }
    };

private:
    /// @brief Reduces the fraction to its lowest terms
    void reduce()
    {
        if constexpr (std::is_same_v<T, int>)
        {
            // Handle integer type
            if (den_.getValue() == 0)
            {
                throw std::runtime_error("Division by zero");
            }

            // Handle negative denominators
            if (den_.getValue() < 0)
            {
                num_.getValue(-num_.getValue());
                den_.getValue(-den_.getValue());
            }

            // Calculate GCD and reduce
            T gcd = std::gcd(std::abs(num_.getValue()), std::abs(den_.getValue()));
            if (gcd > 1)
            {
                num_.getValue(num_.getValue() / gcd);
                den_.getValue(den_.getValue() / gcd);
            }
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            // Handle floating-point types
            if (std::abs(den_.getValue()) < std::numeric_limits<T>::epsilon())
            {
                throw std::runtime_error("Division by zero");
            }

            // For floating-point numbers, we normalize by dividing both by denominator
            T normalize = den_.getValue();
            num_.set(num_.getValue() / normalize);
            den_.set(1);
        }
    }

    static std::string extractClassName()
    {
#ifdef _MSC_VER
        const char *funcSig = __FUNCSIG__;
#else
        const char *funcSig = __PRETTY_FUNCTION__;
#endif
        // Extract the class name from the function signature string
        std::string funcSigStr(funcSig);
        size_t start = funcSigStr.find("Rational<");
        size_t end = funcSigStr.find(">::", start);
        if (start != std::string::npos && end != std::string::npos)
        {
            return funcSigStr.substr(start, end - (start - 1));
        }
        return "UnknownClass";
    }

    T num_;
    T den_;
    Type type_;
};

template <IsVariable T>
inline std::string Rational<T>::toString() const
{
    try
    {
        return num_.toString() + "/" + den_.toString();
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in toString : " + std::string(e.what()));
    }
}

template <IsVariable T>
inline std::string Rational<T>::getTypeName() const
{
    try
    {
        return num_.getTypeName() + "/" + den_.getTypeName();
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in getTypeName : " + std::string(e.what()));
    }
}
template <IsVariable T>
Rational<T> &Rational<T>::operator=(const Rational<T> &other)
{
    try
    {
        num_ = other.num_;
        den_ = other.den_;
        type_ = other.type_;
        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator=(Rational<T> &&other) noexcept
{
    try
    {
        num_ = std::move(other.num_);
        den_ = std::move(other.den_);
        type_ = other.type_;
        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator= : " + std::string(e.what()));
    }
}

template <IsVariable T>
bool Rational<T>::operator==(const Rational<T> &other) const
{
    try
    {
        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}
template <IsVariable T>
bool Rational<T>::operator==(T value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        T common_den = den_;
        T this_num = num_;
        T other_num = value * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}

template <IsVariable T>
bool Rational<T>::operator==(const T &value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        T common_den = den_;
        T this_num = num_;
        T other_num = value * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}

template <IsVariable T>
bool Rational<T>::operator!=(const Rational<T> &other) const
{
    try
    {
        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        return this_num != other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}

template <IsVariable T>
bool Rational<T>::operator!=(T value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        T common_den = den_;
        T this_num = num_;
        T other_num = value * den_;

        return this_num != other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}

template <IsVariable T>
bool Rational<T>::operator!=(const T &value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        T common_den = den_;
        T this_num = num_;
        T other_num = value * den_;

        return this_num != other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}
template <IsVariable T>
Rational<T> Rational<T>::operator+(const Rational<T> &other)
{
    try
    {
        // Приводим дроби к общему знаменателю
        T other_num = other.num_;
        T new_num = (num_ * other.den_) + (other_num * den_);
        T new_den = den_ * other.den_;
        return Rational<T>(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator-(const Rational<T> &other)
{
    try
    {
        // Приводим дроби к общему знаменателю

        T other_num = other.num_;
        T new_num = (num_ * other.den_) - (other_num * den_);
        T new_den = den_ * other.den_;
        return Rational<T>(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator- : " + std::string(e.what()));
    }
}
template <IsVariable T>
Rational<T> Rational<T>::operator*(const Rational<T> &other)
{
    try
    {
        T new_num = num_ * other.num_;
        T new_den = den_ * other.den_;
        return Rational<T>(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator* : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator/(const Rational<T> &other)
{
    try
    {
        T new_num = num_ * other.den_;
        T new_den = den_ * other.num_;
        return Rational<T>(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator/ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator%(const Rational<T> &other)
{
    try
    {
        T new_num = num_ * other.den_;
        T new_den = den_ * other.num_;
        return Rational<T>(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator% : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator+(T value)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        // Perform the addition
        T result_num = this_num + other_num;

        return Rational<T>(result_num, common_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator-(T value)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        // Perform the subtraction
        T result_num = this_num - other_num;

        return Rational<T>(result_num, common_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator- : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator*(T value)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Perform the multiplication
        T result_num = num_ * other.num_;
        T result_den = den_ * other.den_;

        return Rational<T>(result_num, result_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator* : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator/(T value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Perform the division
        T result_num = num_ * other.den_;
        T result_den = den_ * other.num_;

        return Rational<T>(result_num, result_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator/ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator%(T value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Perform the modulus operation
        T result_num = num_ % (value * den_);

        return Rational<T>(result_num, den_);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator% : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator+=(const Rational<T> &other)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        // Perform the addition
        T result_num = this_num + other_num;

        // Update the current object
        num_ = result_num;
        den_ = common_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator-=(const Rational<T> &other)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        // Perform the subtraction
        T result_num = this_num - other_num;

        // Update the current object
        num_ = result_num;
        den_ = common_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator-= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator*=(const Rational<T> &other)
{
    try
    {
        // Perform the multiplication
        T result_num = num_ * other.num_;
        T result_den = den_ * other.den_;

        // Update the current object
        num_ = result_num;
        den_ = result_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator*= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator/=(const Rational<T> &other)
{
    try
    {
        if (other.num_ == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Perform the division
        T result_num = num_ * other.den_;
        T result_den = den_ * other.num_;

        // Update the current object
        num_ = result_num;
        den_ = result_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator/= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator%=(const Rational<T> &other)
{
    try
    {
        if (other.num_ == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Perform the modulus operation
        T result_num = num_ % (other.num_ * den_);

        // Update the current object
        num_ = result_num;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator+=(T value)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        // Perform the addition
        T result_num = this_num + other_num;

        // Update the current object
        num_ = result_num;
        den_ = common_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator-=(T value)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Normalize both rational numbers to a common denominator
        T common_den = den_ * other.den_;
        T this_num = num_ * other.den_;
        T other_num = other.num_ * den_;

        // Perform the subtraction
        T result_num = this_num - other_num;

        // Update the current object
        num_ = result_num;
        den_ = common_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator-= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator*=(T value)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Perform the multiplication
        T result_num = num_ * other.num_;
        T result_den = den_ * other.den_;

        // Update the current object
        num_ = result_num;
        den_ = result_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator*= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator/=(T value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Perform the division
        T result_num = num_ * other.den_;
        T result_den = den_ * other.num_;

        // Update the current object
        num_ = result_num;
        den_ = result_den;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator/= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator%=(T value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);

        // Perform the modulus operation
        T result_num = num_ % (value * den_);

        // Update the current object
        num_ = result_num;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator++()
{
    try
    {
        // Increment the numerator by the denominator
        num_ += den_;
        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator++ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> &Rational<T>::operator--()
{
    try
    {
        // Decrement the numerator by the denominator
        num_ -= den_;
        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator-- : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator++(int)
{
    try
    {
        // Create a copy of the current object
        Rational<T> temp = *this;
        // Increment the numerator by the denominator
        num_ += den_;
        return temp;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator++(int) : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> Rational<T>::operator--(int)
{
    try
    {
        // Create a copy of the current object
        Rational<T> temp = *this;
        // Decrement the numerator by the denominator
        num_ -= den_;
        return temp;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator--(int) : " + std::string(e.what()));
    }
}
template <IsVariable T>
bool operator==(const T value, const Rational<T> &var)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other == var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}

template <IsVariable T>
bool operator!=(const T value, const Rational<T> &var)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other != var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator!= : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> operator+(const T value, const Rational<T> &var)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other + var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> operator-(const T value, const Rational<T> &var)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other - var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator- : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> operator*(const T value, const Rational<T> &var)
{
    try
    {
        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other * var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator* : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> operator/(const T value, const Rational<T> &var)
{
    try
    {
        if (var.num_ == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other / var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator/ : " + std::string(e.what()));
    }
}

template <IsVariable T>
Rational<T> operator%(const T value, const Rational<T> &var)
{
    try
    {
        if (var.num_ == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Convert the value to a rational number with denominator 1
        Rational<T> other(value, 1);
        return other % var;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator% : " + std::string(e.what()));
    }
}

#endif /* RATIONAL_HPP */
