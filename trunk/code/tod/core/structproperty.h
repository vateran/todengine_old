#ifndef TOD_CORE_PROPERTY_STRUCTPROPERTY_H
#define TOD_CORE_PROPERTY_STRUCTPROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::core::StructProperty
    @brief
*/

#include "tod/core/define.h"
#include "tod/core/property.h"
#include "tod/core/properties.h"

namespace tod
{
namespace core
{
    class StructProperty : public Property
    {
    public:
        override bool isReadOnly() const;
        override type_id getType() const;
        
        bool addProperty(Property* property);
        void removeProperty(const name_t* name);
        Property* findProperty(const name_t* name);
        size_t getPropertySize() const;
        Properties::iterator firstProperty();
        Properties::iterator lastProperty();
        Properties::const_iterator firstProperty() const;
        Properties::const_iterator lastProperty() const;

    private:
        struct ForTypeId {};

    private:
        Properties properties_;
    };

#define BIND_PROPERTY_STRUCT(name) \
    static StructProperty s_##name##_struct_property;\
    s_##name##_struct_property.setName(STRING(#name));\
    TYPE.addProperty(&s_##name##_struct_property);

#define BIND_STRUCT_TO_STRUCT(parent_group_name, group_name) \
    static StructProperty s_##group_name##_struct_property;\
    s_##group_name##_struct_property.setName(STRING(#group_name));\
    s_##parent_group_name##_struct_property.addProperty(&s_##group_name##_struct_property);

#define BIND_PROPERTY_TO_STRUCT(group_name, ptype, name, setter, getter) \
    static SimplePropertyBinder<type, ptype> s_##name##_property;\
    s_##name##_property.setName(STRING(#name));\
    s_##name##_property.bind(setter, getter);\
    s_##group_name##_struct_property.addProperty(&s_##name##_property);

}
}


#endif // TOD_CORE_PROPERTY_STRUCTPROPERTY_H
