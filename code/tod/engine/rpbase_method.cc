#include "tod/engine/rpbase.h"

#include "tod/core/methodbinder.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
/**
    @in  param name, texture uri
*/
static void RpBase_v_addTexture_ss
(RpBase* self, Parameter* param)
{
    self->addTexture(
        param->in()->get<String>(0).get(),
        param->in()->get<String>(1).get());
}


//-----------------------------------------------------------------------------
/**
@in  param name, cube texture uri
*/
static void RpBase_v_addCubeTexture_ss
(RpBase* self, Parameter* param)
{
    self->addCubeTexture(
        param->in()->get<String>(0).get(),
        param->in()->get<String>(1).get());
}


//-----------------------------------------------------------------------------
void RpBase::bindMethod()
{
    BIND_METHOD(v_addTexture_ss, RpBase_v_addTexture_ss);
    BIND_METHOD(v_addCubeTexture_ss, RpBase_v_addCubeTexture_ss);
}
