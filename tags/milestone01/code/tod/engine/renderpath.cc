#include "tod/engine/renderpath.h"

#include "tod/engine/rpsection.h"

using namespace tod;
using namespace tod::engine;

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
RpSection* RenderPath::findSection(const String& name)
{
    return dynamic_cast<RpSection*>(findChild(name));
}


//-----------------------------------------------------------------------------
void RenderPath::validate()
{
    for (NodeIterator i = firstChildNode(); i != lastChildNode(); ++i)
    {
        RpSection* section = i->second;
        if (0 == section)
            continue;
        section->validate();
    }
}
