#include "tod/core/resourceentry.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void ResourceEntry_s_getName_v
(ResourceEntry* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getName();
}


//-----------------------------------------------------------------------------
static void ResourceEntry_s_getFileType_v
(ResourceEntry* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getFileType();
}


//-----------------------------------------------------------------------------
static void ResourceEntry_L_getSize_v
(ResourceEntry* self, Parameter* param)
{
    param->out()->get<int64_t>(0) = self->getSize();
}


//-----------------------------------------------------------------------------
static void ResourceEntry_L_getWriteTime_v
(ResourceEntry* self, Parameter* param)
{
    param->out()->get<int64_t>(0) = self->getWriteTime();
}


//-----------------------------------------------------------------------------
void ResourceEntry::bindMethod()
{
    BIND_METHOD(s_getName_v, ResourceEntry_s_getName_v);
    BIND_METHOD(s_getFileType_v, ResourceEntry_s_getFileType_v);
    BIND_METHOD(L_getSize_v, ResourceEntry_L_getSize_v);
    BIND_METHOD(L_getWriteTime_v, ResourceEntry_L_getWriteTime_v);
}
