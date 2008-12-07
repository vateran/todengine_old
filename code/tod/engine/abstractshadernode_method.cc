#include "tod/engine/abstractshadernode.h"

#include "tod/core/methodbinder.h"

using namespace tod;
using namespace tod::engine;

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
void AbstractShaderNode::bindMethod()
{
    BIND_METHOD(v_setTexture_ss, AbstractShaderNode_v_setTexture_ss);
    BIND_METHOD(v_setCubeTexture_ss, AbstractShaderNode_v_setCubeTexture_ss);
}
