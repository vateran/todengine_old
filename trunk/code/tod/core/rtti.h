#ifndef TOD_CORE_OBJECT_RTTI_H
#define TOD_CORE_OBJECT_RTTI_H
/**
    @ingroup TodCoreObject
    @class tod::core::Rtti
    @brief Run-time Type Information(RTTI)
*/

#include "tod/core/type.h"
#include "tod/core/name.h"

namespace tod
{
namespace core
{
    class MetaObject;
    class Rtti
    {
    public:
        Rtti(const type::name_t* name, const Rtti* base);

        const type::Name& Name() const;

        bool equal(const Rtti& rtti) const;
        bool isKindOf(const type::name_t* name) const;
        bool isKindOf(const Rtti& rtti) const;

    private:
        type::Name name;
        const Rtti* base;
        MetaObject* metaObject;
    };

#define DECLARE_SUPERCLASS(cls) public:\
    typedef cls type;\
    static const tod::core::Rtti rtti;\
    override const tod::core::Rtti& getRtti() const { return rtti; }\
    override const tod::core::type::name_t* toString() { return STRING(#cls); }
#define DECLARE_CLASS(cls, base_cls) public:\
    typedef base_cls super;\
    typedef cls type;\
    static const tod::core::Rtti rtti;\
    override const tod::core::Rtti& getRtti() const { return rtti; }\
    override const tod::core::type::name_t* toString() { return STRING(#cls); }

#define IMPLEMENT_SUPERCLASS(cls) const tod::core::Rtti cls::rtti(STRING(#cls), 0);
#define IMPLEMENT_CLASS(cls, base_cls) const tod::core::Rtti cls::rtti(STRING(#cls), &base_cls::rtti);

}
}

#endif // TOD_CORE_OBJECT_RTTI_H
