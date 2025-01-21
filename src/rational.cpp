#include "../include/types/rational.hpp"

template <>
bool Rational::operator== <int>(int value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        int common_den = den_.getValue<int>();
        int this_num = num_.getValue<int>();
        auto other_num = value * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}
template <>
bool Rational::operator== <float>(float value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        float common_den = den_.getValue<float>();
        float this_num = num_.getValue<float>();
        auto other_num = value * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}
template <>
bool Rational::operator== <double>(double value) const
{
    try
    {
        // Normalize the rational number to have a common denominator of 1
        double common_den = den_.getValue<double>();
        double this_num = num_.getValue<double>();
        auto other_num = value * den_;

        return this_num == other_num;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator== : " + std::string(e.what()));
    }
}
template <>
bool Rational::operator!= <int>(const int &other) const
{
    try
    {
        return !(*this == other);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator!= : " + std::string(e.what()));
    }
}
template <>
bool Rational::operator!= <float>(const float &other) const
{
    try
    {
        return !(*this == other);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator!= : " + std::string(e.what()));
    }
}
template <>
bool Rational::operator!= <double>(const double &other) const
{
    try
    {
        return !(*this == other);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator!= : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator+ <int>(int value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        int other_num = value;
        Variable new_num = (num_ * value) + (other_num * den_);
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator+ <float>(float value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        float other_num = value;
        Variable new_num = (num_ * value) + (other_num * den_);
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator+ <double>(double value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        double other_num = value;
        Variable new_num = (num_ * value) + (other_num * den_);
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator- <int>(int value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        int other_num = value;
        Variable new_num = (num_ * value) - (other_num * den_);
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator- <float>(float value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        float other_num = value;
        Variable new_num = (num_ * value) - (other_num * den_);
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator- <double>(double value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        double other_num = value;
        Variable new_num = (num_ * value) - (other_num * den_);
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator* <int>(int value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator* <float>(float value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator* <double>(double value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator/ <int>(int value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator/ <float>(float value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator/ <double>(double value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}
template <>
Rational Rational::operator% <int>(int value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator% <float>(float value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational Rational::operator% <double>(double value)
{
    try
    {
        // Приводим дроби к общему знаменателю
        Variable new_num = num_ * value;
        Variable new_den = den_ * value;
        return Rational(new_num, new_den);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator+ : " + std::string(e.what()));
    }
}

template <>
Rational &Rational::operator+= <int> (int value)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * value;
        auto this_num = num_ * value;
        auto other_num = value * den_;

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
template <>
Rational &Rational::operator+= <float> (float value)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * value;
        auto this_num = num_ * value;
        auto other_num = value * den_;

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

template <>
Rational &Rational::operator+= <double> (double value)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * value;
        auto this_num = num_ * value;
        auto other_num = value * den_;

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

template <>
Rational &Rational::operator-= <int> (int value)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * value;
        auto this_num = num_ * value;
        auto other_num = value * den_;

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

template <>
Rational &Rational::operator-= <float> (float value)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * value;
        auto this_num = num_ * value;
        auto other_num = value * den_;

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
template <>
Rational &Rational::operator-= <double> (double value)
{
    try
    {
        // Normalize both rational numbers to a common denominator
        auto common_den = den_ * value;
        auto this_num = num_ * value;
        auto other_num = value * den_;

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

template <>
Rational &Rational::operator*=<int> (int value)
{
    try
    {
        // Perform the multiplication
        auto result_num = num_ * value;
        auto result_den = den_ * value;

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

template <>
Rational &Rational::operator*=<float> (float value)
{
    try
    {
        // Perform the multiplication
        auto result_num = num_ * value;
        auto result_den = den_ * value;

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

template <>
Rational &Rational::operator*=<double> (double value)
{
    try
    {
        // Perform the multiplication
        auto result_num = num_ * value;
        auto result_den = den_ * value;

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

template <>
Rational &Rational::operator/= <int> (int value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Perform the division
        auto result_num = num_ * value;
        auto result_den = den_ * value;

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

template <>
Rational &Rational::operator/= <float> (float value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Perform the division
        auto result_num = num_ * value;
        auto result_den = den_ * value;

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
template <>
Rational &Rational::operator/= <double> (double value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Division by zero");
        }

        // Perform the division
        auto result_num = num_ * value;
        auto result_den = den_ * value;

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

template <>
Rational &Rational::operator %= <int> (int value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Perform the modulus operation
        auto result_num = num_ % (value * den_);

        // Update the current object
        num_ = result_num;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
    }
}
template <>
Rational &Rational::operator %= <float> (float value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Perform the modulus operation
        auto result_num = num_ % (value * den_);

        // Update the current object
        num_ = result_num;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
    }
}
template <>
Rational &Rational::operator %= <double> (double value)
{
    try
    {
        if (value == 0)
        {
            throw std::runtime_error("Modulus by zero");
        }

        // Perform the modulus operation
        auto result_num = num_ % (value * den_);

        // Update the current object
        num_ = result_num;

        return *this;
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in operator%= : " + std::string(e.what()));
    }
}
