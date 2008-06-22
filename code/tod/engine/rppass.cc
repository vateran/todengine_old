#include "tod/engine/rppass.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/shader.h"
#include "tod/engine/texture.h"
#include "tod/engine/rprendertarget.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(RpPass, RpBase);

//-----------------------------------------------------------------------------
RpPass::RpPass():
clearDepthValue_(1.0f), clearStencilValue_(0)
{
    flags_[FLAG_CLEARTARGET] = true;
    flags_[FLAG_CLEARDEPTH] = true;
    flags_[FLAG_CLEARSTENCIL] = true;
}


//-----------------------------------------------------------------------------
RpPass::~RpPass()
{
    // empty
}


//-----------------------------------------------------------------------------
void RpPass::validate()
{
    // preload RenderTarget
    if (renderTarget_.valid())
        renderTarget_->preload();

    // recursive validate
    RpBase::validate();
}


//-----------------------------------------------------------------------------
uint32_t RpPass::begin()
{
    // change RenderTarget
    if (renderTarget_.valid())
        renderTarget_->begin();

    // invoke begin scene
    Renderer::instance()->beginScene();    

    // clear RenderTarget
    Renderer::instance()->clearScene(
        clearColor_, clearDepthValue_, clearStencilValue_,
        flags_[FLAG_CLEARTARGET], flags_[FLAG_CLEARDEPTH],
        flags_[FLAG_CLEARSTENCIL]);

    // apply shader (note: save/restore all shader state for pass shaders!)
    uint32_t num_pass = RpBase::begin();
    RpBase::beginPass(0);

    // draw full-screen quad
    if (isDrawQuad())
        draw_quad();

    return num_pass;
}


//-----------------------------------------------------------------------------
void RpPass::end()
{
    RpBase::endPass();
    RpBase::end();

    // invoke end scene
    Renderer::instance()->endScene();

    // restore RenderTarget
    if (renderTarget_.valid())
        renderTarget_->end();
}


//-----------------------------------------------------------------------------
void RpPass::draw_quad()
{   
    // setup screen width and height
    const DisplayMode& mode = Renderer::instance()->getDisplayMode();
    real_t sw = static_cast<real_t>(mode.getWidth());
    real_t sh = static_cast<real_t>(mode.getHeight());
    if (renderTarget_.valid())
    {
        sw *= renderTarget_->getRelativeSize();
        sh *= renderTarget_->getRelativeSize();
    }    

    // setup transforms
    Matrix44 m, v, p;
    m.setTranslation(0, 0, 0);
    v.identity();
    p.orthogonalOffsetCenterLH(0, 0, sw, sh, -10000, 10000);
    Renderer::instance()->setTransform(TRANSFORM_WORLD, m);
    Renderer::instance()->setTransform(TRANSFORM_VIEW, v);
    Renderer::instance()->setTransform(TRANSFORM_PROJECTION, p);

    // render quad
    Renderer::instance()->drawQuad(
        Rect(0, 0, static_cast<int>(sw), static_cast<int>(sh)),
            Color(255, 255, 255, 255));
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
void RpPass::setClearTarget(bool enable)
{
    flags_[FLAG_CLEARTARGET] = enable;
}


//-----------------------------------------------------------------------------
bool RpPass::isClearTarget() const
{
    return flags_[FLAG_CLEARTARGET];
}


//-----------------------------------------------------------------------------
void RpPass::setClearDepth(bool enable)
{
    flags_[FLAG_CLEARDEPTH] = enable;
}


//-----------------------------------------------------------------------------
bool RpPass::isClearDepth() const
{
    return flags_[FLAG_CLEARDEPTH];
}


//-----------------------------------------------------------------------------
void RpPass::setClearStencil(bool enable)
{
    flags_[FLAG_CLEARDEPTH] = enable;
}


//-----------------------------------------------------------------------------
bool RpPass::isClearStencil() const
{
    return flags_[FLAG_CLEARDEPTH];
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
    BIND_PROPERTY(float, clear_depth_value, &setClearDepthValue, &clearDepthValue);
    BIND_PROPERTY(uint32_t, clear_stencil_value,
        &setClearStencilValue, &clearStencilValue);
    BIND_PROPERTY(bool, clear_target, &setClearTarget, &isClearTarget);
    BIND_PROPERTY(bool, clear_depth, &setClearDepth, &isClearDepth);
    BIND_PROPERTY(bool, clear_stencil, &setClearStencil, &isClearStencil);
}
