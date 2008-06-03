#ifndef TOD_CORE_PROPERTY_COMPOSITEPROPERTYBINDER_H
#define TOD_CORE_PROPERTY_COMPOSITEPROPERTYBINDER_H
/**
    @ingroup TodCoreObject
    @class tod::VectorProperty
    @brief
*/

#include "tod/core/define.h"
#include "tod/core/compositeproperty.h"
#include "tod/core/properties.h"

namespace tod
{
    template <typename TYPE, typename PROPERTY_TYPE>
    class CompositePropertyBinder : public CompositeProperty<PROPERTY_TYPE>
    {
    private:
        typedef void (TYPE::*Setter)(PROPERTY_TYPE);
        typedef PROPERTY_TYPE (TYPE::*Getter)() const;

    public:
        CompositePropertyBinder();

        void bind(Setter set, Getter get);
        override void set(Object* object, PROPERTY_TYPE value);
        override PROPERTY_TYPE get(Object* object) const;
        override bool isReadOnly() const;

    private:
        Setter setter;
        Getter getter;
    };

#include "tod/core/compositepropertybinder.inl"

#define BIND_COMPOSITE_PROPERTY(ptype, name, setter, getter) \
    static CompositePropertyBinder<type, ptype> s_##name##_property;\
    s_##name##_property.setName(STRING(#name));\
    s_##name##_property.bind(setter, getter);\
    TYPE.addProperty(&s_##name##_property);

#define BIND_COMPOSITE_PROPERTY_FILED(cpname, ptype, name, setter, getter) \
    static SimplePropertyBinder<type, ptype> s_##cpname##_##name##_property;\
    s_##cpname##_##name##_property.setName(STRING(#name));\
    s_##cpname##_##name##_property.bind(setter, getter);\
    s_##cpname##_property.addProperty(&s_##cpname##_##name##_property);
}

#endif // TOD_CORE_PROPERTY_COMPOSITEPROPERTYBINDER_H
