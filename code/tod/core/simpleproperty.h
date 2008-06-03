#ifndef TOD_CORE_PROPERTY_SIMPLEPROPERTY_H
#define TOD_CORE_PROPERTY_SIMPLEPROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::SimpleProperty
    @brief
*/

#include "tod/core/property.h"

namespace tod
{
    template <typename PROPERTY_TYPE>
    class SimpleProperty : public Property
    {
    public:
        virtual void set(Object* object, PROPERTY_TYPE value)=0;
        virtual PROPERTY_TYPE get(Object* object) const=0;

        override type_id getType() const
        {
            return TypeId<PROPERTY_TYPE>::id();
        }
    };
}

#endif // TOD_CORE_PROPERTY_SIMPLEPROPERTY_H
