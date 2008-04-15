#include "tod/engine/cameranode.h"

#include "tod/engine/renderer.h"
#include "tod/engine/shader.h"

using namespace tod::core;
using namespace tod::engine::graphics;

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
    view_ = getTransform();
    view_.inverse();

    Renderer::instance()->setTransform(TRANSFORM_VIEW, view_);
    Renderer::instance()->setTransform(TRANSFORM_PROJECTION, projection_);
}


//-----------------------------------------------------------------------------
bool CameraNode::hasCamera() const
{
    return true;
}
