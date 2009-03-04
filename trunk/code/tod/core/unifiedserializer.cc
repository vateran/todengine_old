#include "tod/core/unifiedserializer.h"

using namespace tod;

//-----------------------------------------------------------------------------
bool UnifiedSerializer::serialize(const Uri& uri, Object* object)
{
    return true;
}


//-----------------------------------------------------------------------------
Object* UnifiedSerializer::deserialize
(Node* parent, const Uri& uri, const char_t* name)
{
    return 0;
}
