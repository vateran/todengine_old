#include "tod/engine/renderer.h"

#include "tod/core/methodbinder.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
static void Renderer_v_setDisplayMode_s(Renderer* self, Parameter* param)
{
    self->setDisplayMode(param->in()->get<String>(0).get());
}

//-----------------------------------------------------------------------------
static void Renderer_s_getDisplayMode_v(Renderer* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getDisplayMode();
}

//-----------------------------------------------------------------------------
void Renderer::bindMethod()
{
    BIND_METHOD(v_setDisplayMode_s, Renderer_v_setDisplayMode_s);
    BIND_METHOD(s_getDisplayMode_v, Renderer_s_getDisplayMode_v);
}
