#include "tod/engine/scenecontext.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
SceneContext::SceneContext():
    rootSceneNode_(0)
{
    transform_.identity();
}


//-----------------------------------------------------------------------------
SceneContext::~SceneContext()
{
    // empty
}

//-----------------------------------------------------------------------------
void SceneContext::setRootSceneNode(SceneNode* scene_node)
{
    rootSceneNode_ = scene_node;
}


//-----------------------------------------------------------------------------
SceneNode* SceneContext::getRootSceneNode()
{
    return rootSceneNode_;
}

//-----------------------------------------------------------------------------
void SceneContext::setTransform(const Matrix44& m)
{
    transform_ = m;
}


//-----------------------------------------------------------------------------
const Matrix44& SceneContext::getTransform() const
{
    return transform_;
}
