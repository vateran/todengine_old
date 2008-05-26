#ifndef TOD_CORE_TYPE_VECTOR3_H
#define TOD_CORE_TYPE_VECTOR3_H
/**
    @ingroup TodCoreType
    @class tod::core::Vector3
    @brief
*/

#include "tod/core/tuple3.h"

namespace tod
{
namespace core
{

typedef Tuple3<float> Vector3;

//-----------------------------------------------------------------------------
inline Vector3 operator + (const Vector3& t1, const Vector3& t2)
{   
    return Vector3(t1.x_ + t2.x_, t1.y_ + t2.y_, t1.z_ + t2.z_);
}

//-----------------------------------------------------------------------------
inline Vector3 operator - (const Vector3& t1, const Vector3& t2)
{
    return Vector3(t1.x_ - t2.x_, t1.y_ - t2.y_, t1.z_ - t2.z_);
}

//-----------------------------------------------------------------------------
inline Vector3 operator * (const Vector3& v, float value)
{
    return Vector3(v.x_ * value, v.y_ * value, v.z_ * value);
}

}
}

#endif // TOD_CORE_TYPE_VECTOR3_H
