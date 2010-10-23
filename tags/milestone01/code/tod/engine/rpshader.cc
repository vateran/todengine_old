#include "tod/engine/rpshader.h"

#include "tod/engine/renderer.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(RpShader, Node);

//-----------------------------------------------------------------------------
RpShader::RpShader()
{
    // empty
}


//-----------------------------------------------------------------------------
RpShader::~RpShader()
{
    // empty
}


//-----------------------------------------------------------------------------
void RpShader::setShaderUri(const Uri& uri)
{
    uri_ = uri;
    shader_.release();
    shader_ = Renderer::instance()->newShader(uri_);
    if (shader_.valid())
        shader_->preload();
}


//-----------------------------------------------------------------------------
const Uri& RpShader::getShaderUri() const
{
    return uri_;
}


//-----------------------------------------------------------------------------
Shader* RpShader::getShader()
{
    return shader_;
}
