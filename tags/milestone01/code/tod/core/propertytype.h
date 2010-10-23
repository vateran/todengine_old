#ifndef TOD_CORE_PROPERTY_PROPERTYTYPE_H
#define TOD_CORE_PROPERTY_PROPERTYTYPE_H
/**
    @ingroup TodCoreObject
    @class tod::PropertyType
    @brief
*/

#include "tod/core/typeid.h"

namespace tod
{
    template <typename PROPERTY_TYPE>
    class SimpleProperty; 

    class Name;
    class String;
    class Uri;    
    template <typename T>
    class PropertyType
    {
    public:
        static Property::Type Id;
    };

    template <typename T>
    Property::Type
    PropertyType<T>::Id = TypeId<T>::id();
}

#endif // TOD_CORE_PROPERTY_PROPERTYTYPE_H
