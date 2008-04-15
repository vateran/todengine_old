#include "tod/engine/renderer.h"

#include "tod/core/assert.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/shader.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_ABSTRACTCLASS(Renderer, Node);

//-----------------------------------------------------------------------------
Renderer::Renderer()
{   
    Matrix44 m;
    m.identity();
    for (int i = 0; i < TRANSFORM_MAX; ++i)
        matrixStack_[i].push(m);
}

//-----------------------------------------------------------------------------
Renderer::~Renderer()
{
    // empty
}


//-----------------------------------------------------------------------------
void Renderer::setTransform(Transform type, const Matrix44& m)
{
    tod_assert(type < TRANSFORM_MAX);
    while (matrixStack_[type].size())
        matrixStack_[type].pop();
    matrixStack_[type].push(m);
    set_transform(type, m);
}


//-----------------------------------------------------------------------------
const Matrix44& Renderer::getTransform(Transform type) const
{
    tod_assert(type < TRANSFORM_MAX);
    return matrixStack_[type].top();
}


//-----------------------------------------------------------------------------
void Renderer::pushTransform(Transform type, const Matrix44& m)
{
    tod_assert(type < TRANSFORM_MAX);
    matrixStack_[type].push(m);
    set_transform(type, m);
}


//-----------------------------------------------------------------------------
void Renderer::popTransform(Transform type)
{
    tod_assert(type < TRANSFORM_MAX);
    matrixStack_[type].pop();
    if (matrixStack_[type].size())
        set_transform(type, matrixStack_[type].top());
}


//-----------------------------------------------------------------------------
void Renderer::set_transform(Transform type, const Matrix44& m)
{
    Shader* shader = getShader();
    if (0 == shader)
        return;
    switch (type)
    {
    case TRANSFORM_WORLD:        
        {
            shader->setMatrix(STRING("WorldMatrix"), m);

            Matrix44 inv(m);
            inv.inverse(0);
            shader->setMatrix(STRING("InvWorldMatrix"), inv);
        }
        break;
    case TRANSFORM_VIEW:
        {
            shader->setMatrix(STRING("ViewMatrix"), m);

            Matrix44 inv(m);
            inv.inverse(0);
            shader->setMatrix(STRING("InvViewMatrix"), inv);

            inv = m;
            inv.m41_ = inv.m42_ = inv.m43_ = 0;
            inv.inverse(0);
            shader->setMatrix(STRING("RevViewMatrix"), inv);
        }
        break;
    case TRANSFORM_PROJECTION:
        shader->setMatrix(STRING("ProjectionMatrix"), m);
        break;
    }
    
    Matrix44 mv(getTransform(TRANSFORM_WORLD));
    mv *= getTransform(TRANSFORM_VIEW);
    shader->setMatrix(STRING("WorldViewMatrix"), mv);
    Matrix44 mvp(mv);
    mvp *= getTransform(TRANSFORM_PROJECTION);
    shader->setMatrix(STRING("WorldViewProjectionMatrix"), mvp);

    // inverse
    mv.inverse(0);
    shader->setMatrix(STRING("InvWorldViewMatrix"), mv);
    mvp.inverse(0);
    shader->setMatrix(STRING("InvWorldViewProjectionMatrix"), mvp);

    shader->commit();
}


//-----------------------------------------------------------------------------
const String& Renderer::getDisplayModeStr() const
{
    static String mode(getDisplayMode());
    return mode;
}


//-----------------------------------------------------------------------------
void Renderer::bindProperty()
{
    BIND_PROPERTY(const String&, display_mode, 0, &getDisplayModeStr);
}