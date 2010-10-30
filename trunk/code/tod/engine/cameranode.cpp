#include "tod/engine/cameranode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"
#include "tod/engine/shader.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(CameraNode, AbstractCameraNode);

//-----------------------------------------------------------------------------
CameraNode::CameraNode():
fov_(3.14f/4.0f), aspectRatio_(1.3333f), near_(0.1f), far_(1000.0f),
windowWidth_(0), windowHeight_(0)
{
    // empty

    ori_.identity();
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
    
    Renderer::instance()->setTransform(TRANSFORM_VIEW, view_);
    Renderer::instance()->setTransform(TRANSFORM_PROJECTION, projection_);
}


//-----------------------------------------------------------------------------
void CameraNode::moveForward(float dist)
{
    camera_.moveForward(dist);
}


//-----------------------------------------------------------------------------
void CameraNode::moveSideward(float dist)
{
    camera_.moveSideward(dist);
}


//-----------------------------------------------------------------------------
void CameraNode::rotate(float x, float y, float z)
{
    camera_.rotateYawPitchRoll(x, y, z);
    setTranslation(camera_.getPos());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateX(float angle)
{
    camera_.rotateYaw(angle);
    setTranslation(camera_.getPos());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateY(float angle)
{
    camera_.rotatePitch(angle);
    setTranslation(camera_.getPos());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::eulerRotateZ(float angle)
{
    camera_.rotateRoll(angle);
    setTranslation(camera_.getPos());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::onChangedWindowSize(int width, int height)
{
    if (windowWidth_ == width && windowHeight_ == height) return;

    aspectRatio_ =
        static_cast<float>(width) / 
        static_cast<float>(height);
    windowWidth_ = width;
    windowHeight_ = height;

    Renderer::instance()->onChangedWindowSize(width, height);
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
