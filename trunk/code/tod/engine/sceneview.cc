#include "tod/engine/sceneview.h"

#include "tod/core/kernel.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/scenenode.h"
#include "tod/engine/sceneserver.h"

using namespace tod::core;
using namespace tod::engine::graphics;

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
    // set scene view matrix
    sceneContext_.setTransform(view_.getMatrix());

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
void SceneView::viewEulerRotationX(float x)
{
    view_.eulerRotateX(x);
}

//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationY(float y)
{
    view_.eulerRotateY(y);
}


//-----------------------------------------------------------------------------
void SceneView::viewEulerRotationZ(float z)
{
    view_.eulerRotateZ(z);
}


//-----------------------------------------------------------------------------
void SceneView::bindProperty()
{
    BIND_PROPERTY(
        const Path&, scene_root_path,
        &setSceneRootPath, &getSceneRootPath);
}
