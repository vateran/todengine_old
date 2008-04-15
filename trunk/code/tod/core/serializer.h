#ifndef TOD_CORE_SERIALIZER_SERIALIZER_H
#define TOD_CORE_SERIALIZER_SERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::core::Serializer
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"

namespace tod
{
namespace core
{
    class Object;
    class Serializer
    {
    public:
        virtual bool serialize(const Uri& uri, Object* object)=0;
        virtual Object* deserialize(const Uri& uri)=0;
    };
}
}

#endif // TOD_CORE_SERIALIZER_SERIALIZER_H
