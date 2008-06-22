#ifndef TOD_CORE_SERIALIZER_SERIALIZER_H
#define TOD_CORE_SERIALIZER_SERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::Serializer
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"
#include "tod/core/name.h"

namespace tod
{
    class SerializerEvent
    {
    public:
        virtual void beginSerialize()=0;
        virtual void endSerialize()=0;

        virtual void beginDeserialize()=0;
        virtual void endDeserialize()=0;
    };

    class Object;
    class Serializer
    {
    public:
        virtual bool serialize(const Uri& uri, Object* object)=0;
        virtual Object* deserialize(const Uri& uri, const Name& name)=0;
    };
}

#endif // TOD_CORE_SERIALIZER_SERIALIZER_H
