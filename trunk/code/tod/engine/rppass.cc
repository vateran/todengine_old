#include "tod/engine/rppass.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/rprendertarget.h"
#include "tod/engine/shader.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(RpPass, RpBase);

//-----------------------------------------------------------------------------
RpPass::RpPass():
clearDepthValue_(1.0f), clearStencilValue_(0)
{
    flags_[FLAG_CLEARCOLOR] = true;
    flags_[FLAG_CLEARDEPTH] = true;
    flags_[FLAG_CLEARSTENCIL] = true;
}


//-----------------------------------------------------------------------------
RpPass::~RpPass()
{
    // empty
}


//-----------------------------------------------------------------------------
uint32_t RpPass::begin()
{
    // invoke begin scene
    Renderer::instance()->beginScene();

    // change RenderTarget
    if (renderTarget_.valid())
        renderTarget_->begin();

    // clear RenderTarget
    Renderer::instance()->clearScene(
        clearColor_, clearDepthValue_, clearStencilValue_,
        flags_[FLAG_CLEARCOLOR], flags_[FLAG_CLEARDEPTH],
        flags_[FLAG_CLEARSTENCIL]);

    return RpBase::begin();
}


//-----------------------------------------------------------------------------
void RpPass::end()
{
    RpBase::end();

    // restore RenderTarget
    if (renderTarget_.valid())
          renderTarget_->end();

    // draw quad
    if (isDrawQuad())
        draw_quad();

    // invoke end scene
    Renderer::instance()->endScene();
}


//-----------------------------------------------------------------------------
void RpPass::draw_quad()
{
    if (renderTarget_.invalid())
        return;
    Shader* s = getShader();
    Renderer::instance()->setShader(s);
    if (0 == s)
        return;
    if (getTechnique().size())
        s->setTechnique(getTechnique());
    s->setTexture(STRING("DiffuseMap"), renderTarget_->getTexture());

    const DisplayMode& mode = Renderer::instance()->getDisplayMode();
    Matrix44 m, v, p;
    m.setTranslation(0, 0, 0);
    v.identity();
    p.orthogonalOffsetCenterLH(0, 0,
        static_cast<real_t>(mode.getWidth()),
        static_cast<real_t>(mode.getHeight()), -10000, 10000);

    Renderer::instance()->setTransform(TRANSFORM_WORLD, m);
    Renderer::instance()->setTransform(TRANSFORM_VIEW, v);
    Renderer::instance()->setTransform(TRANSFORM_PROJECTION, p);

    uint32_t pass;
    s->begin(pass);
    for (uint32_t p = 0; p < pass; ++p)
    {
        s->beginPass(p);
        Renderer::instance()->drawQuad(
            Rect(0, 0,
                mode.getWidth(),
                mode.getHeight()),
                Color(255, 255, 255, 255));
        s->endPass();
    }
    
    s->end();
}


//-----------------------------------------------------------------------------
void RpPass::setClearColor(const Color& color)
{
    clearColor_ = color;
}


//-----------------------------------------------------------------------------
void RpPass::setClearDepthValue(float value)
{
    clearDepthValue_ = value;
}


//-----------------------------------------------------------------------------
void RpPass::setClearStencilValue(uint32_t value)
{
    clearStencilValue_ = value;
}


//-----------------------------------------------------------------------------
const Color& RpPass::getClearColor() const
{
    return clearColor_;
}


//-----------------------------------------------------------------------------
float RpPass::clearDepthValue() const
{
    return clearDepthValue_;
}


//-----------------------------------------------------------------------------
uint32_t RpPass::clearStencilValue() const
{
    return clearStencilValue_;
}


//-----------------------------------------------------------------------------
void RpPass::setDrawQuad(bool enable)
{
    flags_[FLAG_DRAWQUAD] = enable;
}


//-----------------------------------------------------------------------------
bool RpPass::isDrawQuad() const
{
    return flags_[FLAG_DRAWQUAD];
}


//-----------------------------------------------------------------------------
void RpPass::onAddNode(Node* node)
{
    if (renderTarget_.invalid())
    {
        RpRenderTarget* rt = dynamic_cast<RpRenderTarget*>(node);
        if (rt)
            renderTarget_ = rt;
    }
}


//-----------------------------------------------------------------------------
void RpPass::onRemoveNode(Node* node)
{
    RpRenderTarget* rt = dynamic_cast<RpRenderTarget*>(node);
    if (*renderTarget_ == rt)
        renderTarget_.release();
}


//-----------------------------------------------------------------------------
void RpPass::bindProperty()
{
    BIND_PROPERTY(bool, draw_quad, &setDrawQuad, &isDrawQuad);
    BIND_PROPERTY(const Color&, clear_color, &setClearColor, &getClearColor);
}
