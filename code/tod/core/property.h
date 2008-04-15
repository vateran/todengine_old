#ifndef TOD_CORE_PROPERTY_PROPERTY_H
#define TOD_CORE_PROPERTY_PROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::core::Property
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/name.h"
#include "tod/core/vector2.h"
#include "tod/core/vector3.h"
#include "tod/core/vector4.h"
#include "tod/core/typeid.h"

namespace tod
{
namespace core
{
    class Object;
    class Property
    {
    public:
        void setName(const name_t* name);
        const Name& getName() const;
        const String& toString(Object* object);
        void fromString(Object* object, const char_t* value);
        const char_t* getTypeKeyword() const;

        virtual bool isReadOnly() const=0;
        virtual type_id getType() const;

    private:
        Name name_;
    };

#include "tod/core/property.inl"

}
}

#endif // TOD_CORE_PROPERTY_PROPERTY_H
