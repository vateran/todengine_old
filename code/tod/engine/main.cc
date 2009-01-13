#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"

#include "tod/core/define.h"
#include "tod/core/module.h"
#include "tod/core/kernel.h"
#include "tod/core/tostring.h"

#include "tod/engine/triggerserver.h"
#include "tod/engine/timeserver.h"
#include "tod/engine/renderer.h"
#include "tod/engine/sceneserver.h"
#include "tod/engine/sceneview.h"
#include "tod/engine/scenenode.h"
#include "tod/engine/transformnode.h"
#include "tod/engine/shadernode.h"
#include "tod/engine/meshnode.h"
#include "tod/engine/cameranode.h"
#include "tod/engine/renderpath.h"
#include "tod/engine/rpbase.h"
#include "tod/engine/rpsection.h"
#include "tod/engine/rppass.h"
#include "tod/engine/rprendertarget.h"
#include "tod/engine/timenode.h"
#include "tod/engine/terrainnode.h"
#include "tod/engine/treenode.h"
#include "tod/engine/quadtree.h"

#include "tod/engine/formatstringconverter.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
void initialize_Engine(Module* module)
{
    REGISTER_TYPE(module, TriggerServer);
    REGISTER_TYPE(module, TimeServer);;
    REGISTER_TYPE(module, SceneServer);
    REGISTER_TYPE(module, SceneView);
    REGISTER_TYPE(module, SceneNode);
    REGISTER_TYPE(module, TransformNode);
    REGISTER_TYPE(module, AbstractShaderNode);
    REGISTER_TYPE(module, AbstractCameraNode);
    REGISTER_TYPE(module, ShaderNode);
    REGISTER_TYPE(module, MeshNode);
    REGISTER_TYPE(module, CameraNode);
    REGISTER_TYPE(module, RenderPath);
    REGISTER_TYPE(module, RpBase);
    REGISTER_TYPE(module, RpSection);
    REGISTER_TYPE(module, RpPass);
    REGISTER_TYPE(module, RpRenderTarget);
    REGISTER_TYPE(module, TimeNode);
    REGISTER_TYPE(module, TerrainNode);
    REGISTER_TYPE(module, TreeNode);
    REGISTER_TYPE(module, QuadTree::Element);
    
    TimeServer::setSingletonPath(STRING("/sys/server/time"));
    Renderer::setSingletonPath(STRING("/sys/server/renderer"));
    RenderPath::setSingletonPath(STRING("/sys/server/renderpath"));
    SceneServer::setSingletonPath(STRING("/sys/server/scene"));

    static FormatStringConverter format_sc;
    ToString::instance()->addConverter(&format_sc);

    ShaderParamTypeEnumerationInitializer::initialize();

    ilInit();
}


//-----------------------------------------------------------------------------
void finalize_Engine(Module* module)
{
    ilShutDown();
}


//-----------------------------------------------------------------------------
DECLARE_MODULE(Engine);
