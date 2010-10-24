#ifndef TOD_CORE_PROPERTY_PROPERTY_H
#define TOD_CORE_PROPERTY_PROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::Property
    @brief
*/

#include "tod/core/string.h"
#include "tod/core/primitivetype.h"
#include "tod/core/vector2.h"
#include "tod/core/vector3.h"
#include "tod/core/vector4.h"
#include "tod/core/typeid.h"

namespace tod
{
    class Object;
    class Property
    {
    public:
        void setName(const String& name);
        virtual const String& getName() const;
        const String& toString(Object* object);
        void fromString(Object* object, const String& value);
        const char_t* getTypeKeyword() const;

        virtual bool isReadOnly() const=0;
        virtual type_id getType() const;
        virtual Property* findProperty(const String& name);

    private:
        String name_;
    };

#include "tod/core/property.inl"

}

#endif // TOD_CORE_PROPERTY_PROPERTY_H
