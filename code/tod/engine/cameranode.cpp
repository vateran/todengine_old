#include "tod/engine/cameranode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/shader.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(CameraNode, AbstractCameraNode);

//-----------------------------------------------------------------------------
CameraNode::CameraNode():
fov_(3.14f/4.0f), aspectRatio_(1.3333f), near_(0.1f), far_(1000.0f)
{
    // empty
}


//-----------------------------------------------------------------------------
CameraNode::~CameraNode()
{   
    // empty
}


//-----------------------------------------------------------------------------
void CameraNode::renderCamera(SceneServer* scene_server)
{
    projection_.perspectiveFovLH(fov_, aspectRatio_, near_, far_);
    view_ = camera_.getMatrix();
    //view_.inverse();

    Renderer::instance()->setTransform(TRANSFORM_VIEW, view_);
    Renderer::instance()->setTransform(TRANSFORM_PROJECTION, projection_);
}


//-----------------------------------------------------------------------------
void CameraNode::moveForward(float dist)
{
    camera_.translateZ(dist);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::moveSideward(float dist)
{
    camera_.translateX(dist);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateX(float angle)
{
    camera_.rotateX(angle);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateY(float angle)
{
    camera_.rotateY(angle);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateZ(float angle)
{
    camera_.rotateZ(angle);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::onChangedWindowSize(int width, int height)
{
    aspectRatio_ =
        static_cast<float>(width) / 
        static_cast<float>(height);
}


//-----------------------------------------------------------------------------
bool CameraNode::hasCamera() const
{
    return true;
}


//-----------------------------------------------------------------------------
void CameraNode::bindProperty()
{
    BIND_PROPERTY(float, fov, &setFOV, &getFOV);
    BIND_PROPERTY(float, aspect_ratio, &setAspectRatio, &getAspectRatio);
    BIND_PROPERTY(float, near, &setNear, &getNear);
    BIND_PROPERTY(float, far, &setFar, &getFar);
}
