#include "tod/engine/abstractshadernode.h"

#include "tod/core/simplevariable.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/texture.h"

using namespace tod;
using namespace tod::engine;

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
void AbstractShaderNode::setRpPass(const Name& name)
{

}


//-----------------------------------------------------------------------------
const Name& AbstractShaderNode::getRpPass() const
{
    static Name n;
    return n;
}


//-----------------------------------------------------------------------------
int AbstractShaderNode::getRpPassIndex() const
{
    return renderPassIndex_;
}


//-----------------------------------------------------------------------------
void AbstractShaderNode::bindProperty()
{
    BIND_PROPERTY(const Name&, rppass_name, &setRpPass, &getRpPass);
    BIND_PROPERTY(int, rppass_index, 0, &getRpPassIndex);
}
