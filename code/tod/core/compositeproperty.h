#ifndef TOD_CORE_PROPERTY_COMPOSITEPROPERTY_H
#define TOD_CORE_PROPERTY_COMPOSITEPROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::core::CompositeProperty
    @brief
*/

#include "tod/core/properties.h"

namespace tod
{
namespace core
{
    template <typename PROPERTY_TYPE>
    class CompositeProperty : public Property
    {
    public:
        virtual void set(Object* object, PROPERTY_TYPE value)=0;
        virtual PROPERTY_TYPE get(Object* object) const=0;

        override type_id getType() const
        {
            return TypeId<PROPERTY_TYPE>::id();
        }

        bool addProperty(Property* property);
        Property* findProperty(const name_t* name);
        size_t getPropertySize() const;
        Properties::iterator firstProperty();
        Properties::iterator lastProperty();
        Properties::const_iterator firstProperty() const;
        Properties::const_iterator lastProperty() const;

    private:
        Properties properties_;
    };

#include "tod/core/compositeproperty.inl"
    
}
}

#endif // TOD_CORE_PROPERTY_COMPOSITEPROPERTY_H
