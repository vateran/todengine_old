#include "tod/engine/triggerserver.h"

#include "tod/core/methodbinder.h"

using namespace tod;
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
static void TriggerServer_v_setPeriod_f(TriggerServer* self, Parameter* param)
{
    self->setPeriod(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void TriggerServer_f_getPeriod_v(TriggerServer* self, Parameter* param)
{
    param->out()->get<float>(0) = static_cast<float>(self->getPeriod());
}


//-----------------------------------------------------------------------------
static void TriggerServer_v_quit_v(TriggerServer* self, Parameter* param)
{
    self->quit();
}


//-----------------------------------------------------------------------------
void TriggerServer::bindMethod()
{
    BIND_METHOD(v_add_of, TriggerServer_v_add_of);
    BIND_METHOD(v_remove_o, TriggerServer_v_remove_o);
    BIND_METHOD(v_setPeriod_f, TriggerServer_v_setPeriod_f);
    BIND_METHOD(f_getPeriod_v, TriggerServer_f_getPeriod_v);
    BIND_METHOD(v_quit_v, TriggerServer_v_quit_v);
}
