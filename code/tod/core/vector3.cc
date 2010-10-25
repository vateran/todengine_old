#include "tod/core/vector3.h"

#include "tod/core/define.h"
#ifdef __WIN32__
#include <d3dx9.h>
#endif
#include "tod/core/math.h"

using namespace tod;

//-----------------------------------------------------------------------------
float Vector3::size() const
{
    return tod_sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}


//-----------------------------------------------------------------------------
void Vector3::cross(const Vector3& v)
{
#ifdef __WIN32__
    D3DXVec3Cross(
        reinterpret_cast<D3DXVECTOR3*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(&v));
#else
#endif
}


//-----------------------------------------------------------------------------
void Vector3::transformCoord(const Matrix44& m)
{
#ifdef __WIN32__
    D3DXVec3TransformCoord(
        reinterpret_cast<D3DXVECTOR3*>(this),
        reinterpret_cast<CONST D3DXVECTOR3*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
#else
#endif
}
