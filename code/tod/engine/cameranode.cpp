#include "tod/engine/cameranode.h"

#include "tod/engine/renderer.h"
#include "tod/engine/shader.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(CameraNode, AbstractCameraNode);

//-----------------------------------------------------------------------------
CameraNode::CameraNode()
{

}


//-----------------------------------------------------------------------------
CameraNode::~CameraNode()
{

}


//-----------------------------------------------------------------------------
void CameraNode::renderCamera(SceneServer* scene_server)
{
    projection_.perspectiveFovLH(3.14f/4.0f, 1.0f, 1.0f, 10000.0f);
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
void CameraNode::moveLeft(float dist)
{
    camera_.translateX(-dist);
    setTranslation(camera_.getEye());
    setTransform(camera_.getMatrix());
}


//-----------------------------------------------------------------------------
void CameraNode::moveRight(float dist)
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
bool CameraNode::hasCamera() const
{
    return true;
}
