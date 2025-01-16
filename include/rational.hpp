#ifndef RATIONAL_H
#define RATIONAL_H

#include "core.h"
#include "variable.hpp"
#include <numeric>

/// @brief This class is Rational Rational
/// @tparam T type of the Rational
/// @details This class is Rational Rational
class Rational final : public AbstractObject
{
public:
    using AbstractObject::AbstractObject;

    /// @brief Default constructor
    Rational()
        : AbstractObject(extractClassName()), num_(0), den_(1), type_(determineType(Variable{0}))
    {
    }

    /// @brief Constructor with numerator and denominator
    /// @param num numerator
    /// @param den denominator
    explicit Rational(Variable num, Variable den) : AbstractObject(extractClassName()), num_(num), den_(den), type_(determineType(num_))
    {
    }

    /// @brief Constructor with numerator and default denominator
    /// @param num numerator
    explicit Rational(Variable num) : AbstractObject(extractClassName()), num_(num), den_(1), type_(determineType(num_)) {};

    /// @brief Copy constructor
    /// @param other object to copy
    Rational(const Rational &other)
        : AbstractObject(extractClassName()), num_(other.num_), den_(other.den_), type_(other.type_) {};

    /// @brief Move constructor
    /// @param other object to move
    Rational(Rational &&other) noexcept
        : AbstractObject(extractClassName()), num_(std::move(other.num_)), den_(std::move(other.den_)), type_(std::move(other.type_)) {};

    /// @brief Destructor
    ~Rational() = default;

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
    inline std::string toString() const override
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

    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
    inline std::string getTypeName() const override
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

    /// @brief This method returns the value of the object
    /// @param other Rational to copy compare
    /// @return The value of the object
    Rational &operator=(const Rational &other)
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

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to move compare
    /// @return The value of the object
    Rational &operator=(Rational &&other) noexcept
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
        std::cerr << "Error in operator= : " + std::string(e.what()) << std::endl;
    }
}


    /// @brief This method returns the value of the object as a boolean
    /// @param other Rational<T> to compare
    /// @return The value of the object as a boolean
    bool operator==(const Rational &other) const
    {
    try
    {
        // Normalize both rational numbers to a common denominator
        Variable common_den = den_ * other.den_;
        Variable this_num = num_ * other.den_;
        Variable other_num = other.num_ * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}


    /// @brief This method returns the value of the object as a boolean
    /// @param value Rational<T> to compare
    /// @return The value of the object as a boolean
    template <AllowedTypes _Tp>
    bool operator==(_Tp value) const
    {
        try
        {
            // Normalize both rational numbers to a common denominator
            _Tp common_den = den_ * value.den_;
            _Tp this_num = num_ * value.den_;
            _Tp other_num = value.num_ * den_;

            return this_num == other_num;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator== : " + std::string(e.what()));
        }
    }

    /// @brief This method is used to get the value of the object
    /// @param other Rational to copy compare
    /// @return The value of the object
    bool operator!=(const Rational &other) const
    {
    try
    {
        // Normalize both rational numbers to a common denominator
        Variable common_den = den_ * other.den_;
        Variable this_num = num_ * other.den_;
        Variable other_num = other.num_ * den_;

        return this_num != other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}

    /// @brief This method is used to get the value of the object
    /// @param other Rational to copy compare
    /// @return The value of the object
    template <AllowedTypes _Tp>
    bool operator!=(const _Tp &other) const;

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator+(const Rational &other)
    {
    try
    {
        // Приводим дроби к общему знаменателю
        Variable other_num = other.num_;
        Variable new_num = (num_ * other.den_) + (other_num * den_);
        Variable new_den = den_ * other.den_;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

    /// @brief This method returns result of the sub operation
    /// @param other Rational<T> to substract
    /// @return Result of the sub operation
    Rational operator-(const Rational &other)
    {
    try
    {
        // Приводим дроби к общему знаменателю
        Variable other_num = other.num_;
        Variable new_num = (num_ * other.den_) - (other_num * den_);
        Variable new_den = den_ * other.den_;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

    /// @brief This method returns result of the mul operation
    /// @param other Rational<T> to multiply
    /// @return Result of the mul operation
    Rational operator*(const Rational &other)
    {
    try
    {
        Variable new_num = num_ * other.num_;
        Variable new_den = den_ * other.den_;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator* : " + std::string(e.what()));
    }
}

    /// @brief This method returns result of the div operation
    /// @param other Rational<T> to divide
    /// @return Result of the div operation
    Rational operator/(const Rational &other)
    {
    try
    {
        Variable new_num = num_ * other.den_;
        Variable new_den = den_ * other.num_;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator/ : " + std::string(e.what()));
    }
}


    /// @brief This method returns result of the mod operation
    /// @param other Rational<T> to divide
    /// @return Result of the mod operation
    Rational operator%(const Rational &other);

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to add
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational operator+(_Tp value)
    {
        try
        {
            // Приводим дроби к общему знаменателю
            _Tp other_num = value;
            Variable new_num = (num_ * value) + (den_ * other_num);
            Variable new_den = den_ * value;
            return Rational(new_num, new_den);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to substract
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational operator-(_Tp value)
    {
        try
        {
            // Приводим дроби к общему знаменателю
            _Tp other_num = value;
            Variable new_num = (num_ * value) - (other_num * den_);
            Variable new_den = den_ * value;
            return Rational(new_num, new_den);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator- : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to multiply
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational operator*(_Tp value)
    {
        try
        {
            Variable new_num = num_ * value;
            Variable new_den = den_ * value;
            return Rational(new_num, new_den);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator* : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational operator/(_Tp value)
    {
        try
        {
            Variable new_num = num_ * value;
            Variable new_den = den_ * value;
            return Rational(new_num, new_den);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator/ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational operator%(_Tp value)
    {
        try
        {
            Variable new_num = num_ * value;
            Variable new_den = den_ * value;
            return Rational(new_num, new_den);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator% : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to add
    /// @return The value of the object
    Rational &operator+=(const Rational &other)
    {
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * other.den_;
        auto this_num = num_ * other.den_;
        auto other_num = other.num_ * den_;

        // Perform the addition
        auto result_num = this_num + other_num;

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

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to substract
    /// @return The value of the object
    Rational &operator-=(const Rational &other)
    {
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * other.den_;
        auto this_num = num_ * other.den_;
        auto other_num = other.num_ * den_;

        // Perform the subtraction
        auto result_num = this_num - other_num;

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

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to multiply
    /// @return The value of the object
    Rational &operator*=(const Rational &other)
    {
    try
    {
        // Perform the multiplication
        auto result_num = num_ * other.num_;
        auto result_den = den_ * other.den_;

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

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to divide
    /// @return The value of the object
    Rational &operator/=(const Rational &other)
    {
        try
    {
        if (other.num_ == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Perform the division
        auto result_num = num_ * other.den_;
        auto result_den = den_ * other.num_;

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

    /// @brief This method returns the value of the object
    /// @param other Rational<T> to divide
    /// @return The value of the object
    Rational &operator%=(const Rational &other)
    {
        try
    {
        if (other.num_ == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Perform the modulus operation
        auto result_num = num_ % (other.num_ * den_);

        // Update the current object
        num_ = result_num;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
    }
}

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to add
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational &operator+=(_Tp value)
    {
        try
        {
            // Normalize both rational numbers to a common denominator
            _Tp common_den = den_ * value;
            _Tp this_num = num_ * value;
            _Tp other_num = value * den_;

            // Perform the addition
            _Tp result_num = this_num + other_num;

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

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to substract
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational &operator-=(_Tp value)
    {
        try
        {
            // Normalize both rational numbers to a common denominator
            _Tp common_den = den_ * value;
            _Tp this_num = num_ * value;
            _Tp other_num = value * den_;

            // Perform the subtraction
            _Tp result_num = this_num - other_num;

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

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to multiply
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational &operator*=(_Tp value)
    {
        try
        {
            // Perform the multiplication
            _Tp result_num = num_ * value;
            _Tp result_den = den_ * value;

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

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational &operator/=(_Tp value)
    {
        try
        {
            if (value.num_ == 0)
            {
                throw std::runtime_error("Division by zero");
            }

            // Perform the division
            _Tp result_num = num_ * value;
            _Tp result_den = den_ * value;

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

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to divide
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational &operator%=(_Tp value)
    {
        try
        {
            if (value == 0)
            {
                throw std::runtime_error("Modulus by zero");
            }

            // Perform the modulus operation
            _Tp result_num = num_ % (value * den_);

            // Update the current object
            num_ = result_num;

            return *this;
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @return  The value of the object
    Rational &operator++()
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

    /// @brief This method returns the value of the object
    /// @return The value of the object
    Rational &operator--()
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

    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Rational operator++(int)
    {
    try
    {
        // Create a copy of the current object
        Rational temp = *this;
        // Increment the numerator by the denominator
        num_ += den_;
        return temp;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator++(int) : " + std::string(e.what()));
    }
}


    /// @brief This method returns the value of the object
    /// @param  this the value of the object
    /// @return The value of the object
    Rational operator--(int)
    {
    try
    {
        // Create a copy of the current object
        Rational temp = *this;
        // Decrement the numerator by the denominator
        num_ -= den_;
        return temp;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator--(int) : " + std::string(e.what()));
    }
}

/// @brief This friend method of operator << overloading
/// @param out output stream
/// @param Rational<T> the value of the object
/// @return output stream
friend std::ostream &operator<<(std::ostream &out, const Rational &var)
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
friend std::istream &operator>>(std::istream &in, Rational &var)
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
        Rational temp;
        if (!(in >> temp))
        {
            throw std::ios_base::failure("Failed to read value");
        }

        // Присваиваем значение только если чтение прошло успешно
        var = std::move(temp);

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

private:
    Variable num_;
    Variable den_;
    Type type_;

    static Type determineType(Variable num_)
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

    /// @brief Reduces the fraction to its lowest terms
    void reduce()
    {
        // Проверка деления на ноль
        if (den_.getValue<int>() == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Если числитель и знаменатель являются целыми числами
        if constexpr (std::is_integral_v<decltype(num_.getValue<int>())>)
        {
            // Нормализация отрицательного знаменателя
            if (den_.getValue<int>() < 0)
            {
                num_.set(-num_.getValue<int>());
                den_.set(-den_.getValue<int>());
            }

            // Сокращение дроби с использованием GCD
            int gcd = std::gcd(std::abs(num_.getValue<int>()), std::abs(den_.getValue<int>()));
            if (gcd > 1)
            {
                num_.set(num_.getValue<int>() / gcd);
                den_.set(den_.getValue<int>() / gcd);
            }
        }
        else if constexpr (std::is_floating_point_v<decltype(num_.getValue<double>())>)
        {
            // Нормализация для вещественных чисел
            if (std::abs(den_.getValue<double>()) < std::numeric_limits<double>::epsilon())
            {
                throw std::runtime_error("Division by zero");
            }

            double normalize = den_.getValue<double>();
            num_.set(num_.getValue<double>() / normalize);
            den_.set(1.0);
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
        size_t start = funcSigStr.find("Rationa");
        size_t end = funcSigStr.find("l", start);
        if (start != std::string::npos && end != std::string::npos)
        {
            return funcSigStr.substr(start, end - (start - 1));
        }
        return "UnknownClass";
    }
};

#endif /* RATIONAL_H */