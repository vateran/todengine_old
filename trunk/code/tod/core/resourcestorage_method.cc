#include "tod/core/resourcestorage.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void ResourceStorage_s_getName_v
(ResourceStorage* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getName();
}


//-----------------------------------------------------------------------------
static void ResourceStorage_l_findEntries_sb
(ResourceStorage* self, Parameter* param)
{   
    const ResourceEntries& re =
        self->findEntries(
            param->in()->get<String>(0).get().c_str(),
            param->in()->get<bool>(1));

    param->out()->clear();
    for (ResourceEntries::const_iterator rei = re.begin();
         rei != re.end(); ++rei)
    {
        param->out()->add<Object*>(new ResourceEntry(*rei));
    }
}


//-----------------------------------------------------------------------------
void ResourceStorage::bindMethod()
{
    BIND_METHOD(s_getName_v, ResourceStorage_s_getName_v);
    BIND_METHOD(l_findEntries_sb, ResourceStorage_l_findEntries_sb);
}
