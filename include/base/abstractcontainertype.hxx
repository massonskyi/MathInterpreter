#ifndef ABSTRACTCONTAINEROBJECT_H
#define ABSTRACTCONTAINEROBJECT_H

#include "abstractobject.hxx"


#include <memory>
#include <vector>

/// @brief Abstract container object
/// @details Abstract container object
class AbstractContainerType : public AbstractObject{
public:
    using AbstractObject::AbstractObject;
    AbstractContainerType() = default;
protected:
    std::vector<std::shared_ptr<AbstractObject>> objects; // vector of objects
};



#endif /* ABSTRACTCONTAINEROBJECT_H */