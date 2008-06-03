#ifndef TOD_CORE_UTILITY_TOSTRING_H
#define TOD_CORE_UTILITY_TOSTRING_H
/**
    @ingroup TodCoreUtility
    @class tod::ToString
    @brief 
*/

#include <hash_map>
#include "tod/core/primitivetype.h"
#include "tod/core/singleton.h"
#include "tod/core/string.h"

namespace tod
{
    class Object;
    class Property;
    class StringConverter;
    class ToString : public Singleton<ToString>
    {
    public:
        ToString();
        virtual~ToString();

        void addConverter(StringConverter* sc);
        const char_t* getTypeKeyword(const Property* property) const;
        const String& toString(Object* object, Property* property);
        void fromString(Object* object, Property* property, const char_t* value);

    private:
        typedef stdext::hash_map<type_id, StringConverter*> StringConverters;

    private:
        StringConverters converters_;
    };
}

#endif // TOD_CORE_UTILITY_TOSTRING_H
