#ifndef TOD_CORE_TYPE_MATRIX44_H
#define TOD_CORE_TYPE_MATRIX44_H
/**
    @ingroup TodCoreType
    @class tod::core::Matrix44
    @brief 4x4 Matrix
*/

#include "tod/core/primitivetype.h"
#include "tod/core/vector3.h"
#include "tod/core/vector4.h"
#include "tod/core/plane.h"
#include "tod/core/quaternion.h"

namespace tod
{
namespace core
{
    class Matrix44
    {
    public:
        Matrix44();

        void setTranslation(const Vector3& translation);
        void setTranslation(real_t x, real_t y, real_t z);
        void setEulerRotationAxis(const Vector3& rotation, real_t angle);
        void setEulerRotationAxis(real_t x, real_t y, real_t z, real_t angle);
        void setRotation(const Quaternion& q);
        void setScaling(const Vector3& scaling);
        void setScaling(real_t x, real_t y, real_t z);

        void translate(const Vector3& translation);
        void translate(real_t x, real_t y, real_t z);
        void scale(const Vector3& scaling);
        void scale(real_t x, real_t y, real_t z);
        void rotateX(real_t x);
        void rotateY(real_t y);
        void rotateZ(real_t z);
        void eulerRotate(real_t x, real_t y, real_t z);
        void rotateQuaternion(const Quaternion& q);

        real_t getTx() const;
        real_t getTy() const;
        real_t getTz() const;
        Vector3 getTranslation() const;

        void identity();
        bool isIdentity() const;
        void inverse(real_t* determinant=0);
        void transpose();
        float determinant();

        void multiply(const Matrix44& m);
        void multiplyTranspose(const Matrix44& m);
        Vector3 multiplyDivW(const Vector3& v) const;

        void lookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up);
        void lookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up);
        void orthogonalLH(real_t w, real_t h, real_t z_near, real_t z_far);
        void orthogonalRH(real_t w, real_t h, real_t z_near, real_t z_far);
        void orthogonalOffsetCenterLH(
            real_t l, real_t t, real_t r, real_t b,
            real_t z_near, real_t z_far);
        void orthogonalOffsetCenterRH(
            real_t l, real_t t, real_t r, real_t b,
            real_t z_near, real_t z_far);
        void perspectiveFovLH(
            real_t fov_y, real_t aspect_ratio, real_t z_near, real_t z_far);
        void perspectiveFovRH(
            real_t fov_y, real_t aspect_ratio, real_t z_near, real_t z_far);
        void perspectiveLH(real_t w, real_t h, real_t z_near, real_t z_far);
        void perspectiveRH(real_t w, real_t h, real_t z_near, real_t z_far);
        void perspectiveOffsetCenterLH(
            real_t l, real_t t, real_t r, real_t b,
            real_t z_near, real_t z_far);
        void perspectiveOffsetCenterRH(
            real_t l, real_t t, real_t r, real_t b,
            real_t z_near, real_t z_far);
        void reflect(const Plane& plane);
        void setRotateAxis(const Vector3& axis, real_t angle);
        void setRotateQuaternion(const Quaternion& quaternion);
        void setRotateX(real_t x);
        void setRotateY(real_t y);
        void setRotateZ(real_t z);
        void setRotateYawRollPitch(real_t yaw, real_t roll, real_t pitch);
        void scaling(const Vector3& scaling);
        void scaling(real_t x, real_t y, real_t z);
        void shadow(const Vector4& light, const Plane& plane);
        void transformation(
            const Vector3& scaling_center,
            const Quaternion& scaling_rotation,
            const Vector3& scaling,
            const Vector3& rotation_center,
            const Quaternion& rotation,
            const Vector3& translation);

        Matrix44 operator * (const Matrix44& lhs) const;
        Vector3 operator * (const Vector3& lhs) const;
        Vector4 operator * (const Vector4& lhs) const;
        Plane operator * (const Plane& lhs) const;
        void operator *= (const Matrix44& lhs);

    public:
        union
        {
            struct
            {
                real_t m11_, m12_, m13_, m14_;
                real_t m21_, m22_, m23_, m24_;
                real_t m31_, m32_, m33_, m34_;
                real_t m41_, m42_, m43_, m44_;
            };
            real_t a_[16];
            real_t m_[4][4];
        };
    };
}
}

#endif // TOD_CORE_TYPE_MATRIX44_H
