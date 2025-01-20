#ifndef ABSTRACTSIMPLEOBJECT_H
#define ABSTRACTSIMPLEOBJECT_H

#include "core.h"
#include "abstractobject.h"

#include <memory>
#include <string>
using namespace std;

/// @brief Th Abstract simple type 
/// @details This class is the base class for all simple types
class AbstractSimpleType : public AbstractObject{
public:
    using AbstractObject::AbstractObject;
    AbstractSimpleType() = default;
    /// @brief This method sets the value of the object
    /// @param value The value to set 
    inline virtual void set(const string& value){ throw runtime_error("Not implemented"); }
    

    /// @brief This method returns the value of the object as a string dec
    /// @return The value of the object as a string dec
    inline virtual string dec() const { throw runtime_error("Not implemented"); }
    
    /// @brief This method returns the value of the object as a string hex
    /// @return The value of the object as a string hex
    inline virtual string hex() const { throw runtime_error("Not implemented"); }

    /// @brief This method returns the value of the object as a string oct
    /// @return The value of the object as a string oct
    inline virtual string oct() const { throw runtime_error("Not implemented"); }

    /// @brief This method returns the value of the object as a string bin
    /// @return The value of the object as a string bin
    inline virtual string bin() const { throw runtime_error("Not implemented"); }

    /// @brief This method returns the value of the object as a boolean
    /// @return The value of the object as a boolean
    inline virtual bool equals(const AbstractSimpleType& other)const{ throw runtime_error("Not implemented"); }

    /// @brief  This method clones the object value of the object
    /// @return The cloned object
    inline virtual std::unique_ptr<AbstractSimpleType> clone()const{ throw runtime_error("Not implemented"); }

    /// @brief This method serializes the object value of the object
    /// @return The serialized object
    [[nodiscard]]
    inline virtual string serialize()const{ throw runtime_error("Not implemented"); }

    /// @brief  This method deserializes the object value of the object
    /// @param value The serialized object to deserialize
    inline virtual void deserialize(const string& value){ throw runtime_error("Not implemented"); }

    friend ostream& operator<<(ostream& os, const AbstractSimpleType& obj){
        os << obj.serialize();
        return os;
    }
    friend istream& operator>>(istream& is, AbstractSimpleType& obj){
        string value;
        is >> value;
        obj.deserialize(value);
        return is;
    }
};


#endif /*ABSTRACTSIMPLEOBJECT_H*/