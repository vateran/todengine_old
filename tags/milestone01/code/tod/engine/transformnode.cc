#include "tod/engine/transformnode.h"

#include "tod/core/assert.h"
#include "tod/engine/sceneserver.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/core/compositepropertybinder.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TransformNode, SceneNode);

//-----------------------------------------------------------------------------
TransformNode::TransformNode()
{
    setActive(true);
    setVisible(true);
}


//-----------------------------------------------------------------------------
TransformNode::~TransformNode()
{
    // empty
}


//-----------------------------------------------------------------------------
void TransformNode::attach
(SceneServer* scene_server, SceneContext* scene_context)
{
    tod_assert(scene_server);
    if (!isActive() || !isVisible())
        return;
    scene_server->beginGroup(this, scene_context);
    SceneNode::attach(scene_server, scene_context);
    scene_server->endGroup();
}


//-----------------------------------------------------------------------------
void TransformNode::renderTransform
(SceneServer* scene_server, SceneContext* scene_context,
 const Matrix44& parent_matrix)
{
    tod_assert(scene_server);
    tod_assert(scene_context);

    if (isLockViewer())
    {
        // handle lock to viewer
        /*const Matrix44& view = scene_server->getTransform(TRANSFORM_INVVIEW);
        Matrix44 m = transform_.getMatrix() * parent_matrix;
        m.m41_ = view.m41_;
        m.m42_ = view.m42_;
        m.m43_ = view.m43_;
        scene_server->setModelTransform(m);*/
    }
    else
    {
        // default case
        scene_server->setModelTransform(transform_.getMatrix() * parent_matrix);
    }
}


//-----------------------------------------------------------------------------
bool TransformNode::hasTransform() const
{
    return true;
}


//-----------------------------------------------------------------------------
bool TransformNode::checkFlags(const Flag& flag) const
{
    return flags_[flag];
}


//-----------------------------------------------------------------------------
bool TransformNode::isActive() const
{
    return checkFlags(ACTIVE);
}


//-----------------------------------------------------------------------------
bool TransformNode::isVisible() const
{
    return checkFlags(VISIBLE);
}


//-----------------------------------------------------------------------------
bool TransformNode::isLockViewer() const
{
    return checkFlags(LOCKVIEWER);
}


//-----------------------------------------------------------------------------
void TransformNode::setActive(bool v)
{
    flags_[ACTIVE] = v;
}


//-----------------------------------------------------------------------------
void TransformNode::setVisible(bool v)
{
    flags_[VISIBLE] = v;
}


//-----------------------------------------------------------------------------
void TransformNode::setLockViewer(bool v)
{
    flags_[LOCKVIEWER] = v;
}


//-----------------------------------------------------------------------------
void TransformNode::bindProperty()
{
    BIND_COMPOSITE_PROPERTY(
        const Vector3&, translation, &setTranslation, &getTranslation);
    BIND_COMPOSITE_PROPERTY(
        const Vector3&, euler_rotation, &setEulerRotation, &getEulerRotation);
    BIND_COMPOSITE_PROPERTY_FILED(
        euler_rotation, float, x, &setEulerRx, &getEulerRx);
    BIND_COMPOSITE_PROPERTY_FILED(
        euler_rotation, float, y, &setEulerRy, &getEulerRy);
    BIND_COMPOSITE_PROPERTY_FILED(
        euler_rotation, float, z, &setEulerRz, &getEulerRz);
    BIND_COMPOSITE_PROPERTY(
        const Vector3&, scaling, &setScaling, &getScaling);
}
