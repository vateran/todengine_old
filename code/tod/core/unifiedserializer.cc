#include "tod/core/unifiedserializer.h"

using namespace tod;

//-----------------------------------------------------------------------------
bool UnifiedSerializer::serialize(const Uri& uri, Object* object)
{
    return true;
}


//-----------------------------------------------------------------------------
Object* UnifiedSerializer::deserialize(const Uri& uri, const Name& name)
{
    return 0;
}
