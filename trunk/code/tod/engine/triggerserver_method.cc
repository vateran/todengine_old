#include "tod/engine/triggerserver.h"

#include "tod/core/methodbinder.h"

using namespace tod::core;
using namespace tod::engine;

//-----------------------------------------------------------------------------
static void TriggerServer_v_add_of(TriggerServer* self, Parameter* param)
{
    self->add(param->in()->get<Node*>(0), param->in()->get<float>(1));
}

//-----------------------------------------------------------------------------
static void TriggerServer_v_remove_o(TriggerServer* self, Parameter* param)
{
    self->remove(param->in()->get<Node*>(0));
}

//-----------------------------------------------------------------------------
void TriggerServer::bindMethod()
{
    BIND_METHOD(v_add_of, TriggerServer_v_add_of);
    BIND_METHOD(v_remove_o, TriggerServer_v_remove_o);
}
