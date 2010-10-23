#include "tod/core/define.h"
#include "tod/core/module.h"
#include "tod/core/kernel.h"
#include "tod/d3d9graphics/d3d9renderer.h"
#include "tod/d3d9graphics/xfilenode.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
void initialize_D3D9Graphics(Module* module)
{
    REGISTER_TYPE(module, D3D9Renderer);
    REGISTER_TYPE(module, XFileNode);
}


//-----------------------------------------------------------------------------
void finalize_D3D9Graphics(Module* module)
{

}


//-----------------------------------------------------------------------------
DECLARE_MODULE(D3D9Graphics);
