#include "tod/core/object.h"

#include "tod/core/define.h"

using namespace tod;

IMPLEMENT_SUPERCLASS(Object);

//-----------------------------------------------------------------------------
bool Object::isKindOf(const String& name)
{
    return getType()->isKindOf(name);
}


//-----------------------------------------------------------------------------
bool Object::isKindOf(const Type* type)
{
    return getType()->isKindOf(type);
}


//-----------------------------------------------------------------------------
void Object::bindProperty()
{
    // empty
}
