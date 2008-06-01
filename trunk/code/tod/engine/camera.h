#ifndef TOD_ENGINE_GRAPHICS_CORE_CAMERA_H
#define TOD_ENGINE_GRAPHICS_CORE_CAMERA_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::Camera
    @brief 
*/

#include "tod/core/vector3.h"
#include "tod/core/matrix44.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Camera
    {
    public:
        Camera();

        void setView(
            const core::Vector3& eye,
            const core::Vector3& look,
            const core::Vector3& up);

        void setTranslation(const core::Vector3& v);
        void translateX(float dist);
        void translateY(float dist);
        void translateZ(float dist);

        void rotateX(float angle);
        void rotateY(float angle);
        void rotateZ(float angle);

        const core::Matrix44& getMatrix();

    private:
        core::Vector3 eye_;
        core::Vector3 at_;
        core::Vector3 up_;

        core::Vector3 view_;
        core::Vector3 cross_;

        core::Matrix44 viewMatrix_;
        core::Matrix44 invViewMatrix_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_CAMERA_H
