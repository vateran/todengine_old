#ifndef TOD_ENGINE_GRAPHICS_SCENE_EDITORSCENEVIEW_H
#define TOD_ENGINE_GRAPHICS_SCENE_EDITORSCENEVIEW_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::EditorSceneView
    @brief 
*/

#include "tod/engine/sceneview.h"

namespace tod
{
namespace engine
{
    class SceneServer;
    class EditorSceneView : public SceneView
    {
    public:
        EditorSceneView();
        virtual~EditorSceneView();
        DECLARE_CLASS(EditorSceneView, SceneView);

        override void render(SceneServer* scene_server);

        static void bindMethod();
        static void bindProperty();

    private:
        void drawEditorView();

    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_EDITORSCENEVIEW_H
