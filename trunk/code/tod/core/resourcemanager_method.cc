#include "tod/core/resourcemanager.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void ResourceManager_v_initialize_s
(ResourceManager* self, Parameter* param)
{
    self->initialize(param->in()->get<String>(0).get().c_str());
}


//-----------------------------------------------------------------------------
static void ResourceManager_l_getStorages_v
(ResourceManager* self, Parameter* param)
{
    param->out()->clear();
    for (ResourceStorages::iterator rsi = self->firstStorage();
         rsi != self->lastStorage(); ++rsi)
    {
        param->out()->add<Object*>(new ResourceStorage(**rsi));
    }
}


//-----------------------------------------------------------------------------
static void ResourceManager_q_findStorage_s
(ResourceManager* self, Parameter* param)
{
    param->out()->get<Object*>(0) = 
        new ResourceStorage(
            *self->findStorage(param->in()->get<String>(0)));
}


//-----------------------------------------------------------------------------
void ResourceManager::bindMethod()
{
    BIND_METHOD(v_initialize_s, ResourceManager_v_initialize_s);
    BIND_METHOD(l_getStorages_v, ResourceManager_l_getStorages_v);
    BIND_METHOD(q_findStorage_s, ResourceManager_q_findStorage_s);
}
