#ifndef TOD_D3D9GRAPHICS_EXCEPTION_D3D9EXCEPTION_H
#define TOD_D3D9GRAPHICS_EXCEPTION_D3D9EXCEPTION_H

#include "tod/core/exception.h"
#include "tod/core/string.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    enum 
    {
        D3D9GRAPHICSEXCEPTIONCODE = 1000,

        D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3D9,
        D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3D9DEVICE,
        D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3D9EFFECTPOOL,
        D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3DSPRITE,
        D3D9GRAPHICSEXCEPTIONCODE_COULDNOTREGISTERWINDOW,
        D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATEWINDOW,
        D3D9GRAPHICSEXCEPTIONCODE_TITLEISEMPTY,
        D3D9GRAPHICSEXCEPTIONCODE_D3D9EFFECTCOMPILATIONERROR,
        D3D9GRAPHICSEXCEPTIONCODE_D3DXCREATETEXTUREFROMFILEINMEMORYEXERROR,
        D3D9GRAPHICSEXCEPTIONCODE_OUTOFVIDEOMEMOTY,
        D3D9GRAPHICSEXCEPTIONCODE_OUTOFMEMORY,
        D3D9GRAPHICSEXCEPTIONCODE_INVALIDCALL,
        D3D9GRAPHICSEXCEPTIONCODE_CREATETEXTUREERROR,
        D3D9GRAPHICSEXCEPTIONCODE_CREATEVERTEXBUFFERERROR,
    };

    class D3D9Exception
    {
    public:
        D3D9Exception(
            long hresult,
            core::Exception& exception,
            const core::String& detail_description);
    };

#define THROW_D3D9EXCEPTION(code, hr, desc) do {\
    tod::core::Exception e(\
        code, ___LINE___, ___FILE___, ___FUNCTION___, STRING(""));\
        D3D9Exception(hr, e, desc); } while (0);
}
}
}

#endif // TOD_D3D9GRAPHICS_EXCEPTION_D3D9EXCEPTION_H
