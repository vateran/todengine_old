#ifndef TOD_CORE_OBJECT_OBJECT_H
#define TOD_CORE_OBJECT_OBJECT_H
/**
    @ingroup TodCoreObject
    @class tod::Object
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/name.h"
#include "tod/core/time.h"
#include "tod/core/type.h"

namespace tod
{
    class Object
    {
    public:
        DECLARE_SUPERCLASS(Object);

        bool isKindOf(const name_t* name);
        bool isKindOf(const Type& type);

        static void bindMethod();
        static void bindProperty();
    };
}

#endif // TOD_CORE_OBJECT_OBJECT_H
