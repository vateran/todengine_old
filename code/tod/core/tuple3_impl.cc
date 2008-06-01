#include "tod/core/tuple3_impl.h"

#include <d3dx9.h>

using namespace tod::core;

//-----------------------------------------------------------------------------
void Tuple3_Impl::transformCoord(void* tuple3, const Matrix44& m)
{
    D3DXVec3TransformCoord(
        reinterpret_cast<D3DXVECTOR3*>(tuple3),
        reinterpret_cast<CONST D3DXVECTOR3*>(tuple3),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
}
