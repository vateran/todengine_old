#include "tod/engine/xfilenode.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(XFileNode, ShapeNode);

//-----------------------------------------------------------------------------
XFileNode::XFileNode()
{

}


//-----------------------------------------------------------------------------
XFileNode::~XFileNode()
{

}


//-----------------------------------------------------------------------------
void XFileNode::applyGeometry(SceneServer* scene_server)
{

}


//-----------------------------------------------------------------------------
void XFileNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{

}


//-----------------------------------------------------------------------------
bool XFileNode::loadResource()
{
    return true;
}


//-----------------------------------------------------------------------------
void XFileNode::unloadResource()
{

}


//-----------------------------------------------------------------------------
bool XFileNode::hasGeometry() const
{
    return true;
}
