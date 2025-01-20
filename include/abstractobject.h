#ifndef ABSTRACTOBJECT_H_
#define ABSTRACTOBJECT_H_

#include "core.h"
#include <string>
#include <stdexcept> // runtime_error
#include <utility>

using namespace std;
/// @brief This class is used to represent an object
class AbstractObject
{
public:
    /// @brief Default constructorsssss
    AbstractObject() = default;

    /// @brief This constructor is used to create a new object
    /// @param n The name of the object new object
    explicit AbstractObject(string n = "") : name(std::move(n)) {}

    /// @brief Default destructor
    virtual ~AbstractObject() = default;

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
    [[nodiscard]] virtual string toString() const { throw runtime_error("Not implemented"); }

    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
    [[nodiscard]] virtual string getTypeName() const { throw runtime_error("Not implemented"); }

    /// @brief This method is used to set the name of the object
    /// @param n The name of the object
    void setName(const string &n) { name = n; }

    /// @brief This method is used to get the name of the object
    /// @return The name of the object
    [[nodiscard]] string getName() const { return name; }

    virtual AbstractObject operator+(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject operator-(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject operator*(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject operator/(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject operator%(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }

    virtual AbstractObject &operator+=(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject &operator-=(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject &operator*=(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject &operator/=(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject &operator%=(const AbstractObject &)
    {
        throw runtime_error("Not implemented");
    }
    virtual AbstractObject &operator=(const AbstractObject &) { throw runtime_error("Not implemented"); }
    virtual bool operator==(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    virtual bool operator!=(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator<(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator<=(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator>(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator>=(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator!() const { throw runtime_error("Not implemented"); }
    // virtual bool operator&&(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator||(const AbstractObject &) const { throw runtime_error("Not implemented"); }
    // virtual bool operator&(const AbstractObject &) const { throw runtime_error("Not implemented"); }

    virtual AbstractObject &operator++() { throw runtime_error("Not implemented"); }
    virtual AbstractObject &operator--() { throw runtime_error("Not implemented"); }
    // Виртуальный метод для вывода
    virtual void print(std::ostream &os) const
    {
        throw std::runtime_error("Not implemented");
    }
    /// @brief This method returns the value of the object
    /// @return The value of the object
    [[nodiscard]] virtual AbstractObject get() const { throw runtime_error("Not implemented"); }
    // Дружеский оператор вывода, который вызывает виртуальный метод print()
    friend std::ostream &operator<<(std::ostream &os, const AbstractObject &obj)
    {
        obj.print(os);
        return os;
    }

protected:
    string name; // name of the object
};

#endif /* ABSTRACTOBJECT_H_ */