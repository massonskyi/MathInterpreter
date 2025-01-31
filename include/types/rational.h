#ifndef RATIONAL_H
#define RATIONAL_H

#include "variable.h"
#include <numeric>
#include <utility>

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
    explicit Rational(Variable num, Variable den) : AbstractObject(extractClassName()), num_(std::move(num)), den_(std::move(den)), type_(determineType(num_))
    {
    }

    /// @brief Constructor with numerator and default denominator
    /// @param num numerator
    explicit Rational(Variable num) : AbstractObject(extractClassName()), num_(std::move(num)), den_(1), type_(determineType(num_)) {};

    /// @brief Copy constructor
    /// @param other object to copy
    Rational(const Rational &other)
        : AbstractObject(extractClassName()), num_(other.num_), den_(other.den_), type_(other.type_) {};

    /// @brief Move constructor
    /// @param other object to move
    Rational(Rational &&other) noexcept
        : AbstractObject(extractClassName()), num_(std::move(other.num_)), den_(std::move(other.den_)), type_(other.type_) {};

    /// @brief Destructor
    ~Rational() override = default;
    // Виртуальный метод для вывода
    void print(std::ostream &os) const override
    {
        std::cout << *this << std::endl;
    }
    /// @brief This method returns object by index its index container
    /// @return object by index
     [[nodiscard]] AbstractObject get() const override
    {
        throw std::runtime_error("Not implemented");
    }
    [[nodiscard]] Variable getNum() const
    {
        return num_;
    }
    [[nodiscard]] Variable getDen() const
    {
        return den_;
    }
    /// @brief  This method is used to print the object
    /// @return The string representation of the object
     [[nodiscard]] std::string toString() const override
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
     [[nodiscard]] std::string getTypeName() const override
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
        return *this;
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
            const Variable this_num = num_ * other.den_;
            const Variable other_num = other.num_ * den_;

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
    bool operator!=(const _Tp &other) const {
        try {
            return !(*this == other);
        } catch (const std::exception &e) {
            throw std::runtime_error("Error in operator!= : " + std::string(e.what()));
        }
    }

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator+(const Rational &other)
    {
        try
        {
            return Rational((num_ * other.den_) + (other.num_ * den_), den_ * other.den_);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator+(const Rational &other)const
    {
        try
        {
            return Rational((num_ * other.den_) + (other.num_ * den_), den_ * other.den_);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator+(const Variable& other)
    {
        try
        {
            return Rational((num_ * other) + (other * den_), den_ * other);
        }
        catch (const std::exception& e)
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
            return Rational((num_ * other.den_) - (other.num_ * den_), den_ * other.den_);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator-(const Variable& other)
    {
        try
        {
            return Rational((num_ * other) - (other * den_), den_ * other);
        }
        catch (const std::exception& e)
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
            return Rational(num_ * other.num_, den_ * other.den_);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator* : " + std::string(e.what()));
        }
    }
    /// @brief This method returns result of the mul operation
    /// @param other Rational<T> to multiply
    /// @return Result of the mul operation
    Rational operator*(const Rational &other)const
    {
        try
        {
            return Rational(num_ * other.num_, den_ * other.den_);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator* : " + std::string(e.what()));
        }
    }
    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator*(const Variable& other)
    {
        try
        {
            return Rational((num_ * other) * (other * den_), den_ * other);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
        }
    }
    /// @brief This method returns result of the div operation
    /// @param other Rational<T> to divide
    /// @return Result of the div operation
    Rational operator/(const Rational &other)
    {
        try
        {
            return Rational(num_ * other.den_, den_ * other.num_);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in operator/ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns result of the add operation
    /// @param other Rational<T> to add
    /// @return Result of the add operation
    Rational operator/(const Variable& other)
    {
        try
        {
            return Rational((num_ * other) * (other * den_), den_ * other);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
        }
    }

    /// @brief This method returns result of the mod operation
    /// @param other Rational<T> to divide
    /// @return Result of the mod operation
    Rational operator%(const Rational &other) {
        try {
            return Rational(num_ * other.den_, den_ * other.num_);
        }catch (const std::exception &e) {
            throw std::runtime_error("Error in operator% : " + std::string(e.what()));
        }
    }

    /// @brief This method returns the value of the object
    /// @param value Rational<T> to add
    /// @return The value of the object
    template <AllowedTypes _Tp>
    Rational operator+(_Tp value)
    {
        try
        {
            // Приводим дроби к общему знаменателю
            return Rational((num_ * value) + (den_ * value), den_ * value);
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
            return Rational((num_ * value) - (value * den_), den_ * value);
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
            return Rational(num_ * value, den_ * value);
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
            return Rational(num_ * value, den_ * value);
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
            return Rational(num_ * value, den_ * value);
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
            const auto common_den = den_ * other.den_;
            auto this_num = num_ * other.den_;
            const auto other_num = other.num_ * den_;

            // Perform the addition
            const auto result_num = this_num + other_num;

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
            const auto common_den = den_ * other.den_;
            auto this_num = num_ * other.den_;
            const auto other_num = other.num_ * den_;

            // Perform the subtraction
            const auto result_num = this_num - other_num;

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
            const auto result_num = num_ * other.num_;
            const auto result_den = den_ * other.den_;

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
            const auto result_num = num_ * other.den_;
            const auto result_den = den_ * other.num_;

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
            const auto result_num = num_ % (other.num_ * den_);

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
    Rational &operator++() override
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
    Rational &operator--() override
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
    /// @param var the value of the object
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

    static Type determineType(const Variable &num)
    {
        if (const std::string &typeStr = num.getType(); typeStr == "INT")
        {
            return Type::INT;
        }
        else if (typeStr == "DOUBLE")
        {
            return Type::DOUBLE;
        }
        else if (typeStr == "FLOAT")
        {
            return Type::FLOAT;
        }
        else if (typeStr == "OTHER")
        {
            return Type::OTHER;
        }
        else
        {
            throw std::invalid_argument("Unknown type");
        }
    }
    static std::string extractClassName()
    {
#ifdef _MSC_VER
        auto funcSig = __FUNCSIG__;
#else
        auto funcSig = __PRETTY_FUNCTION__;
#endif
        // Extract the class name from the function signature string
        std::string funcSigStr(funcSig);
        const size_t start = funcSigStr.find("Rationa");
        if (const size_t end = funcSigStr.find('l', start); start != std::string::npos && end != std::string::npos)
        {
            return funcSigStr.substr(start, end - (start - 1));
        }
        return "UnknownClass";
    }
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
            if (int gcd = std::gcd(std::abs(num_.getValue<int>()), std::abs(den_.getValue<int>())); gcd > 1)
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

            auto normalize = den_.getValue<double>();
            num_.set(num_.getValue<double>() / normalize);
            den_.set(1.0);
        }
    }
};

#endif /* RATIONAL_H */