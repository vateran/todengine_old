#include "tod/engine/formatstringconverter.h"

#include "tod/core/typeid.h"
#include "tod/core/simpleproperty.h"
#include "tod/engine/format.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
type_id FormatStringConverter::getTypeId()
{
    return TypeId<const Format&>::id();
}


//-----------------------------------------------------------------------------
const char_t* FormatStringConverter::getTypeKeyword() const
{
    return STRING("format");
}


//-----------------------------------------------------------------------------
const String& FormatStringConverter::toString
(Object* object, Property* property)
{
    typedef SimpleProperty<const Format&> AdaptiveProperty;
    AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
    return str_ = p->get(object).toString();
}


//-----------------------------------------------------------------------------
void FormatStringConverter::fromString
(Object* object, Property* property, const char_t* value)
{
    typedef SimpleProperty<const Format&> AdaptiveProperty;
    AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
    p->set(object, value);
}
