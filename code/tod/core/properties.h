#ifndef TOD_CORE_PROPERTY_PROPERTIES_H
#define TOD_CORE_PROPERTY_PROPERTIES_H
/**
    @ingroup TodCoreObject
    @class tod::Properties
    @brief
*/

#include <map>
#include "tod/core/property.h"

namespace tod
{
    class Properties : public std::map<Name, Property*>
    {
    public:
    };
}

#endif // TOD_CORE_PROPERTY_PROPERTIES_H
