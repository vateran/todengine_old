#include "tod/core/quaternion.h"

#include "tod/core/define.h"
#ifdef __WIN32__
#include <d3dx9.h>
#endif

using namespace tod;

//-----------------------------------------------------------------------------
Quaternion::Quaternion()
{
    // empty
}


//-----------------------------------------------------------------------------
Quaternion::Quaternion(const Vector3& v):
Tuple4<real_t>(v.x_, v.y_, v.x_, 1)
{
}


//-----------------------------------------------------------------------------
Quaternion::Quaternion(real_t x, real_t y, real_t z, real_t w):
Tuple4<real_t>(x, y, z, w)
{
}


//-----------------------------------------------------------------------------
void Quaternion::identity()
{
#ifdef __WIN32__
    D3DXQuaternionIdentity(reinterpret_cast<D3DXQUATERNION*>(this));
#else
#endif
}


//-----------------------------------------------------------------------------
void Quaternion::normalize()
{
#ifdef __WIN32__
    D3DXQuaternionNormalize(
        reinterpret_cast<D3DXQUATERNION*>(this),
        reinterpret_cast<const D3DXQUATERNION*>(this));
#else
#endif
}


//-----------------------------------------------------------------------------
void Quaternion::inverse()
{
#ifdef __WIN32__
    D3DXQuaternionInverse(
        reinterpret_cast<D3DXQUATERNION*>(this),
        reinterpret_cast<const D3DXQUATERNION*>(this));
#else
#endif
}


//-----------------------------------------------------------------------------
void Quaternion::rotationAxis(const Vector3& axis, float32_t angle)
{
#ifdef __WIN32__
    D3DXQuaternionRotationAxis(
        reinterpret_cast<D3DXQUATERNION*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(&axis),
        angle);
#else
#endif
}


//-----------------------------------------------------------------------------
void Quaternion::rotationYawPitchRoll(real_t yaw, real_t pitch, real_t roll)
{
#ifdef __WIN32__
    D3DXQuaternionRotationYawPitchRoll(
        reinterpret_cast<D3DXQUATERNION*>(this), yaw, pitch, roll);
#else
#endif
}


//-----------------------------------------------------------------------------
void Quaternion::slerp(const Quaternion& target, float32_t t)
{
#ifdef __WIN32__
    D3DXQuaternionSlerp(
        reinterpret_cast<D3DXQUATERNION*>(this),        
        reinterpret_cast<const D3DXQUATERNION*>(this),
        reinterpret_cast<const D3DXQUATERNION*>(&target),
        t);
#else
#endif
}


//-----------------------------------------------------------------------------
Vector3 Quaternion::getVector3() const
{
    return Vector3(x_, y_, z_);
}


//-----------------------------------------------------------------------------
const Quaternion& Quaternion::operator *= (const Quaternion& a)
{
#ifdef __WIN32__
    D3DXQuaternionMultiply(
        reinterpret_cast<D3DXQUATERNION*>(this),
        reinterpret_cast<const D3DXQUATERNION*>(this),
        reinterpret_cast<const D3DXQUATERNION*>(&a));
#else
#endif

    return *this;
}
