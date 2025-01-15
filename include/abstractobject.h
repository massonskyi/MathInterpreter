#ifndef ABSTRACTOBJECT_H_
#define ABSTRACTOBJECT_H_

#include "core.h"
#include <string>
#include <stdexcept> // runtime_error

using namespace std;
/// @brief This class is used to represent an object
class AbstractObject {
public:
    /// @brief Default constructorsssss
    AbstractObject() = default;

    /// @brief This constructor is used to create a new object
    /// @param n The name of the object new object
    AbstractObject(const string& n = "") : name(n) {}

    /// @brief Default destructor
    virtual ~AbstractObject() = default;

    /// @brief  This method is used to print the object
    /// @return The string representation of the object
    inline virtual string toString() const{ throw runtime_error("Not implemented"); }

    /// @brief  This method is used to get the type of the object
    /// @return The type of the object
    inline virtual string getTypeName() const{ throw runtime_error("Not implemented"); }

    /// @brief This method is used to set the name of the object
    /// @param n The name of the object
    inline void setName(const string& n) { name = n; }

    /// @brief This method is used to get the name of the object
    /// @return The name of the object
    inline string getName() const { return name; }

protected:
    string name; // name of the object
};


#endif /* ABSTRACTOBJECT_H_ */