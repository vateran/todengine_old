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
#include "tod/core/path.h"
#include "tod/engine/camera.h"
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

        void setSceneRootPath(const Path& path);
        const Path& getSceneRootPath() const;
        void setWindowId(int window_id);
        int getWindowId() const;

        void pick(int x, int y);

        void moveForward(float dst);
        void moveLeft(float dst);
        void moveRight(float dst);

        void viewEulerRotationX(float x);
        void viewEulerRotationY(float y);
        void viewEulerRotationZ(float z);

        static void bindMethod();
        static void bindProperty();

    private:
        int windowId_;
        Path sceneRootPath_;
        SceneContext sceneContext_;
        Camera camera_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
