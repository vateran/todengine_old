#include "tod/engine/sceneview.h"

#include "tod/core/kernel.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/scenenode.h"
#include "tod/engine/sceneserver.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(SceneView, Node);

//-----------------------------------------------------------------------------
SceneView::SceneView():
windowId_(0)
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
void SceneView::setSceneRootPath(const Path& path)
{
    sceneRootPath_ = path;
    sceneContext_.setRootSceneNode(
        dynamic_cast<SceneNode*>(Kernel::instance()->lookup(sceneRootPath_)));
}


//-----------------------------------------------------------------------------
const Path& SceneView::getSceneRootPath() const
{
    return sceneRootPath_;
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
    camera_.translateZ(dst);
}


//-----------------------------------------------------------------------------
void SceneView::moveLeft(float dst)
{
    camera_.translateX(-dst);
}


//-----------------------------------------------------------------------------
void SceneView::moveRight(float dst)
{
    camera_.translateX(dst);
}


//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationX(float x)
{
    camera_.rotateX(x);
}

//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationY(float y)
{
    camera_.rotateY(y);
}


//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationZ(float z)
{
    camera_.rotateZ(z);
}


//-----------------------------------------------------------------------------
void SceneView::bindProperty()
{
    BIND_PROPERTY(
        const Path&, scene_root_path,
        &setSceneRootPath, &getSceneRootPath);
}
