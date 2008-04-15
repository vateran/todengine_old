#ifndef TOD_CORE_SERIALIZER_XMLSERIALIZER_H
#define TOD_CORE_SERIALIZER_XMLSERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::core::XmlSerializer
    @brief
*/

#include "tod/core/define.h"
#include "tod/core/serializer.h"

namespace tod
{
namespace core
{
    class Object;
    class XmlSerializer : public Serializer
    {
    public:
        override bool serialize(const Uri& uri, Object* object);
        override Object* deserialize(const Uri& uri)=0;
    };
}
}

#endif // TOD_CORE_SERIALIZER_XMLSERIALIZER_H
