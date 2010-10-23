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
static void TerrainNode_v_lower_iiii(TerrainNode* self, Parameter* param)
{
    self->lower(
        param->in()->get<int>(0),
        param->in()->get<int>(1),
        param->in()->get<int>(2),
        param->in()->get<int>(3));
}


//-----------------------------------------------------------------------------
static void TerrainNode_v_makeKernel_iff(TerrainNode* self, Parameter* param)
{
    self->makeKernel(
        param->in()->get<int>(0),
        param->in()->get<float>(1),
        param->in()->get<float>(2));
}


//-----------------------------------------------------------------------------
static void TerrainNode_v_computeNormal_v(TerrainNode* self, Parameter* param)
{
    self->computeNormal();
}


//-----------------------------------------------------------------------------
void TerrainNode::bindMethod()
{
    BIND_METHOD(v_raiseTerrain_iiii, TerrainNode_v_raiseTerrain_iiii);
    BIND_METHOD(v_lower_iiii, TerrainNode_v_lower_iiii);
    BIND_METHOD(v_makeKernel_iff, TerrainNode_v_makeKernel_iff);  
    BIND_METHOD(v_computeNormal_v, TerrainNode_v_computeNormal_v);  
}
