#ifndef TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
#define TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::graphics::SceneView
    @brief 
*/

#include <vector>
#include "tod/core/transform44.h"
#include "tod/core/matrix44.h"
#include "tod/core/object.h"
#include "tod/core/path.h"
#include "tod/engine/scenecontext.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class SceneServer;
    class SceneView : public core::Object
    {
    public:
        SceneView();
        virtual~SceneView();
        DECLARE_CLASS(SceneView, core::Object);

        void render(SceneServer* scene_server);

        void setSceneRootPath(const core::Path& path);
        const core::Path& getSceneRootPath() const;
        void setWindowId(int window_id);
        int getWindowId() const;

        void viewEulerRotationX(float x);
        void viewEulerRotationY(float y);
        void viewEulerRotationZ(float z);

        static void bindMethod();
        static void bindProperty();

    private:
        int windowId_;
        core::Path sceneRootPath_;
        SceneContext sceneContext_;
        core::Transform44 view_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_SCENEVIEW_H
