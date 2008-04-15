#ifndef TOD_ENGINE_GRAPHICS_SCENE_SCENECONTEXT_H
#define TOD_ENGINE_GRAPHICS_SCENE_SCENECONTEXT_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::graphics::SceneContext
    @brief 
*/

#include "tod/core/matrix44.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class SceneNode;
    class SceneContext
    {
    public:
        SceneContext();
        virtual~SceneContext();

        void setRootSceneNode(SceneNode* scene_node);
        SceneNode* getRootSceneNode();

        void setTransform(const core::Matrix44& m);
        const core::Matrix44& getTransform() const;

    private:
        SceneNode* rootSceneNode_;
        core::Matrix44 transform_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_SCENECONTEXT_H
