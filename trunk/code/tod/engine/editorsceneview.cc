#include "tod/engine/editorsceneview.h"

#include "tod/engine/renderer.h"
#include "tod/engine/sceneserver.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(EditorSceneView, SceneView);

//-----------------------------------------------------------------------------
EditorSceneView::EditorSceneView()
{
    // empty
}


//-----------------------------------------------------------------------------
EditorSceneView::~EditorSceneView()
{
    // empty
}


//-----------------------------------------------------------------------------
void EditorSceneView::render(SceneServer* scene_server)
{
    scene_server->beginScene();
    scene_server->attach(&sceneContext_);    
    scene_server->endScene();
    scene_server->renderScene();
    drawEditorView();
    scene_server->presentScene(getWindowId());
}


//-----------------------------------------------------------------------------
void EditorSceneView::drawEditorView()
{
    Renderer::instance()->beginScene();

    Renderer::instance()->drawLine();

    Renderer::instance()->endScene();
}


//-----------------------------------------------------------------------------
void EditorSceneView::bindProperty()
{
}
