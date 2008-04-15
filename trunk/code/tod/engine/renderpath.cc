#include "tod/engine/renderpath.h"

#include "tod/engine/rpsection.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(RenderPath, Node);

//-----------------------------------------------------------------------------
RenderPath::RenderPath()
{
    // empty
}


//-----------------------------------------------------------------------------
RenderPath::~RenderPath()
{
    // empty
}


//-----------------------------------------------------------------------------
RpSection* RenderPath::findSection(const Name& name)
{
    return dynamic_cast<RpSection*>(findChild(name));
}
