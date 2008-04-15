#include "tod/core/object.h"

#include "tod/core/define.h"

using namespace tod::core;

IMPLEMENT_SUPERCLASS(Object);

//-----------------------------------------------------------------------------
bool Object::isKindOf(const name_t* name)
{
    return getType().isKindOf(name);
}


//-----------------------------------------------------------------------------
bool Object::isKindOf(const Type& type)
{
    return getType().isKindOf(type);
}


//-----------------------------------------------------------------------------
void Object::bindProperty()
{
    // empty
}
