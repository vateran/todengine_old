#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_CAMERANODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_CAMERANODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::CameraNode
    @brief 
*/

#include "tod/engine/abstractcameranode.h"

namespace tod
{
namespace engine
{
    class CameraNode : public AbstractCameraNode
    {
    public:
        CameraNode();
        virtual~CameraNode();
        DECLARE_CLASS(CameraNode, AbstractCameraNode);

        override void renderCamera(SceneServer* scene_server);
        override bool hasCamera() const;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
