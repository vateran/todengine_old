#include "tod/engine/abstractshadernode.h"

#include "tod/core/simplevariable.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/texture.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(AbstractShaderNode, TransformNode);

//-----------------------------------------------------------------------------
AbstractShaderNode::AbstractShaderNode():
renderPassIndex_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
AbstractShaderNode::~AbstractShaderNode()
{
    // empty
}


//-----------------------------------------------------------------------------
void AbstractShaderNode::addTexture(const Name& name, const Uri& uri)
{   
    // load texture
    Texture* texture = Renderer::instance()->newTexture(uri);
    if (0 == texture)
        return;
    texture->preload();

    // add shader parameter
    typedef SimpleVariable<Texture*> TextureVariable;
    TextureVariable* t = addShaderParam<Texture*>(name);
    *t = texture;
}


//-----------------------------------------------------------------------------
void AbstractShaderNode::addCubeTexture(const Name& name, const Uri& uri)
{
    // load texture
    Texture* texture = Renderer::instance()->newCubeTexture(uri);
    if (0 == texture)
        return;
    texture->preload();

    // add shader parameter
    typedef SimpleVariable<Texture*> TextureVariable;
    TextureVariable* t = addShaderParam<Texture*>(name);
    *t = texture;
}


//-----------------------------------------------------------------------------
void AbstractShaderNode::setRpPassIndex(int index)
{
    renderPassIndex_ = index;
}


//-----------------------------------------------------------------------------
int AbstractShaderNode::getRpPassIndex() const
{
    return renderPassIndex_;
}


//-----------------------------------------------------------------------------
void AbstractShaderNode::bindProperty()
{
    BIND_PROPERTY(int, rppass_index, &setRpPassIndex, &getRpPassIndex);
}
