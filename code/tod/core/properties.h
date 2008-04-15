#ifndef TOD_CORE_PROPERTY_PROPERTIES_H
#define TOD_CORE_PROPERTY_PROPERTIES_H
/**
    @ingroup TodCoreObject
    @class tod::core::Properties
    @brief
*/

#include <map>
#include "tod/core/property.h"

namespace tod
{
namespace core
{    
    class Properties : public std::map<Name, Property*>
    {
    public:
    };
}
}

#endif // TOD_CORE_PROPERTY_PROPERTIES_H
