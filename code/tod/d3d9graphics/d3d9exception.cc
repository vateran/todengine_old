#include "tod/d3d9graphics/d3d9exception.h"

#include <d3d9.h>
#include "tod/core/exception.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
D3D9Exception::D3D9Exception
(long hresult, Exception& exception, const String& detail_description)
{
    String description;
    switch (hresult)
    {
    case D3DERR_WRONGTEXTUREFORMAT:
        description = STRING("Wrong texture format");
        break;
    case D3DERR_UNSUPPORTEDCOLOROPERATION:
        description = STRING("Unsupported color operation");
        break;
    case D3DERR_UNSUPPORTEDCOLORARG:
        description = STRING("Unsupported color argument");
        break;
    case D3DERR_UNSUPPORTEDALPHAOPERATION:
        description = STRING("Unsupported alpha operation");
        break;
    case D3DERR_UNSUPPORTEDALPHAARG:
        description = STRING("Unsupported alpha argument");
        break;
    case D3DERR_TOOMANYOPERATIONS:
        description = STRING("Too many operations");
        break;
    case D3DERR_CONFLICTINGTEXTUREFILTER:
        description = STRING("Conflicting texture filter");
        break;
    case D3DERR_UNSUPPORTEDFACTORVALUE:
        description = STRING("Unsupported factor value");
        break;
    case D3DERR_CONFLICTINGRENDERSTATE:
        description = STRING("Conflicting render state");
        break;
    case D3DERR_UNSUPPORTEDTEXTUREFILTER:
        description = STRING("Unsupported texture filter");
        break;
    case D3DERR_CONFLICTINGTEXTUREPALETTE:
        description = STRING("Conflicting texture palette");
        break;
    case D3DERR_DRIVERINTERNALERROR:
        description = STRING("Driver internal error");
        break;
    case D3DERR_NOTFOUND:
        description = STRING("Not found");
        break;
    case D3DERR_MOREDATA:
        description = STRING("More data");
        break;
    case D3DERR_DEVICELOST:
        description = STRING("Device lost");
        break;
    case D3DERR_DEVICENOTRESET:
        description = STRING("Device not reset");
        break;
    case D3DERR_NOTAVAILABLE:
        description = STRING("Not available");
        break;
    case D3DERR_OUTOFVIDEOMEMORY:
        description = STRING("Out of video memory");
        break;
    case D3DERR_INVALIDDEVICE:
        description = STRING("Invalid device");
        break;
    case D3DERR_INVALIDCALL:
        description = STRING("Invalid call");
        break;
    case D3DERR_DRIVERINVALIDCALL:
        description = STRING("Driver invalid call");
        break;
    case D3DERR_WASSTILLDRAWING:
        description = STRING("Was still drawing");
        break;
    default:
        description = STRING("Unknown error");
        break;
    }

    exception.setDescription(
        detail_description + STRING(" : ") + description );
    ExceptionManager::instance()->handle(exception);
}
