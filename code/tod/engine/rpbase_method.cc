#include "tod/engine/rpbase.h"

#include "tod/core/methodbinder.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
/**
    @in  param name  shader parameter name
    @in  param value float value
*/
static void RpBase_v_setFloat_sf(RpBase* self, Parameter* param)
{
    self->setFloat(
        param->in()->get<String>(0).get(),
        param->in()->get<float>(1).get());
}


//-----------------------------------------------------------------------------
/**
    @in  param name, texture uri
*/
static void RpBase_v_setTexture_ss
(RpBase* self, Parameter* param)
{
    self->setTexture(
        param->in()->get<String>(0).get(),
        param->in()->get<String>(1).get());
}


//-----------------------------------------------------------------------------
/**
    @in  param name, cube texture uri
*/
static void RpBase_v_setCubeTexture_ss
(RpBase* self, Parameter* param)
{
    self->setCubeTexture(
        param->in()->get<String>(0).get(),
        param->in()->get<String>(1).get());
}

static void RpBase_i_getShaderParamNum_v(RpBase* self, Parameter* param)
{
    if (self->getShader() == 0)
    {
        param->out()->get<int>(0) = 0;
        return;
    }
    param->out()->get<int>(0) = self->getShader()->getParameterNum();
}

static void RpBase_ssss_getShaderParamDesc_i(RpBase* self, Parameter* param)
{
    if (self->getShader() == 0)
        return;    

    ShaderParamDesc desc =
        self->getShader()->getParameterDesc(param->in()->get<int>(0));
    param->out()->get<String>(0) = desc.name_;
    param->out()->get<String>(1) = desc.semantic_;
    param->out()->get<String>(2) = ShaderParamTypeEnumeration(desc.type_).toString();
    param->out()->get<String>(3) = desc.value_;
}


//-----------------------------------------------------------------------------
void RpBase::bindMethod()
{
    BIND_METHOD(v_setFloat_sf, RpBase_v_setFloat_sf);
    BIND_METHOD(v_setTexture_ss, RpBase_v_setTexture_ss);
    BIND_METHOD(v_setCubeTexture_ss, RpBase_v_setCubeTexture_ss);
    BIND_METHOD(i_getShaderParamNum_v, RpBase_i_getShaderParamNum_v);
    BIND_METHOD(ssss_getShaderParamDesc_i, RpBase_ssss_getShaderParamDesc_i);
}
