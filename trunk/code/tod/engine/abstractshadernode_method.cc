#include "tod/engine/abstractshadernode.h"

#include "tod/core/methodbinder.h"
#include "tod/engine/shader.h"

using namespace tod;
using namespace tod::engine;

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
/**
    @in  param name  shader parameter name
    @in  param value float value
*/
static void AbstractShaderNode_v_setFloat_sf(AbstractShaderNode* self, Parameter* param)
{
    self->setFloat(
        param->in()->get<String>(0).get(),
        param->in()->get<float>(1).get());
}


//-----------------------------------------------------------------------------
/**
    @in  param name, texture uri
*/
static void AbstractShaderNode_v_setTexture_ss
(AbstractShaderNode* self, Parameter* param)
{
    self->setTexture(
        param->in()->get<String>(0).get(),
        param->in()->get<String>(1).get());
}


//-----------------------------------------------------------------------------
/**
    @in  param name, cube texture uri
*/
static void AbstractShaderNode_v_setCubeTexture_ss
(AbstractShaderNode* self, Parameter* param)
{
    self->setCubeTexture(
        param->in()->get<String>(0).get(),
        param->in()->get<String>(1).get());
}


//-----------------------------------------------------------------------------
static void AbstractShaderNode_i_getShaderParamNum_v
(AbstractShaderNode* self, Parameter* param)
{
    if (self->getShader() == 0)
    {
        param->out()->get<int>(0) = 0;
        return;
    }
    param->out()->get<int>(0) = self->getShader()->getParameterNum();
}


//-----------------------------------------------------------------------------
static void AbstractShaderNode_ssss_getShaderParamDesc_i
(AbstractShaderNode* self, Parameter* param)
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
void AbstractShaderNode::bindMethod()
{
    BIND_METHOD(v_setFloat_sf, AbstractShaderNode_v_setFloat_sf);
    BIND_METHOD(v_setTexture_ss, AbstractShaderNode_v_setTexture_ss);
    BIND_METHOD(v_setCubeTexture_ss, AbstractShaderNode_v_setCubeTexture_ss);
    BIND_METHOD(i_getShaderParamNum_v, AbstractShaderNode_i_getShaderParamNum_v);
    BIND_METHOD(ssss_getShaderParamDesc_i, AbstractShaderNode_ssss_getShaderParamDesc_i);
}
