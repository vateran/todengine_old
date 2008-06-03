#ifndef TOD_CORE_OBJECT_VARIABLE_H
#define TOD_CORE_OBJECT_VARIABLE_H
/**
    @ingroup TodCoreObject
    @class tod::Variable
    @brief
*/

#include "tod/core/primitivetype.h"

namespace tod
{
    class Variable
    {
    public:
        virtual Variable* clone()=0;
        virtual type_id getType() const=0;
    };
}

#endif // TOD_CORE_OBJECT_VARIABLE_H
