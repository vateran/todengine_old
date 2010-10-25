#include "tod/engine/sceneview.h"

#include "tod/core/kernel.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/scenenode.h"
#include "tod/engine/sceneserver.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(SceneView, Object);

//-----------------------------------------------------------------------------
SceneView::SceneView():
windowId_(0), root_(0), camera_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
SceneView::~SceneView()
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneView::render(SceneServer* scene_server)
{
    // render
    scene_server->beginScene();
    scene_server->attach(&sceneContext_);
    scene_server->endScene();
    scene_server->renderScene();
    scene_server->presentScene(getWindowId());
}

//-----------------------------------------------------------------------------
void SceneView::setSceneRoot(Node* root)
{
    root_ = root;
    sceneContext_.setRootSceneNode(
        dynamic_cast<SceneNode*>(root_));
}


//-----------------------------------------------------------------------------
Node* SceneView::getSceneRoot() const
{
    return root_;
}


//-----------------------------------------------------------------------------
void SceneView::setCamera(CameraNode* camera)
{
    camera_ = camera;
}


//-----------------------------------------------------------------------------
CameraNode* SceneView::getCamera() const
{
    return camera_;
}


//-----------------------------------------------------------------------------
void SceneView::setWindowId(int window_id)
{
    windowId_ = window_id;
}


//-----------------------------------------------------------------------------
int SceneView::getWindowId() const
{
    return windowId_;
}


//-----------------------------------------------------------------------------
void SceneView::pick(int x, int y, int w, int h)
{
    SceneServer::instance()->pick(x, y, w, h);
}


//-----------------------------------------------------------------------------
void SceneView::moveForward(float dst)
{
    camera_->moveForward(dst);
}


//-----------------------------------------------------------------------------
void SceneView::moveSideward(float dst)
{
    camera_->moveSideward(dst);
}


//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationX(float x)
{
    camera_->eulerRotateX(x);
}

//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationY(float y)
{
    camera_->eulerRotateY(y);
}


//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationZ(float z)
{
    camera_->eulerRotateZ(z);
}


//-----------------------------------------------------------------------------
void SceneView::bindProperty()
{
}
