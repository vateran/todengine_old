#ifndef TOD_CORE_PROPERTY_SIMPLEPROPERTYBINDER_H
#define TOD_CORE_PROPERTY_SIMPLEPROPERTYBINDER_H
/**
    @ingroup TodCoreObject
    @class tod::SimplePropertyBinder
    @brief
*/

#include "tod/core/simpleproperty.h"

namespace tod
{
    template <typename TYPE, typename PROPERTY_TYPE>
    class SimplePropertyBinder : public SimpleProperty<PROPERTY_TYPE>
    {
    private:
        typedef void (TYPE::*Setter)(PROPERTY_TYPE);
        typedef PROPERTY_TYPE (TYPE::*Getter)() const;

    public:
        SimplePropertyBinder();

        void bind(Setter set, Getter get);
        override void set(Object* object, PROPERTY_TYPE value);
        override PROPERTY_TYPE get(Object* object) const;
        override bool isReadOnly() const;

    private:
        Setter setter;
        Getter getter;
    };

#include "tod/core/simplepropertybinder.inl"

#define BIND_PROPERTY(ptype, name, setter, getter) \
    static SimplePropertyBinder<type, ptype> s_##name##_property;\
    s_##name##_property.setName(#name);\
    s_##name##_property.bind(setter, getter);\
    TYPE.addProperty(&s_##name##_property);
}

#endif // TOD_CORE_PROPERTY_SIMPLEPROPERTYBINDER_H
