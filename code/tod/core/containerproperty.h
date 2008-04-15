#ifndef TOD_CORE_PROPERTY_CONTAINERPROPERTY_H
#define TOD_CORE_PROPERTY_CONTAINERPROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::core::ContainerProperty
    @brief
*/

#include <hash_map>
#include "tod/core/property.h"

namespace tod
{
namespace core
{
    template <typename TYPE, typename KEY_TYPE, typename VALUE_TYPE>
    class ContainerProperty : public Property
    {
    private:
        typedef void (TYPE::*Inserter)(const KEY_TYPE&);
        typedef void (TYPE::*Remover)(const KEY_TYPE&);
        typedef VALUE_TYPE& (TYPE::*Searcher)(const KEY_TYPE&);

    public:
        ContainerProperty();

        override bool isReadOnly() const;
        override type_id getType() const;

        void bind(Inserter inserter, Remover remover, Searcher searcher);

        void insert(Object* object, const KEY_TYPE& index);
        void remove(Object* object, const KEY_TYPE& index);
        VALUE_TYPE& search(Object* object, const KEY_TYPE& index);

    private:
        Inserter inserter_;
        Remover remover_;
        Searcher searcher_;
    };

#include "tod/core/containerproperty.inl"

#define BIND_CONTAINER_PROPERTY(keytype, valuetype, name, inserter, remover, searcher) \
    static ContainerProperty<type, keytype, valuetype> s_##name##_property;\
    s_##name##_property.setName(STRING(#name));\
    s_##name##_property.bind(inserter, remover, searcher);\
    TYPE.addProperty(&s_##name##_property);

}
}

#endif // TOD_CORE_PROPERTY_CONTAINERPROPERTY_H
