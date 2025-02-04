#ifndef ABSTRACTCONTAINEROBJECT_H
#define ABSTRACTCONTAINEROBJECT_H

#include "abstractobject.h"


#include <memory>
#include <vector>

/// @brief Abstract container object
/// @details Abstract container object
class AbstractContainerType : public AbstractObject{
public:
    using AbstractObject::AbstractObject;
    AbstractContainerType() = default;
    
    // virtual ~AbstractContainerType () = default;

    // virtual void sort() = 0;
    // virtual size_t size() const = 0;

protected:
    std::vector<std::shared_ptr<AbstractObject>> objects; // vector of objects
};



#endif /* ABSTRACTCONTAINEROBJECT_H */