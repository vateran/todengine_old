#ifndef TOD_ENGINE_GRAPHICS_CORE_CAMERA_H
#define TOD_ENGINE_GRAPHICS_CORE_CAMERA_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::Camera
    @brief 
*/

#include "tod/core/vector3.h"
#include "tod/core/matrix44.h"

namespace tod
{
namespace engine
{
    class Camera
    {
    public:
        Camera();

        void setView(
            const Vector3& eye,
            const Vector3& look,
            const Vector3& up);

        void setTranslation(const Vector3& v);
        void translateX(float dist);
        void translateY(float dist);
        void translateZ(float dist);

        void rotateX(float angle);
        void rotateY(float angle);
        void rotateZ(float angle);

        const Vector3& getEye() const;

        const Matrix44& getMatrix();

    private:
        Vector3 eye_;
        Vector3 at_;
        Vector3 up_;

        Vector3 view_;
        Vector3 cross_;

        Matrix44 viewMatrix_;
        Matrix44 invViewMatrix_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_CAMERA_H
