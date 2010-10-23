#include "tod/engine/rpbase.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(RpBase, Node);

//-----------------------------------------------------------------------------
RpBase::RpBase()
{
    // empty
}

//-----------------------------------------------------------------------------
RpBase::~RpBase()
{
    // empty
}


//-----------------------------------------------------------------------------
void RpBase::validate()
{
    for (NodeIterator i = firstChildNode(); i != lastChildNode(); ++i)
    {
        RpBase* rpbase = i->second;
        if (0 == rpbase)
            continue;
        rpbase->validate();
    }
}


//-----------------------------------------------------------------------------
uint32_t RpBase::begin()
{
    uint32_t num_pass;
    if (shader_.valid())
    {
        commit(shader_);
        if (getTechnique().size())
            shader_->setTechnique(getTechnique());
        shader_->begin(num_pass, true);
        Renderer::instance()->setShader(shader_);
        return num_pass;
    }
    return 0;
}


//-----------------------------------------------------------------------------
void RpBase::end()
{
    if (shader_.valid())
    {
        shader_->end();
    }
}


//-----------------------------------------------------------------------------
void RpBase::beginPass(uint32_t pass)
{
    if (shader_.valid())
    {
        shader_->beginPass(pass);
    }
}


//-----------------------------------------------------------------------------
void RpBase::endPass()
{
    if (shader_.valid())
    {
        shader_->endPass();
    }
}


//-----------------------------------------------------------------------------
void RpBase::setShaderUri(const Uri& uri)
{
    shaderUri_ = uri;
    shader_.release();
    shader_ = Renderer::instance()->newShader(uri);
    if (shader_.valid())
        shader_->preload();
}


//-----------------------------------------------------------------------------
const Uri& RpBase::getShaderUri() const
{
    return shaderUri_;
}


//-----------------------------------------------------------------------------
void RpBase::setTechnique(const String& t)
{
    technique_ = t;
}


//-----------------------------------------------------------------------------
const String& RpBase::getTechnique() const
{
    return technique_;
}


//-----------------------------------------------------------------------------
Shader* RpBase::getShader()
{
    return shader_;
}


//-----------------------------------------------------------------------------
void RpBase::bindProperty()
{
    BIND_PROPERTY(const Uri&, shader_uri, &setShaderUri, &getShaderUri);
    BIND_PROPERTY(const String&, technique, &setTechnique, &getTechnique);
}