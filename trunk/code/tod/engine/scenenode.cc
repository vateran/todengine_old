#include "tod/engine/scenenode.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(SceneNode, Node);

//-----------------------------------------------------------------------------
SceneNode::SceneNode():
resourceValid_(false)
{
    // empty
}


//-----------------------------------------------------------------------------
SceneNode::~SceneNode()
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneNode::attach
(SceneServer* scene_server, SceneContext* scene_context)
{
    SceneNode* child;
    for (NodeIterator i = firstChildNode(); i != lastChildNode(); ++i)
    {
        child = i->second;
        if (0 == child)
            continue;
        child->attach(scene_server, scene_context);
    }
}


//-----------------------------------------------------------------------------
bool SceneNode::loadResource()
{
    // empty
    resourceValid_ = true;
    return true;
}


//-----------------------------------------------------------------------------
void SceneNode::unloadResource()
{
    // empty
    resourceValid_ = false;
}


//-----------------------------------------------------------------------------
void SceneNode::renderTransform
(SceneServer* scene_server, SceneContext* scene_context,
 const Matrix44& parent_matrix)
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneNode::applyShader(SceneServer* scene_server)
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneNode::renderShader
(SceneServer* scene_server, SceneContext* scene_context)
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneNode::applyGeometry(SceneServer* scene_server)
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneNode::renderCamera(SceneServer* scene_server)
{
    // empty
}


//-----------------------------------------------------------------------------
bool SceneNode::hasTransform() const
{
    return false;
}


//-----------------------------------------------------------------------------
bool SceneNode::hasShader() const
{
    return false;
}


//-----------------------------------------------------------------------------
bool SceneNode::hasGeometry() const
{
    return false;
}


//-----------------------------------------------------------------------------
bool SceneNode::hasCamera() const
{
    return false;
}
