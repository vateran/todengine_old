#ifndef TOD_CORE_SERIALIZER_SERIALIZER_H
#define TOD_CORE_SERIALIZER_SERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::Serializer
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"
#include "tod/core/string.h"

namespace tod
{
    class Object;
    class Node;
    class Serializer
    {
    public:
        virtual bool serialize(const Uri& uri, Object* object)=0;
        virtual Object* deserialize(Node* parent, const Uri& uri, const char_t* name)=0;
    };
}

#endif // TOD_CORE_SERIALIZER_SERIALIZER_H
