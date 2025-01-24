#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <stdexcept>

/// @brief This strucutre is used to throw exceptions
struct Exception : public std::exception
{
    /// @brief Default constructor
    Exception() = default;
    
    /// @brief Constructor with error message
    /// @param err Error message
    explicit Exception(std::string err) : err(std::move(err)) {}

    /// @brief override std::exception::what() 
    /// @return err message
    [[nodiscard]] const char *what() const noexcept override
    {
        return err.empty() ? "Interpreter exception with err: Unknown error" : err.c_str();
    }

private:
    std::string err;
};

struct InvalidCommand final : public Exception
{
    /// @brief Default constructor
    InvalidCommand() : Exception("Invalid command") {}

    /// @brief Constructor with error message
    /// @param err error message
    explicit InvalidCommand(const std::string &err) : Exception(err) {}
};

struct UnknownVariable final : public Exception
{
    /// @brief Default constructor
    UnknownVariable() : Exception("Unknown variable") {}
    
    /// @brief Constructor with error message
    /// @param err error message
    explicit UnknownVariable(const std::string &err) : Exception(err) {}
};

struct UnknownOperator final : public Exception
{
    /// @brief Default constructor
    UnknownOperator() : Exception("Unknown operator") {}
    
    /// @brief Constructor with error message
    /// @param err error message
    explicit UnknownOperator(const std::string &err) : Exception(err) {}
};

struct UnknownFunction final : public Exception
{
    /// @brief Default constructor
    UnknownFunction() : Exception("Unknown function") {}

    /// @brief Constructor with error message
    /// @param err error message
    explicit UnknownFunction(const std::string &err) : Exception(err) {}
};

struct InvalidExpression final : public Exception
{
    /// @brief Default constructor
    InvalidExpression() : Exception("Invalid expression") {}

    /// @brief Constructor with error message
    /// @param err error message
    explicit InvalidExpression(const std::string &err) : Exception(err) {}
};
#endif /* EXCEPTIONS_HPP */