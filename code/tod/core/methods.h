#ifndef TOD_CORE_PROPERTY_METHODS_H
#define TOD_CORE_PROPERTY_METHODS_H
/**
    @ingroup TodCoreObject
    @class tod::Properties
    @brief
*/

#include <map>
#include "tod/core/method.h"

namespace tod
{
    class Methods : public std::map<Name, Method*>
    {
    public:
    };
}

#endif // TOD_CORE_PROPERTY_METHODS_H
