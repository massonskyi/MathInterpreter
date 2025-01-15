// #ifndef VARIABLE_H
// #define VARIABLE_H

// #include "core.h"
// #include "abstractsimpletype.h"

// #include <stdexcept>
// #include <variant>
// #include <sstream>
// #include <cmath>  // Для std::isnan, std::isinf
// #include <limits> // Для std::numeric_limits
// #include <string>
// #include <bitset>
// #include <utility> // Для std::move

// #ifdef __GNUG__
// #include <cxxabi.h>
// #endif
// /// @brief  This class is used to create a variable with a value
// /// @tparam T type of the value
// template <AllowedTypes T>
// class Variable final : public AbstractSimpleType
// {
// public:
//     using AbstractSimpleType::AbstractSimpleType;
//     using value_type = T;
//     /// @brief Constructor without parameters
//     Variable() : AbstractSimpleType(extractClassName()), value_(static_cast<T>(0)), type_(determineType()) {};

//     /// @brief  Constructor with parameter
//     /// @details This constructor is used to create a variable with a value
//     /// @tparam T type of the value
//     /// @param value
//     explicit Variable(T value) : AbstractSimpleType(extractClassName()), value_(value), type_(determineType()) {};

//     /// @brief Copy constructor
//     /// @param other Variable to copy
//     Variable(const Variable<T> &other) noexcept : AbstractSimpleType(other), value_(other.value_), type_(other.type_) {};

//     /// @brief Move constructor
//     /// @param other Variable to move
//     Variable(Variable<T> &&other) noexcept : AbstractSimpleType(std::move(other)), value_(std::move(other.value_)), type_(std::move(other.type_)) {};

//     /// @brief Destructor
//     /// @details Destructor of the class variable
//     ~Variable() = default;

//     /// @brief This method returns the value of the object as a string hex
//     /// @return The value of the object as a string hex
//     inline std::string hex() const override;

//     /// @brief This method returns the value of the object as a string dec
//     /// @return The value of the object as a string dec
//     inline std::string dec() const override;

//     /// @brief This method returns the value of the object as a string bin
//     /// @return The value of the object as a string bin
//     inline std::string bin() const override;

//     /// @brief This method returns the value of the object as a string oct
//     /// @return The value of the object as a string oct
//     inline std::string oct() const override;

//     /// @brief  This method is used to print the object
//     /// @return The string representation of the object
//     inline std::string toString() const override;

//     /// @brief  This method is used to get the type of the object
//     /// @return The type of the object
//     inline std::string getTypeName() const override;

//     /// @brief  This method returns the type of the object
//     /// @return The type of the object
//     inline Type getType() const;
//     /// @brief This method returns the value of the object as a boolean
//     /// @return The value of the object as a boolean
//     inline bool equals(const AbstractSimpleType &other) const override;

//     /// @brief  This method clones the object value of the object
//     /// @return The cloned object
//     inline std::unique_ptr<AbstractSimpleType> clone() const override;

//     /// @brief This method serializes the object value of the object
//     /// @return The serialized object
//     [[nodiscard]]
//     inline std::string serialize() const override;

//     /// @brief  This method deserializes the object value of the object
//     /// @param value The serialized object to deserialize
//     inline void deserialize(const std::string &data) override;

//     /// @brief This method sets the value of the object
//     /// @param value The value of the object
//     inline void set(const string &value) override;

//     /// @brief This method sets the value of the object
//     /// @param value The value of the object
//     inline void set(T value);

//     /// @brief This method returns the value of the object
//     /// @return The value of the object
//     inline T getValue() const;

//     /// @brief This method returns the value of the object
//     /// @return The value of the object
//     inline AbstractSimpleType get() const override;

//     /// @brief This method returns the value of the object
//     /// @param other Variable to copy compare
//     /// @return The value of the object
//     Variable<T> &operator=(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to move compare
//     /// @return The value of the object
//     Variable<T> &operator=(Variable<T> &&other) noexcept;

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to copy compare
//     /// @return The value of the object
//     Variable<T> &operator=(T value);
//     /// @brief  This method returns the value of the object
//     /// @param value Variable<T> to copy compare
//     /// @return The value of the object
//     Variable<T> &operator=(const T &value);

//     /// @brief This method returns the value of the object as a boolean
//     /// @param other Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator==(const Variable<T> &other) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param value Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator==(T value) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param value Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator==(const T &value) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param other Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator!=(const Variable<T> &other) const;

//     /// @brief This method returns the value of the object as a boolean
//     /// @param value Variable<T> to compare
//     /// @return The value of the object as a boolean
//     bool operator!=(T value) const;

//     /// @brief This method returns result of the add operation
//     /// @param other Variable<T> to add
//     /// @return Result of the add operation
//     Variable<T> operator+(const Variable<T> &other);

//     /// @brief This method returns result of the sub operation
//     /// @param other Variable<T> to substract
//     /// @return Result of the sub operation
//     Variable<T> operator-(const Variable<T> &other);

//     /// @brief This method returns result of the mul operation
//     /// @param other Variable<T> to multiply
//     /// @return Result of the mul operation
//     Variable<T> operator*(const Variable<T> &other);

//     /// @brief This method returns result of the div operation
//     /// @param other Variable<T> to divide
//     /// @return Result of the div operation
//     Variable<T> operator/(const Variable<T> &other);

//     /// @brief This method returns result of the mod operation
//     /// @param other Variable<T> to divide
//     /// @return Result of the mod operation
//     Variable<T> operator%(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to add
//     /// @return The value of the object
//     Variable<T> operator+(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to substract
//     /// @return The value of the object
//     Variable<T> operator-(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to multiply
//     /// @return The value of the object
//     Variable<T> operator*(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Variable<T> operator/(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Variable<T> operator%(T value);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to add
//     /// @return The value of the object
//     Variable<T> &operator+=(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to substract
//     /// @return The value of the object
//     Variable<T> &operator-=(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to multiply
//     /// @return The value of the object
//     Variable<T> &operator*=(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to divide
//     /// @return The value of the object
//     Variable<T> &operator/=(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param other Variable<T> to divide
//     /// @return The value of the object
//     Variable<T> &operator%=(const Variable<T> &other);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to add
//     /// @return The value of the object
//     Variable<T> &operator+=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to substract
//     /// @return The value of the object
//     Variable<T> &operator-=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to multiply
//     /// @return The value of the object
//     Variable<T> &operator*=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Variable<T> &operator/=(T value);

//     /// @brief This method returns the value of the object
//     /// @param value Variable<T> to divide
//     /// @return The value of the object
//     Variable<T> &operator%=(T value);

//     /// @brief This method returns the value of the object
//     /// @return  The value of the object
//     Variable<T> &operator++();

//     /// @brief This method returns the value of the object
//     /// @return The value of the object
//     Variable<T> &operator--();

//     /// @brief This method returns the value of the object
//     /// @param  this the value of the object
//     /// @return The value of the object
//     Variable<T> operator++(int);

//     /// @brief This method returns the value of the object
//     /// @param  this the value of the object
//     /// @return The value of the object
//     Variable<T> operator--(int);

//     /// @brief This friend method of operator << overloading
//     /// @param out output stream
//     /// @param Variable<T> the value of the object
//     /// @return output stream
//     friend std::ostream &operator<<(std::ostream &out, const Variable<T> &var)
//     {
//         try
//         {
//             if (!out)
//             {
//                 return out; // Return the bad stream instead of throwing
//             }

//             out << var.toString();

//             return out;
//         }
//         catch (const std::ios_base::failure &e)
//         {
//             throw std::runtime_error("I/O error in operator<<: " + std::string(e.what()));
//         }
//         catch (const std::exception &e)
//         {
//             out.setstate(std::ios::failbit);
//             throw std::runtime_error("Unexpected error in operator<<: " + std::string(e.what()));
//         }
//         catch (...)
//         {
//             out.setstate(std::ios::failbit);
//             throw std::runtime_error("Unknown error in operator<<");
//         }
//     }

//     /// @brief This friend method of operator >> overloading
//     /// @param in input stream
//     /// @param Variable<T> the value of the object
//     /// @return input stream
//     friend std::istream &operator>>(std::istream &in, Variable<T> &var)
//     {
//         try
//         {
//             // Проверка состояния потока перед операцией
//             if (!in)
//             {
//                 throw std::ios_base::failure("Input stream is in bad state");
//             }

//             // Очищаем возможные ошибки потока
//             in.clear();

//             // Пропускаем начальные пробелы
//             in >> std::ws;

//             // Создаем временную переменную для безопасного чтения
//             T temp;
//             if (!(in >> temp))
//             {
//                 throw std::ios_base::failure("Failed to read value");
//             }

//             // Присваиваем значение только если чтение прошло успешно
//             var.value_ = std::move(temp);

//             return in;
//         }
//         catch (const std::ios_base::failure &e)
//         {
//             throw std::runtime_error("I/O error in operator>>: " + std::string(e.what()));
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Unexpected error in operator>>: " + std::string(e.what()));
//         }
//     };

//     /// @brief This friend method of operator == overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return true if the values are equal, false otherwise
//     friend bool operator==(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return value == var.value_;
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator==: " + std::string(e.what()));
//         }
//     };
//     /// @brief This friend method of operator != overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return true if the values are not equal, false otherwise
//     friend bool operator!=(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return value != var.value_;
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator!=: " + std::string(e.what()));
//         }
//     }
//     /// @brief This friend method of operator + overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return the value of the object
//     friend Variable<T> operator+(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return Variable<T>(value + var.value_);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator+: " + std::string(e.what()));
//         }
//     };

//     /// @brief This friend method of operator - overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return the value of the object
//     friend Variable<T> operator-(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return Variable<T>(value - var.value_);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator-: " + std::string(e.what()));
//         }
//     };

//     /// @brief This friend method of operator * overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return the value of the object
//     friend Variable<T> operator*(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return Variable<T>(value * var.value_);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator*: " + std::string(e.what()));
//         }
//     };

//     /// @brief This friend method of operator / overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return the value of the object
//     friend Variable<T> operator/(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return Variable<T>(value / var.value_);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator/: " + std::string(e.what()));
//         }
//     }
//     /// @brief This friend method of operator % overloading
//     /// @param value the value of the object
//     /// @param var the value of the object
//     /// @return the value of the object
//     friend Variable<T> operator%(const T value, const Variable<T> &var)
//     {
//         try
//         {
//             return Variable<T>(value % var.value_);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in operator%: " + std::string(e.what()));
//         }
//     }

// protected:
//     /// @brief This method returns type of the value
//     /// @return type of the value
//     static constexpr Type determineType()
//     {
//         try
//         {
//             if constexpr (std::is_same_v<T, int>)
//             {
//                 return Type::INT;
//             }
//             else if constexpr (std::is_same_v<T, double>)
//             {
//                 return Type::DOUBLE;
//             }
//             else if constexpr (std::is_same_v<T, float>)
//             {
//                 return Type::FLOAT;
//             }
//             else
//             {
//                 throw std::runtime_error("Unsupported type");
//             }
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in determineType: " + std::string(e.what()));
//         }
//     };

//     /// @brief This method is used for safe operations
//     /// @param a the value of the object
//     /// @param b the value of the object
//     /// @return the value of the object
//     static T safeAdd(const std::variant<T> &a, const std::variant<T> &b)
//     {
//         try
//         {
//             return std::visit([](auto &&arg1, auto &&arg2) -> T
//                               { return static_cast<T>(arg1 + arg2); }, a, b);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in safeAdd: " + std::string(e.what()));
//         }
//     }

//     /// @brief This method is used for safe operations
//     /// @param a the value of the object
//     /// @param b the value of the object
//     /// @return the value of the object
//     static T safeSubtract(std::variant<T> a, std::variant<T> b)
//     {
//         try
//         {
//             return std::visit([](auto &&arg1, auto &&arg2)
//                               {
//             using U = std::decay_t<decltype(arg1)>;
//             return arg1 - arg2; }, a, b);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in safeSubtract: " + std::string(e.what()));
//         }
//     };

//     /// @brief This method is used for safe operations
//     /// @param a the value of the object
//     /// @param b the value of the object
//     /// @return the value of the object
//     static T safeMultiply(std::variant<T> a, std::variant<T> b)
//     {
//         try
//         {
//             return std::visit([](auto &&arg1, auto &&arg2)
//                               {
//             using U = std::decay_t<decltype(arg1)>;
//             return arg1 * arg2; }, a, b);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in safeMultiply: " + std::string(e.what()));
//         }
//     };

//     /// @brief This method is used for safe operations
//     /// @param a the value of the object
//     /// @param b the value of the object
//     /// @return the value of the object
//     static T safeDivide(std::variant<T> a, std::variant<T> b)
//     {
//         try
//         {
//             return std::visit([](auto &&arg1, auto &&arg2)
//                               {
//             using U = std::decay_t<decltype(arg1)>;
//             if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long> || std::is_same_v<T, long long>) {
//                 if (arg2 == 0) {
//                     throw std::runtime_error("Division by zero");
//                 }
//                 return arg1 / arg2;
//             } else {
//                 throw std::runtime_error("Unsupported type for division operation");
//             } }, a, b);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in safeDivide: " + std::string(e.what()));
//         }
//     };

//     /// @brief This method is used for safe operations
//     /// @param a the value of the object
//     /// @param b the value of the object
//     /// @return the value of the object
//     static T safeModulo(std::variant<T> a, std::variant<T> b)
//     {
//         try
//         {
//             return std::visit([](auto &&arg1, auto &&arg2)
//                               {
//             using U = std::decay_t<decltype(arg1)>;
//             if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long> || std::is_same_v<T, long long>) {
//                 if (arg2 == 0) {
//                     throw std::runtime_error("Division by zero");
//                 }
//                 return arg1 % arg2;
//             } else {
//                 throw std::runtime_error("Unsupported type for modulo operation");
//             } }, a, b);
//         }
//         catch (const std::exception &e)
//         {
//             throw std::runtime_error("Error in safeModulo: " + std::string(e.what()));
//         }
//     };

//     /// @brief This method is checked for division by zero
//     /// @param value the value of the object
//     /// @return true if division by zero false otherwise
//     static bool isDivisionByZero(const std::variant<T> &value);

//     /// @brief This method checked for type compatibility for operation
//     /// @param other the value of the object
//     /// @return true if type compatibility false otherwise
//     bool areTypesCompatibleForOperation(const Variable<T> &other) const;

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
//         size_t start = funcSigStr.find("Variable<");
//         size_t end = funcSigStr.find(">::", start);
//         if (start != std::string::npos && end != std::string::npos)
//         {
//             return funcSigStr.substr(start, end - (start - 1));
//         }
//         return "UnknownClass";
//     }
//     std::variant<T> value_; // the value of the object
//     Type type_;             // the type of the object
// };

// template <AllowedTypes T>
// inline std::string Variable<T>::hex() const
// {
//     try
//     {
//         std::ostringstream stream;
//         switch (type_)
//         {
//         case Type::INT:
//             stream << "0x" << std::uppercase << std::hex
//                    << std::get<int>(value_);
//             break;
//         case Type::FLOAT:
//         case Type::DOUBLE:
//             stream << std::hexfloat << std::get<T>(value_);
//             break;
//         default:
//             throw std::invalid_argument("Unsupported numeric type");
//         }
//         return stream.str();
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error converting value to hexadecimal string: " +
//                                  std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline std::string Variable<T>::dec() const
// {
//     try
//     {
//         std::ostringstream stream;
//         switch (type_)
//         {
//         case Type::INT:
//             return std::to_string(std::get<int>(value_));

//         case Type::FLOAT:
//         case Type::DOUBLE:
//             stream << std::fixed;
//             if constexpr (std::is_same_v<T, float>)
//             {
//                 stream << std::get<float>(value_);
//             }
//             else if constexpr (std::is_same_v<T, double>)
//             {
//                 stream << std::get<double>(value_);
//             }
//             return stream.str();

//         default:
//             throw std::invalid_argument("Unsupported numeric type");
//         }
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error converting value to decimal string: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline std::string Variable<T>::bin() const
// {
//     try
//     {
//         if (type_ != Type::INT)
//         {
//             throw std::invalid_argument("Binary representation supported only for integer types");
//         }

//         constexpr size_t BITS = sizeof(T) * 8;
//         return std::bitset<BITS>(std::get<T>(value_)).to_string();
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error converting value to binary string: " +
//                                  std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline std::string Variable<T>::oct() const
// {
//     try
//     {
//         if (type_ != Type::INT)
//         {
//             throw std::invalid_argument("Octal representation supported only for integer types");
//         }

//         std::ostringstream stream;
//         stream << '0' << std::oct << std::get<T>(value_);
//         return stream.str();
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error converting value to octal string: " +
//                                  std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline std::string Variable<T>::toString() const
// {
//     try
//     {
//         if (value_.valueless_by_exception())
//         {
//             return "Error: variant is empty";
//         }

//         std::stringstream ss;
//         // Попробуем получить конкретное значение типа T
//         if (auto val = std::get_if<T>(&value_))
//         {
//             ss << *val;
//             return ss.str();
//         }

//         return "Error: incorrect type";
//     }
//     catch (const std::exception &e)
//     {
//         return "Error: " + std::string(e.what());
//     }
// }

// template <AllowedTypes T>
// inline std::string Variable<T>::getTypeName() const
// {
//     return std::visit([](const auto &arg) -> std::string
//                       {
//         using U = std::remove_cvref_t<decltype(arg)>;
//             std::string type_name = typeid(U).name();
// #ifdef __GNUG__
//             int status;
//             char* demangled = abi::__cxa_demangle(type_name.c_str(), nullptr, nullptr, &status);
//             if (demangled) {
//                 type_name = demangled;
//                 free(demangled);
//             }
// #else
//             // Получаем имя типа
//             std::string type_name = typeid(U).name();
            
//             // Удаляем "class " и "struct " из начала имени (специфично для MSVC)
//             if (type_name.substr(0, 6) == "class ") {
//                 type_name = type_name.substr(6);
//             }
//             if (type_name.substr(0, 7) == "struct ") {
//                 type_name = type_name.substr(7);
//             }
// #endif
//             return type_name; }, value_);
// }
// template <AllowedTypes T>
// inline Type Variable<T>::getType() const
// {
//     return type_;
// }
// template <AllowedTypes T>
// inline bool Variable<T>::equals(const AbstractSimpleType &other) const
// {
//     const Variable<T> *otherVariable = dynamic_cast<const Variable<T> *>(&other);
//     if (otherVariable)
//     {
//         return value_ == otherVariable->value_;
//     }
//     return false;
// }

// template <AllowedTypes T>
// inline std::unique_ptr<AbstractSimpleType> Variable<T>::clone() const
// {
//     return std::make_unique<Variable<T>>(*this);
// }

// template <AllowedTypes T>
// inline std::string Variable<T>::serialize() const
// {
//     return std::visit([](auto &&arg) -> std::string
//                       {
//         using U = std::decay_t<decltype(arg)>;
//         if constexpr (std::is_same_v<U, std::string>) {
//             return arg;
//         } else {
//             return std::to_string(arg);
//         } }, value_);
// }

// template <AllowedTypes T>
// inline void Variable<T>::deserialize(const std::string &data)
// {
//     value_ = std::visit([&](auto &&arg) -> T
//                         {
//         using U = std::decay_t<decltype(arg)>;
//         if constexpr (std::is_same_v<U, std::string>) {
//             return data;
//         } else {
//             return std::stoi(data);
//         } }, value_);
// }

// template <AllowedTypes T>
// inline void Variable<T>::set(const std::string &value)
// {
//     try
//     {
//         if constexpr (std::is_same_v<T, std::string>)
//         {
//             value_ = value;
//         }
//         else
//         {
//             value_ = static_cast<T>(std::stod(value)); // Предполагаем, что T - это числовой тип
//         }
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error setting value: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline void Variable<T>::set(T value)
// {
//     try
//     {
//         value_ = value;
//         type_ = determineType();
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error setting value: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline T Variable<T>::getValue() const
// {
//     return std::get<T>(value_);
// }

// template <AllowedTypes T>
// AbstractSimpleType Variable<T>::get() const
// {
//     try
//     {
//         return Variable(*this);
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error getting value: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline Variable<T> &Variable<T>::operator=(const Variable<T> &other)
// {
//     try
//     {
//         value_ = other.value_;
//         type_ = other.type_;
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error assigning value: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline Variable<T> &Variable<T>::operator=(Variable<T> &&other) noexcept
// {
//     try
//     {
//         value_ = std::move(other.value_);
//         type_ = other.type_;
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error assigning value: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline Variable<T> &Variable<T>::operator=(T value)
// {
//     try
//     {
//         value_ = value;
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error assigning value: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline Variable<T> &Variable<T>::operator=(const T &value)
// {
//     try
//     {
//         value_ = value;
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error assigning value: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline bool Variable<T>::operator==(const Variable<T> &other) const
// {
//     try
//     {
//         return value_ == other.value_ && type_ == other.type_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error comparing values: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline bool Variable<T>::operator==(T value) const
// {
//     try
//     {
//         return value_ == value && type_ == type_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error comparing values: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline bool Variable<T>::operator==(const T &value) const
// {
//     try
//     {
//         return value_ == value && type_ == type_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error comparing values: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline bool Variable<T>::operator!=(const Variable<T> &other) const
// {
//     try
//     {
//         return value_ != other.value_ || type_ != other.type_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error comparing values: " + std::string(e.what()));
//     }
// }
// template <AllowedTypes T>
// inline bool Variable<T>::operator!=(T value) const
// {
//     try
//     {
//         return value_ != value || type_ != type_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error comparing values: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// inline Variable<T> Variable<T>::operator+(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for addition");
//         }
//         return Variable<T>(safeAdd(value_, other.value_));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in addition: " + std::string(e.what()));
//     }
// }
// // Операторы для работы с другим объектом Variable
// template <AllowedTypes T>
// Variable<T> Variable<T>::operator-(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for subtraction");
//         }
//         return Variable<T>(safeSubtract(value_, other.value_));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in subtraction: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator*(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for multiplication");
//         }
//         return Variable<T>(safeMultiply(value_, other.value_));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in multiplication: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator/(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for division");
//         }
//         if (isDivisionByZero(other.value_))
//         {
//             throw std::runtime_error("Division by zero");
//         }
//         return Variable<T>(safeDivide(value_, other.value_));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in division: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator%(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for modulo");
//         }
//         if (isDivisionByZero(other.value_))
//         {
//             throw std::runtime_error("Modulo by zero");
//         }
//         return Variable<T>(safeModulo(value_, other.value_));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in modulo: " + std::string(e.what()));
//     }
// }

// // Операторы для работы со значением типа T (по значению)
// template <AllowedTypes T>
// Variable<T> Variable<T>::operator+(T value)
// {
//     try
//     {
//         return Variable<T>(safeAdd(value_, std::variant<T>(value)));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in addition: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator-(T value)
// {
//     try
//     {
//         return Variable<T>(safeSubtract(value_, std::variant<T>(value)));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in subtraction: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator*(T value)
// {
//     try
//     {
//         return Variable<T>(safeMultiply(value_, std::variant<T>(value)));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in multiplication: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator/(T value)
// {
//     try
//     {
//         if (value == T{})
//         {
//             throw std::runtime_error("Division by zero");
//         }
//         return Variable<T>(safeDivide(value_, std::variant<T>(value)));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in division: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator%(T value)
// {
//     try
//     {
//         if (value == T{})
//         {
//             throw std::runtime_error("Modulo by zero");
//         }
//         return Variable<T>(safeModulo(value_, std::variant<T>(value)));
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in modulo: " + std::string(e.what()));
//     }
// }

// // Операторы составного присваивания для Variable
// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator+=(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for addition assignment");
//         }
//         value_ = safeAdd(value_, other.value_);
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in addition assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator-=(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for subtraction assignment");
//         }
//         value_ = safeSubtract(value_, other.value_);
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in subtraction assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator*=(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for multiplication assignment");
//         }
//         value_ = safeMultiply(value_, other.value_);
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in multiplication assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator/=(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for division assignment");
//         }
//         if (isDivisionByZero(other.value_))
//         {
//             throw std::runtime_error("Division by zero in assignment");
//         }
//         value_ = safeDivide(value_, other.value_);
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in division assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator%=(const Variable<T> &other)
// {
//     try
//     {
//         if (!areTypesCompatibleForOperation(other))
//         {
//             throw std::runtime_error("Incompatible types for modulo assignment");
//         }
//         if (isDivisionByZero(other.value_))
//         {
//             throw std::runtime_error("Modulo by zero in assignment");
//         }
//         value_ = safeModulo(value_, other.value_);
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in modulo assignment: " + std::string(e.what()));
//     }
// }

// // Операторы составного присваивания для T по значению
// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator+=(T value)
// {
//     try
//     {
//         value_ = safeAdd(value_, std::variant<T>(value));
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in addition assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator-=(T value)
// {
//     try
//     {
//         value_ = safeSubtract(value_, std::variant<T>(value));
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in subtraction assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator*=(T value)
// {
//     try
//     {
//         value_ = safeMultiply(value_, std::variant<T>(value));
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in multiplication assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator/=(T value)
// {
//     try
//     {
//         if (value == T{})
//         {
//             throw std::runtime_error("Division by zero in assignment");
//         }
//         value_ = safeDivide(value_, std::variant<T>(value));
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in division assignment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator%=(T value)
// {
//     try
//     {
//         if (value == T{})
//         {
//             throw std::runtime_error("Modulo by zero in assignment");
//         }
//         value_ = safeModulo(value_, std::variant<T>(value));
//         return *this;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in modulo assignment: " + std::string(e.what()));
//     }
// }

// // Операторы составного присваивания для константной ссылки на T

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator++()
// {
//     try
//     {
//         // Проверяем, поддерживает ли тип операцию инкремента
//         if constexpr (std::is_arithmetic_v<T> || requires(T x) { ++x; })
//         {
//             ++value_;
//             return *this;
//         }
//         else
//         {
//             throw std::runtime_error("Type does not support increment operation");
//         }
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in prefix increment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> &Variable<T>::operator--()
// {
//     try
//     {
//         // Проверяем, поддерживает ли тип операцию декремента
//         if constexpr (std::is_arithmetic_v<T> || requires(T x) { --x; })
//         {
//             --value_;
//             return *this;
//         }
//         else
//         {
//             throw std::runtime_error("Type does not support decrement operation");
//         }
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in prefix decrement: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator++(int)
// {
//     try
//     {
//         // Проверяем, поддерживает ли тип операцию инкремента
//         if constexpr (std::is_arithmetic_v<T> || requires(T x) { x++; })
//         {
//             Variable<T> temp(*this); // Создаем копию текущего объекта
//             ++(*this);               // Используем префиксный оператор
//             return temp;             // Возвращаем старое значение
//         }
//         else
//         {
//             throw std::runtime_error("Type does not support increment operation");
//         }
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in postfix increment: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// Variable<T> Variable<T>::operator--(int)
// {
//     try
//     {
//         // Проверяем, поддерживает ли тип операцию декремента
//         if constexpr (std::is_arithmetic_v<T> || requires(T x) { x--; })
//         {
//             Variable<T> temp(*this); // Создаем копию текущего объекта
//             --(*this);               // Используем префиксный оператор
//             return temp;             // Возвращаем старое значение
//         }
//         else
//         {
//             throw std::runtime_error("Type does not support decrement operation");
//         }
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in postfix decrement: " + std::string(e.what()));
//     }
// }

// template <AllowedTypes T>
// bool operator==(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return value == var.value_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator==: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// bool operator!=(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return value != var.value_;
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator!=: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// Variable<T> operator+(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return Variable<T>(value + var.value_);
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator+: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// Variable<T> operator-(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return Variable<T>(value - var.value_);
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator-: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// Variable<T> operator*(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return Variable<T>(value * var.value_);
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator*: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// Variable<T> operator/(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return Variable<T>(value / var.value_);
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator/: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// Variable<T> operator%(const T value, const Variable<T> &var)
// {
//     try
//     {
//         return Variable<T>(value % var.value_);
//     }
//     catch (const std::exception &e)
//     {
//         throw std::runtime_error("Error in operator%: " + std::string(e.what()));
//     }
// };

// template <AllowedTypes T>
// bool Variable<T>::isDivisionByZero(const std::variant<T> &value)
// {
//     if (std::holds_alternative<T>(value))
//     {
//         return std::get<T>(value) == 0;
//     }
//     throw std::runtime_error("Division by zero: Invalid type in variant");
// }

// template <AllowedTypes T>
// bool Variable<T>::areTypesCompatibleForOperation(const Variable<T> &other) const
// {
//     if (type_ != other.type_)
//     {
//         throw std::runtime_error("Incompatible types");
//     }
//     return true;
// }
// #endif /*VARIABLE_H */
#ifndef VARIABLE_H
#define VARIABLE_H

#include "core.h"
#include "abstractsimpletype.h"

#include <stdexcept>
#include <variant>
#include <sstream>
#include <cmath>
#include <limits>
#include <string>
#include <bitset>
#include <utility>

class Variable final : public AbstractSimpleType {
public:
    using value_type = std::variant<int, float, double>;
    
    // Constructors
    Variable() : AbstractSimpleType("Variable"), value_(0), type_(Type::INT) {}
    
    Variable(int value) : AbstractSimpleType("Variable"), value_(value), type_(Type::INT) {}
    Variable(float value) : AbstractSimpleType("Variable"), value_(value), type_(Type::FLOAT) {}
    Variable(double value) : AbstractSimpleType("Variable"), value_(value), type_(Type::DOUBLE) {}
    
    // Copy constructor
    Variable(const Variable& other) noexcept 
        : AbstractSimpleType(other), value_(other.value_), type_(other.type_) {}
    
    // Move constructor
    Variable(Variable&& other) noexcept 
        : AbstractSimpleType(std::move(other)), 
          value_(std::move(other.value_)), 
          type_(std::move(other.type_)) {}
    
    ~Variable() = default;

    // String representation methods
    std::string hex() const override {
        try {
            std::ostringstream stream;
            std::visit([&stream](const auto& val) {
                if constexpr (std::is_integral_v<std::decay_t<decltype(val)>>) {
                    stream << "0x" << std::uppercase << std::hex << val;
                } else {
                    stream << std::hexfloat << val;
                }
            }, value_);
            return stream.str();
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error converting to hex: " + std::string(e.what()));
        }
    }

    std::string dec() const override {
        try {
            std::ostringstream stream;
            std::visit([&stream](const auto& val) {
                stream << val;
            }, value_);
            return stream.str();
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error converting to decimal: " + std::string(e.what()));
        }
    }

    std::string bin() const override {
        try {
            if (type_ != Type::INT) {
                throw std::invalid_argument("Binary representation only supported for integers");
            }
            return std::bitset<32>(std::get<int>(value_)).to_string();
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error converting to binary: " + std::string(e.what()));
        }
    }

    std::string oct() const override {
        try {
            if (type_ != Type::INT) {
                throw std::invalid_argument("Octal representation only supported for integers");
            }
            std::ostringstream stream;
            stream << '0' << std::oct << std::get<int>(value_);
            return stream.str();
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error converting to octal: " + std::string(e.what()));
        }
    }

    std::string toString() const override {
        try {
            std::stringstream ss;
            std::visit([&ss](const auto& val) { ss << val; }, value_);
            return ss.str();
        }
        catch (const std::exception& e) {
            return "Error: " + std::string(e.what());
        }
    }

    // Type information
    std::string getTypeName() const override {
        return std::visit([](const auto& val) {
            return std::string(typeid(val).name());
        }, value_);
    }

    Type getType() const {
        return type_;
    }

    // Comparison
    bool equals(const AbstractSimpleType& other) const override {
        const Variable* otherVar = dynamic_cast<const Variable*>(&other);
        return otherVar && value_ == otherVar->value_;
    }

    // Clone
    std::unique_ptr<AbstractSimpleType> clone() const override {
        return std::make_unique<Variable>(*this);
    }

    // Serialization
    std::string serialize() const override {
        return toString();
    }

    void deserialize(const std::string& data) override {
        try {
            switch (type_) {
                case Type::INT:
                    value_ = std::stoi(data);
                    break;
                case Type::FLOAT:
                    value_ = std::stof(data);
                    break;
                case Type::DOUBLE:
                    value_ = std::stod(data);
                    break;
                default:
                    throw std::runtime_error("Unsupported type for deserialization");
            }
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Error in deserialization: " + std::string(e.what()));
        }
    }

    // Value setters and getters
    void set(const std::string& value) override {
        deserialize(value);
    }

    template<typename T>
    void set(T value) {
        value_ = value;
        type_ = determineType(value);
    }

    template<typename T>
    T getValue() const {
        return std::get<T>(value_);
    }

    AbstractSimpleType get() const override {
        return *this;
    }

    // Operators
    Variable& operator=(const Variable& other) {
        if (this != &other) {
            value_ = other.value_;
            type_ = other.type_;
        }
        return *this;
    }

    Variable& operator=(Variable&& other) noexcept {
        if (this != &other) {
            value_ = std::move(other.value_);
            type_ = other.type_;
        }
        return *this;
    }

    // Basic arithmetic operators
    Variable operator+(const Variable& other) const {
        return binaryOperation(other, std::plus<>());
    }

    Variable operator-(const Variable& other) const {
        return binaryOperation(other, std::minus<>());
    }

    Variable operator*(const Variable& other) const {
        return binaryOperation(other, std::multiplies<>());
    }

    Variable operator/(const Variable& other) const {
        if (isZero(other.value_)) {
            throw std::runtime_error("Division by zero");
        }
        return binaryOperation(other, std::divides<>());
    }

private:
    value_type value_;
    Type type_;

    static Type determineType(const value_type& val) {
        if (std::holds_alternative<int>(val)) return Type::INT;
        if (std::holds_alternative<float>(val)) return Type::FLOAT;
        if (std::holds_alternative<double>(val)) return Type::DOUBLE;
        throw std::runtime_error("Unknown type");
    }

    template<typename Op>
    Variable binaryOperation(const Variable& other, Op operation) const {
        return std::visit([&](const auto& a, const auto& b) {
            using ResultType = decltype(operation(a, b));
            return Variable(static_cast<ResultType>(operation(a, b)));
        }, value_, other.value_);
    }

    static bool isZero(const value_type& val) {
        return std::visit([](const auto& v) { return v == 0; }, val);
    }
};

#endif // VARIABLE_H