#ifndef AST_h
#define AST_h

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <variant>
#include "../types/types.h"
#include "../function/base.h"

using ASTValue = std::variant<Variable, Vector, Matrix, Rational>;

std::ostream& operator << (const ASTValue& value, std::ostream& os) {
    if (std::holds_alternative<Variable>(value)) {
        os << std::get<Variable>(value).toString();
    } else if (std::holds_alternative<Vector>(value)) {
        os << std::get<Vector>(value).toString();
    } else if (std::holds_alternative<Matrix>(value)) {
        os << std::get<Matrix>(value).toString();
    } else if (std::holds_alternative<Rational>(value)) {
        os << std::get<Rational>(value).toString();
    }

    return os;
}
std::ostream& operator << (std::ostream& os, const ASTValue& value) {
    if (std::holds_alternative<Variable>(value)) {
        os << std::get<Variable>(value).toString();
    } else if (std::holds_alternative<Vector>(value)) {
        os << std::get<Vector>(value).toString();
    } else if (std::holds_alternative<Matrix>(value)) {
        os << std::get<Matrix>(value).toString();
    } else if (std::holds_alternative<Rational>(value)) {
        os << std::get<Rational>(value).toString();
    }
    return os;
}

class ASTNode {
public:
    struct Position {
        size_t line;
        size_t column;

        friend std::ostream& operator<<(std::ostream& os, const Position& pos) {
            os << "Line: " << pos.line << ", Column: " << pos.column;
            return os;
        }
    };
    virtual ~ASTNode() = default;
    [[nodiscard]] virtual ASTValue evaluate() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;

    [[nodiscard]] virtual Position position() const = 0;
};

class ASTContext {
public:
    ASTContext() = default;
    ASTContext(const ASTContext& other) {
        variables_ = other.variables_;
    }

    ASTContext(ASTContext&& other) noexcept : variables_(std::move(other.variables_)) {}
    
    ASTContext& operator=(const ASTContext& other) {
        if (this!= &other) {
            variables_ = other.variables_;
        }
        return *this;
    };
    ASTContext& operator=(ASTContext&& other) noexcept {
        if (this!= &other) {
            variables_ = std::move(other.variables_);
        }
        return *this;
    };
    
    void setVariable(const std::string& name, ASTValue value) {
        variables_[name] = std::move(value);
    }
    void emplace(const std::string& name, ASTValue value) {
        variables_[name] = std::move(value);
    }
    ASTValue getVariable(const std::string& name) const {
        if (auto it = variables_.find(name); it != variables_.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable not found: " + name);
    }

    bool findVariable(const std::string& name) const {
        return variables_.find(name) != variables_.end();
    }

    const ASTContext& context() const { return *this; }

    std::unordered_map<std::string, ASTValue> variables() const { return variables_; }

private:
    std::unordered_map<std::string, ASTValue> variables_;
};

class NumberNode : public ASTNode {
public:
    NumberNode() = default;
    explicit NumberNode(double value, Position pos = {0, 0}) : _value(value), pos(pos)  {}
    
    NumberNode(const NumberNode& other)=   delete;
    NumberNode(NumberNode&& other) noexcept=   delete;
    ~NumberNode() override = default;
    

    [[nodiscard]] ASTValue evaluate() const override {
        return Variable(_value); // Возвращаем значение как Variable
    }

    [[nodiscard]] std::string toString() const override {
        return std::to_string(_value); // Преобразуем число в строку
    }
    [[nodiscard]] Position position() const override { return pos; }
private:
    double _value{};
    Position pos{};
};

class VariableNode : public ASTNode {
public:
    VariableNode() = default;
    explicit VariableNode(std::string  name, ASTContext& context, Position pos_ = {0, 0})
        : _name(std::move(name)), context(context), pos_(pos_)  {}
    VariableNode(const VariableNode& other) =   delete;
    VariableNode(VariableNode&& other)=   delete;
    ~VariableNode() override = default;
    ASTValue evaluate() const override {
        return context.getVariable(_name);
    }

    ASTContext pos() const {
        return context;
        // Возвращаем контекст, чтобы можно было получить доступ к переменным внутри нода
        // для получения значения переменной
    }
    Position position() const override { return pos_; }
    std::string toString() const override {
        return _name; // Возвращаем имя переменной
    }

private:
    std::string _name;
    ASTContext context;
    Position pos_{};
};
// ast.hxx
class VectorNode : public ASTNode {
public:
    VectorNode(){
        elements = {};
        pos = {0, 0};
    }

    explicit VectorNode(std::vector<std::shared_ptr<ASTNode>> elements ={}, Position pos = {0, 0})
        : elements(std::move(elements)), pos(pos)  {}

    VectorNode(const VectorNode& other){
        elements = other.elements;
        pos = other.pos;
    }
    VectorNode(VectorNode&& other) noexcept{
        elements = other.elements;
        pos = other.pos;
    }
    [[nodiscard]] ASTValue evaluate() const override {
        Vector vec;
        for (const auto& elem : elements) {
            vec.push_back(std::get<Variable>(elem->evaluate()));
        }
        return vec;
    }
    void addElement(const std::shared_ptr<ASTNode>& element) {
        elements.push_back(element);
    }

    [[nodiscard]] Position position() const override { return pos; }
    [[nodiscard]] std::string toString() const override {
        std::string s = "[";
        for (const auto& elem : elements) {
            s.append(elem->toString(), 1);
            s.append(", ", 2);
            if (&elem!= &elements.back()) {
                s.append(" ", 1);
            }
        }
        s.append("]");
        return s;
    };
private:
    std::vector<std::shared_ptr<ASTNode>> elements;
    Position pos{};
};

class MatrixNode : public ASTNode {
public:
    explicit MatrixNode(std::vector<std::shared_ptr<ASTNode>> rows = {}, Position pos = {0, 0})
        : rows(std::move(rows)), pos(pos)  {}
    [[nodiscard]] ASTValue evaluate() const override {
        Matrix mat;
        for (const auto& row : rows) {
            mat.push_back(std::get<Vector>(row->evaluate()));
        }
        return mat;
    }
    void addRow(std::shared_ptr<ASTNode> row) {
        rows.push_back(std::move(row));
    }

    [[nodiscard]] Position position() const override { return pos; }
    [[nodiscard]] std::string toString() const override {
        std::string s = "[";
        for (const auto& row : rows) {
            s.append(row->toString(), 1);
            s.append(", ", 2);
            if (&row!= &rows.back()) {
                s.append(" ", 1);
            }
        }
        s.append("]");
        return s;
    };

private:
    std::vector<std::shared_ptr<ASTNode>> rows;
    Position pos;
};

class RationalNode : public ASTNode {
public:
    RationalNode(int numerator, int denominator, Position pos = {0, 0})
        : numerator(numerator), denominator(denominator), pos(pos)  {}

    [[nodiscard]] ASTValue evaluate() const override {
        return Rational(Variable(numerator), Variable(denominator));
    }
    [[nodiscard]] Position position() const override { return pos; }
    [[nodiscard]] std::string toString() const override {
        return "(" + std::to_string(numerator) + "/" + std::to_string(denominator) + ")";
    }
private:
    int numerator, denominator;
    Position pos;
};
class BinaryOpNode : public ASTNode {
public:
    BinaryOpNode(std::string op, std::shared_ptr<ASTNode> left, std::shared_ptr<ASTNode> right,Position pos = {0, 0})
        : op(std::move(op)), left(std::move(left)), right(std::move(right)), pos(pos)  {}

    [[nodiscard]] ASTValue evaluate() const override {
        auto l = left->evaluate();
        auto r = right->evaluate();
        return apply_operation(l, r);
    }
    [[nodiscard]] std::shared_ptr<ASTNode> Left()const { return left; }
    [[nodiscard]] std::shared_ptr<ASTNode> Right() const { return right; }

    [[nodiscard]] std::string Op()const { return op; }

    [[nodiscard]] std::string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
    [[nodiscard]] Position position() const override { return pos; }

private:
    [[nodiscard]] ASTValue apply_operation(const ASTValue& l, const ASTValue& r) const {
        return std::visit([this](auto&& lhs, auto&& rhs) -> ASTValue {
            using L = std::decay_t<decltype(lhs)>;
            using R = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<L, Variable> && std::is_same_v<R, Variable>) {
                if (op == "+") return lhs + rhs;
                if (op == "-") return lhs - rhs;
                if (op == "*") return lhs * rhs;
                if (op == "/") {
                    if (rhs == 0) throw std::runtime_error("Division by zero");
                    return lhs / rhs;
                }
            }
            else if constexpr (std::is_same_v<L, Vector> || std::is_same_v<R, Vector>) {
                return apply_vector_operation(lhs, rhs);
            }
            else if constexpr (std::is_same_v<L, Matrix> || std::is_same_v<R, Matrix>) {
                return apply_matrix_operation(lhs, rhs);
            }
            // Добавьте поддержку других типов (например, Vector, Matrix, Rational)
            throw std::runtime_error("Unsupported operation for given types");
        }, l, r);
    }
    [[nodiscard]] ASTValue apply_vector_operation(const ASTValue& l, const ASTValue& r)const {
        return std::visit([&](auto&& lhs, auto&& rhs) -> ASTValue {
            using L = std::decay_t<decltype(lhs)>;
            using R = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<L, Vector>) {
                if constexpr (std::is_same_v<R, Vector>) {
                    // Вектор-вектор операции
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                    if (op == "*") return lhs * rhs;  // Скалярное произведение
                    if (op == "/") return lhs / rhs;  // Скалярное произведение
                }
                else if constexpr (std::is_same_v<R, Variable>) {
                    // Вектор-скаляр операции
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                }
            }
            else if constexpr (std::is_same_v<R, Vector> && std::is_same_v<L, Variable>) {
                // Скаляр-вектор операции
                if (op == "*") return rhs * lhs;
                if (op == "/") return rhs / lhs;
                if (op == "+") return rhs + lhs;
                if (op == "-") return rhs - lhs;

            }else if constexpr (std::is_same_v<L, Matrix> && std::is_same_v<R, Vector>) {
                if (op == "*") return lhs * rhs;
                if (op == "/") return lhs / rhs;
                if (op == "+") return lhs + rhs;
                if (op == "-") return lhs - rhs;
            }

            throw std::runtime_error("Unsupported vector operation");
        }, l, r);
    }

    [[nodiscard]] ASTValue apply_matrix_operation(const ASTValue& l, const ASTValue& r)const {
        return std::visit([&](auto&& lhs, auto&& rhs) -> ASTValue {
            using L = std::decay_t<decltype(lhs)>;
            using R = std::decay_t<decltype(rhs)>;

            if constexpr (std::is_same_v<L, Matrix>) {
                if constexpr (std::is_same_v<R, Matrix>) {
                    // Матрица-матрица операции
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                }
                else if constexpr (std::is_same_v<R, Vector>) {
                    // Матрица-вектор операции
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;

                }
                else if constexpr (std::is_same_v<R, Variable>) {
                    // Матрица-скаляр операции
                    if (op == "*") return lhs * rhs;
                    if (op == "/") return lhs / rhs;
                    if (op == "+") return lhs + rhs;
                    if (op == "-") return lhs - rhs;
                }
            }
            else if constexpr (std::is_same_v<R, Matrix> && std::is_same_v<L, double>) {
                // Скаляр-матрица операции
                if (op == "*") return rhs * lhs;
            }

            throw std::runtime_error("Unsupported matrix operation");
        }, l, r);
    }
    std::string op;
    std::shared_ptr<ASTNode> left;
    std::shared_ptr<ASTNode> right;
    Position pos;
};

class FunctionCallNode : public ASTNode {
public:
    FunctionCallNode(std::string name, std::vector<std::shared_ptr<ASTNode>> args, Position pos = {0, 0})
        : name(std::move(name)), args(std::move(args)), pos(pos)  {}

    [[nodiscard]] ASTValue evaluate() const override {
        std::vector<ASTValue> evaluated_args;
        evaluated_args.reserve(args.size());
        for (const auto& arg : args) {
            evaluated_args.push_back(arg->evaluate());
        }

        if (name == "sin") {
            if (evaluated_args.size() != 1)
                throw std::runtime_error("Function 'sin' expects 1 argument");
            return std::visit([](auto& arg) -> ASTValue {
                return _M_sin(arg);
                }, evaluated_args[0]);
        }
        if (name == "cos") {
            if (evaluated_args.size() != 1)
                throw std::runtime_error("Function 'cos' expects 1 argument");
            return std::visit([](auto& arg) -> ASTValue {
                return _M_cos(arg);
                }, evaluated_args[0]);
        }
        // Добавьте другие функции (например, "sqrt", "log", "exp")
        throw std::runtime_error("Unknown function: " + name);
    }

    [[nodiscard]] std::string toString() const override {
        std::string result = name + "(";
        for (size_t i = 0; i < args.size(); ++i) {
            result += args[i]->toString();
            if (i < args.size() - 1) result += ", ";
        }
        result += ")";
        return result;
    }
    [[nodiscard]] std::string Name() const { return name; }
    [[nodiscard]] std::vector<std::shared_ptr<ASTNode>> Args() const { return args; }
    [[nodiscard]] Position position() const override { return pos; }
private:
    std::string name;
    std::vector<std::shared_ptr<ASTNode>> args;
    Position pos;
};


#endif