#ifndef TOD_CORE_UTILITY_STRINGCONVERTER_H
#define TOD_CORE_UTILITY_STRINGCONVERTER_H
/**
    @ingroup TodCoreUtility
    @class tod::StringConverter
    @brief 
*/

#include "tod/core/primitivetype.h"
#include "tod/core/string.h"

namespace tod
{
    class Object;
    class Property;
    class StringConverter
    {
    public:
        virtual type_id getTypeId()=0;
        virtual const char_t* getTypeKeyword() const=0;
        virtual const String& toString(Object* object, Property* property)=0;
        virtual void fromString(Object* object, Property* property, const String& value)=0;
    };
}

#endif // TOD_CORE_UTILITY_STRINGCONVERTER_H
