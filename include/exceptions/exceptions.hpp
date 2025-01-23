#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <stdexcept>

struct Exception : public std::exception
{
    Exception() = default;
    explicit Exception(std::string err) : err(std::move(err)) {}

    [[nodiscard]] const char *what() const noexcept override
    {
        return err.empty() ? "Interpreter exception with err: Unknown error" : err.c_str();
    }

private:
    std::string err;
};

struct InvalidCommand final : public Exception
{
    InvalidCommand() : Exception("Invalid command") {}
    explicit InvalidCommand(const std::string &err) : Exception(err) {}
};

struct UnknownVariable final : public Exception
{
    UnknownVariable() : Exception("Unknown variable") {}
    explicit UnknownVariable(const std::string &err) : Exception(err) {}
};

struct UnknownOperator final : public Exception
{
    UnknownOperator() : Exception("Unknown operator") {}
    explicit UnknownOperator(const std::string &err) : Exception(err) {}
};

struct UnknownFunction final : public Exception
{
    UnknownFunction() : Exception("Unknown function") {}
    explicit UnknownFunction(const std::string &err) : Exception(err) {}
};

struct InvalidExpression final : public Exception
{
    InvalidExpression() : Exception("Invalid expression") {}
    explicit InvalidExpression(const std::string &err) : Exception(err) {}
};
#endif /* EXCEPTIONS_HPP */