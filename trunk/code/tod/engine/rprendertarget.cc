#include "tod/engine/rprendertarget.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/texture.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(RpRenderTarget, Node);

//-----------------------------------------------------------------------------
RpRenderTarget::RpRenderTarget():
relativeSize_(1)
{
    // empty
}


//-----------------------------------------------------------------------------
RpRenderTarget::~RpRenderTarget()
{
    // empty
}


//-----------------------------------------------------------------------------
void RpRenderTarget::create_texture()
{
    texture_.release();
    texture_ = Renderer::instance()->newTexture(getTextureUri());
    if (texture_.invalid())
        return;
    texture_->destroy();

    const DisplayMode& mode = Renderer::instance()->getDisplayMode();
    int w = static_cast<int>(mode.getWidth() * getRelativeSize());
    int h = static_cast<int>(mode.getHeight() * getRelativeSize());
    if (!texture_->create(w, h, 1, getFormat(), USAGE_RENDERTARGET))
        return;
}


//-----------------------------------------------------------------------------
void RpRenderTarget::begin()
{
    if (texture_.invalid())
        create_texture();
    if (texture_.valid())
        Renderer::instance()->pushRenderTarget(texture_);
}


//-----------------------------------------------------------------------------
void RpRenderTarget::end()
{
    if (texture_.valid())
        Renderer::instance()->popRenderTarget();
}


//-----------------------------------------------------------------------------
void RpRenderTarget::setAlias(const Name& alias)
{
    alias_ = alias;
}


//-----------------------------------------------------------------------------
const Name& RpRenderTarget::getAlias() const
{
    return alias_;
}


//-----------------------------------------------------------------------------
void RpRenderTarget::setTextureUri(const Uri& uri)
{
    uri_ = uri;
    texture_.release();
}


//-----------------------------------------------------------------------------
const Uri& RpRenderTarget::getTextureUri() const
{
    return uri_;
}


//-----------------------------------------------------------------------------
void RpRenderTarget::setFormat(const Format& format)
{
    format_ = format;
    texture_.release();
}


//-----------------------------------------------------------------------------
const Format& RpRenderTarget::getFormat() const
{
    return format_;
}


//-----------------------------------------------------------------------------
void RpRenderTarget::setRelativeSize(float s)
{
    relativeSize_ = s;
    texture_.release();
}


//-----------------------------------------------------------------------------
float RpRenderTarget::getRelativeSize() const
{
    return relativeSize_;
}


//-----------------------------------------------------------------------------
Texture* RpRenderTarget::getTexture()
{
    return texture_;
}


//-----------------------------------------------------------------------------
void RpRenderTarget::bindProperty()
{
    BIND_PROPERTY(float, relative_size, &setRelativeSize, &getRelativeSize);
    BIND_PROPERTY(const Name&, alias, &setAlias, &getAlias);
    BIND_PROPERTY(const Uri&, texture_uri, &setTextureUri, &getTextureUri);
    BIND_PROPERTY(const Format&, texture_format, &setFormat, &getFormat);
}
