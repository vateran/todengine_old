#ifndef TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
#define TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::SceneView
    @brief 
*/

#include <vector>
#include "tod/core/transform44.h"
#include "tod/core/matrix44.h"
#include "tod/core/object.h"
#include "tod/core/node.h"
#include "tod/core/path.h"
#include "tod/engine/camera.h"
#include "tod/engine/cameranode.h"
#include "tod/engine/scenecontext.h"

namespace tod
{
namespace engine
{
    class SceneServer;
    class SceneView : public Object
    {
    public:
        SceneView();
        virtual~SceneView();
        DECLARE_CLASS(SceneView, Object);

        void render(SceneServer* scene_server);

        void setSceneRoot(Node* root);
        Node* getSceneRoot() const;
        void setCamera(CameraNode* camera);
        CameraNode* getCamera() const;
        void setWindowId(int window_id);
        int getWindowId() const;

        void pick(int x, int y, int w, int h);

        void moveForward(float dst);
        void moveSideward(float dst);

        void viewEulerRotationX(float x);
        void viewEulerRotationY(float y);
        void viewEulerRotationZ(float z);

        static void bindMethod();
        static void bindProperty();

    private:
        int windowId_;
        Node* root_;
        CameraNode* camera_;
        SceneContext sceneContext_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
