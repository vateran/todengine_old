#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_CAMERANODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_CAMERANODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::CameraNode
    @brief 
*/

#include "tod/engine/camera.h"
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

        void moveForward(float dist);
        void moveSideward(float dist);

        void rotate(float x, float y, float z);

        void eulerRotateX(float angle);
        void eulerRotateY(float angle);
        void eulerRotateZ(float angle);

        void setFOV(float fov);
        float getFOV() const;
        void setAspectRatio(float aspect);
        float getAspectRatio() const;
        void setNear(float z);
        float getNear() const;
        void setFar(float z);
        float getFar() const;

        void onChangedWindowSize(int width, int height);

        static void bindMethod();
        static void bindProperty();

    private:
        Camera camera_;
        float fov_;
        float aspectRatio_;
        float near_;
        float far_;

        Vector3 pos_;
        Quaternion ori_;
    };

#include "tod/engine/cameranode.inl"

}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
