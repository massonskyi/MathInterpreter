#ifndef ABSTRACTCONTAINEROBJECT_H
#define ABSTRACTCONTAINEROBJECT_H


#include "core.h"
#include "abstractobject.h"


#include <memory>
#include <vector>

/// @brief Abstract container object
/// @details Abstract container object
class AbstractContainerType : public AbstractObject{
public:
    using AbstractObject::AbstractObject;

    // /// @brief This method adds object to the container
    // /// @param object to add be added to the container
    // inline virtual void add(std::shared_ptr<AbstractObject> object){ throw std::runtime_error("Not implemented"); }

    // /// @brief This method returns size of the container
    // /// @return size of the container
    // inline virtual size_t size() const { throw std::runtime_error("Not implemented"); }

    // /// @brief This method returns object by index its index container
    // /// @param index of the object
    // /// @return object by index
    // inline virtual std::shared_ptr<AbstractObject> get(size_t index) const { throw std::runtime_error("Not implemented"); }
protected:
    std::vector<std::shared_ptr<AbstractObject>> objects; // vector of objects
};



#endif /* ABSTRACTCONTAINEROBJECT_H */