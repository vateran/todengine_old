#include "tod/core/define.h"
#include "tod/core/module.h"
#include "tod/core/kernel.h"
#include "tod/d3d9graphics/d3d9renderer.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
void initialize_D3D9Graphics(Module* module)
{
    REGISTER_TYPE(module, D3D9Renderer);
}

//-----------------------------------------------------------------------------
DECLARE_MODULE(D3D9Graphics);
