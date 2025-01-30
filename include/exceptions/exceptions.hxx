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

struct RedeclarationError final : public Exception{

    /// @brief Default constructor
    RedeclarationError() : Exception("Variable already exists"){} ;

    /// @brief Constructor with error message
    /// @param err error message
    explicit RedeclarationError(const std::string &err) : Exception(err) {};
};

struct InvalidSyntax final : public  Exception{

    /// @brief Default constructor
    InvalidSyntax() : Exception("Invalid Syntax") {} ;

    /// @brief Constructor with error message
    /// @param err error message
    explicit InvalidSyntax(const std::string &err) : Exception(err) {};
};
struct InvalidTypeError final: public Exception {
    /// @brief Default constructor
    InvalidTypeError() : Exception("Invalid Syntax") {} ;

    /// @brief Constructor with error message
    /// @param err error message
    explicit InvalidTypeError(const std::string &err) : Exception(err) {};
};

struct TypeMismatchError final: public Exception {
    /// @brief Default constructor
    TypeMismatchError() : Exception("Invalid Syntax") {} ;

    /// @brief Constructor with error message
    /// @param err error message
    explicit TypeMismatchError(const std::string &err) : Exception(err) {};
};

// New custom exceptions for function validation
struct InvalidReturnTypeError final : public Exception {
    InvalidReturnTypeError() : Exception("Invalid return type usage") {}
    explicit InvalidReturnTypeError(const std::string& err) : Exception(err) {}
};

struct UnbalancedBracesError final : public Exception {
    UnbalancedBracesError() : Exception("Unbalanced braces in function body") {}
    explicit UnbalancedBracesError(const std::string& err) : Exception(err) {}
};

struct MissingSemicolonError final : public Exception {
    MissingSemicolonError() : Exception("Missing semicolons in statements") {}
    explicit MissingSemicolonError(const std::string& err) : Exception(err) {}
};

struct UndeclaredVariableError final : public Exception {
    UndeclaredVariableError() : Exception("Usage of undeclared variable") {}
    explicit UndeclaredVariableError(const std::string& err) : Exception(err) {}
};

struct MissingLetKeywordError final : public Exception {
    MissingLetKeywordError() : Exception("Missing 'let' keyword in parameter declaration") {}
    explicit MissingLetKeywordError(const std::string& err) : Exception(err) {}
};

struct InvalidFunctionDeclarationError final : public Exception {
    InvalidFunctionDeclarationError() : Exception("Invalid function declaration syntax") {}
    explicit InvalidFunctionDeclarationError(const std::string& err) : Exception(err) {}
};

struct MissingReturnArrowError final : public Exception {
    MissingReturnArrowError() : Exception("Missing return type arrow '->'") {}
    explicit MissingReturnArrowError(const std::string& err) : Exception(err) {}
};
#endif /* EXCEPTIONS_HPP */