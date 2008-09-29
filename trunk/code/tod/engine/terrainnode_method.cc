#include "tod/engine/terrainnode.h"

#include "tod/core/methodbinder.h"
#include "tod/engine/sceneserver.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
static void TerrainNode_v_raiseTerrain_iiii(TerrainNode* self, Parameter* param)
{
    self->raise(
        param->in()->get<int>(0),
        param->in()->get<int>(1),
        param->in()->get<int>(2),
        param->in()->get<int>(3));
}


//-----------------------------------------------------------------------------
void TerrainNode::bindMethod()
{
    BIND_METHOD(v_raiseTerrain_iiii, TerrainNode_v_raiseTerrain_iiii);
  
}
