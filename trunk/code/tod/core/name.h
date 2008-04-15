#ifndef TOD_CORE_TYPE_NAME_H
#define TOD_CORE_TYPE_NAME_H
/**
    @ingroup TodCoreType
    @class tod::core::Name
    @brief Name type
*/

#include "tod/core/string.h"

namespace tod
{
namespace core
{
    class Name : public String
    {
    public:
        Name() {}
        Name(const char_t* s):String(s) {}
        Name(const Name& name):String(name) {}
        Name(const String& s):String(s) {}
    };
}
}

#endif // TOD_CORE_TYPE_NAME_H
