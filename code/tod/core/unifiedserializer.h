#ifndef TOD_CORE_SERIALIZER_UNIFIEDSERIALIZER_H
#define TOD_CORE_SERIALIZER_UNIFIEDSERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::UnifiedSerializer
    @brief
*/

#include <map>
#include "tod/core/define.h"
#include "tod/core/name.h"
#include "tod/core/serializer.h"

namespace tod
{
    class Object;
    class UnifiedSerializer : public Serializer
    {
    public:
        override bool serialize(const Uri& uri, Object* object);
        override Object* deserialize(const Uri& uri)=0;

    private:
        typedef std::map<Name, Serializer*> Serializers;

    private:
        Serializers serializers_;

    };
}

#endif // TOD_CORE_SERIALIZER_UNIFIEDSERIALIZER_H
