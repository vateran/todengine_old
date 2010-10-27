#ifndef TOD_CORE_TYPE_QUATERNION_H
#define TOD_CORE_TYPE_QUATERNION_H
/**
    @ingroup TodCoreType
    @class tod::Quaternion
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/tuple4.h"
#include "tod/core/vector3.h"

namespace tod
{
    class Quaternion : public Tuple4<real_t>
    {
    public:
        Quaternion();
        Quaternion(const Vector3& v);
        Quaternion(real_t x, real_t y, real_t z, real_t w);

        void identity();
        void normalize();
        void inverse();
        void rotationAxis(const Vector3& axis, float32_t angle);
        void rotationYawPitchRoll(real_t yaw, real_t pitch, real_t roll);
        //spherical linear interpolation
        void slerp(const Quaternion& target, float32_t t);

        Vector3 getVector3() const;

        const Quaternion& operator *= (const Quaternion& a);

    };
}

#endif // TOD_CORE_TYPE_QUATERNION_H
