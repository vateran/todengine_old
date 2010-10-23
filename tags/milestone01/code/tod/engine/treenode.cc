#include "tod/engine/treenode.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TreeNode, ShapeNode);

//-----------------------------------------------------------------------------
TreeNode::TreeNode()
{

}


//-----------------------------------------------------------------------------
TreeNode::~TreeNode()
{

}


//-----------------------------------------------------------------------------
void TreeNode::applyGeometry(SceneServer* scene_server)
{

}


//-----------------------------------------------------------------------------
void TreeNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{

}


//-----------------------------------------------------------------------------
bool TreeNode::loadResource()
{
    return true;
}


//-----------------------------------------------------------------------------
void TreeNode::unloadResource()
{

}


//-----------------------------------------------------------------------------
bool TreeNode::hasGeometry() const
{
    return true;
}
