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
        description = "Wrong texture format";
        break;
    case D3DERR_UNSUPPORTEDCOLOROPERATION:
        description = "Unsupported color operation";
        break;
    case D3DERR_UNSUPPORTEDCOLORARG:
        description = "Unsupported color argument";
        break;
    case D3DERR_UNSUPPORTEDALPHAOPERATION:
        description = "Unsupported alpha operation";
        break;
    case D3DERR_UNSUPPORTEDALPHAARG:
        description = "Unsupported alpha argument";
        break;
    case D3DERR_TOOMANYOPERATIONS:
        description = "Too many operations";
        break;
    case D3DERR_CONFLICTINGTEXTUREFILTER:
        description = "Conflicting texture filter";
        break;
    case D3DERR_UNSUPPORTEDFACTORVALUE:
        description = "Unsupported factor value";
        break;
    case D3DERR_CONFLICTINGRENDERSTATE:
        description = "Conflicting render state";
        break;
    case D3DERR_UNSUPPORTEDTEXTUREFILTER:
        description = "Unsupported texture filter";
        break;
    case D3DERR_CONFLICTINGTEXTUREPALETTE:
        description = "Conflicting texture palette";
        break;
    case D3DERR_DRIVERINTERNALERROR:
        description = "Driver internal error";
        break;
    case D3DERR_NOTFOUND:
        description = "Not found";
        break;
    case D3DERR_MOREDATA:
        description = "More data";
        break;
    case D3DERR_DEVICELOST:
        description = "Device lost";
        break;
    case D3DERR_DEVICENOTRESET:
        description = "Device not reset";
        break;
    case D3DERR_NOTAVAILABLE:
        description = "Not available";
        break;
    case D3DERR_OUTOFVIDEOMEMORY:
        description = "Out of video memory";
        break;
    case D3DERR_INVALIDDEVICE:
        description = "Invalid device";
        break;
    case D3DERR_INVALIDCALL:
        description = "Invalid call";
        break;
    case D3DERR_DRIVERINVALIDCALL:
        description = "Driver invalid call";
        break;
    case D3DERR_WASSTILLDRAWING:
        description = "Was still drawing";
        break;
    default:
        description = "Unknown error";
        break;
    }

    exception.setDescription(
        detail_description + " : " + description );
    ExceptionManager::instance()->handle(exception);
}
