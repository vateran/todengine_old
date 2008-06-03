#include "tod/core/property.h"

#include "tod/core/tostring.h"

using namespace tod;

//-----------------------------------------------------------------------------
const String& Property::toString(Object* object)
{
    return ToString::instance()->toString(object, this);
}


//-----------------------------------------------------------------------------
void Property::fromString(Object* object, const char_t* value)
{
    ToString::instance()->fromString(object, this, value);
}


//-----------------------------------------------------------------------------
const char_t* Property::getTypeKeyword() const
{
    return ToString::instance()->getTypeKeyword(this);
}
