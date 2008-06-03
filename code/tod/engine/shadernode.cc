#include "tod/engine/shadernode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/shader.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(ShaderNode, AbstractShaderNode);

//-----------------------------------------------------------------------------
ShaderNode::ShaderNode():
shader_(0)
{

}


//-----------------------------------------------------------------------------
ShaderNode::~ShaderNode()
{

}


//-----------------------------------------------------------------------------
void ShaderNode::applyShader(SceneServer* scene_server)
{
    if (shader_.invalid())
        return;
    Renderer::instance()->setShader(shader_);
}


//-----------------------------------------------------------------------------
void ShaderNode::renderShader
(SceneServer* scene_server, SceneContext* scene_context)
{
    if (shader_.invalid())
        return;
    commit(shader_);
    if (getTechnique().size())
        shader_->setTechnique(getTechnique());
}


//-----------------------------------------------------------------------------
bool ShaderNode::loadResource()
{
    if (getShaderUri().empty())
        return false;

    super::loadResource();
    shader_ = Renderer::instance()->newShader(getShaderUri());
    shader_->preload();
    return true;
}


//-----------------------------------------------------------------------------
void ShaderNode::unloadResource()
{
    shader_.release();
    super::unloadResource();
}


//-----------------------------------------------------------------------------
bool ShaderNode::hasShader() const
{
    return true;
}


//-----------------------------------------------------------------------------
void ShaderNode::setShaderUri(const Uri& uri)
{
    uri_ = uri;
}


//-----------------------------------------------------------------------------
const Uri& ShaderNode::getShaderUri() const
{
    return uri_;
}


//-----------------------------------------------------------------------------
void ShaderNode::setTechnique(const String& t)
{
    technique_ = t;
}


//-----------------------------------------------------------------------------
const String& ShaderNode::getTechnique() const
{
    return technique_;
}


//-----------------------------------------------------------------------------
void ShaderNode::bindProperty()
{
    BIND_PROPERTY(const Uri&, shader_uri, &setShaderUri, &getShaderUri);
    BIND_PROPERTY(const String&, technique, &setTechnique, &getTechnique);
}