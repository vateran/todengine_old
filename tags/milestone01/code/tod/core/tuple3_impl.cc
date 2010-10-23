#include "tod/core/tuple3_impl.h"

#ifdef __WIN32_
#include <d3dx9.h>
#endif

using namespace tod;

//-----------------------------------------------------------------------------
void Tuple3_Impl::transformCoord(void* tuple3, const Matrix44& m)
{
#ifdef __WIN32__
    D3DXVec3TransformCoord(
        reinterpret_cast<D3DXVECTOR3*>(tuple3),
        reinterpret_cast<CONST D3DXVECTOR3*>(tuple3),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
#else
#endif
}
