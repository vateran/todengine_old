#ifndef TOD_CORE_PROPERTY_ENUMPROPERTYBINDER_H
#define TOD_CORE_PROPERTY_ENUMPROPERTYBINDER_H
/**
    @ingroup TodCoreObject
    @class tod::core::EnumPropertyBinder
    @brief
*/

#include "tod/core/enumproperty.h"

namespace tod
{
namespace core
{
    template <typename TYPE, typename PROPERTY_TYPE>
    class EnumPropertyBinder : public EnumProperty<PROPERTY_TYPE>
    {
    private:
        typedef void (TYPE::*Setter)(const PROPERTY_TYPE&);
        typedef const PROPERTY_TYPE& (TYPE::*Getter)() const;

    public:
        EnumPropertyBinder();

        void bind(Setter set, Getter get);
        override void set(Object* object, const char_t* name);
        override void set(Object* object, const PROPERTY_TYPE& value);
        override const PROPERTY_TYPE& get(Object* object) const;
        override bool isReadOnly() const;

    private:
        Setter setter;
        Getter getter;
    };

#include "tod/core/enumpropertybinder.inl"

#define BIND_ENUM_PROPERTY(ptype, name, setter, getter) \
    static EnumPropertyBinder<type, ptype> s_##ptype##_property;\
    s_##ptype##_property.setName(STRING(#name));\
    s_##ptype##_property.bind(setter, getter);\
    TYPE.addProperty(&s_##ptype##_property);

#define ENUM_PROPERTY_ADD(ptype, value) \
    s_##ptype##_property.add(STRING(#value), value);

}
}

#endif // TOD_CORE_PROPERTY_ENUMPROPERTYBINDER_H
