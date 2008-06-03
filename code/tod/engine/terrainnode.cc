#include "tod/engine/terrainnode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"

using namespace tod::core;
using namespace tod::engine::graphics;

IMPLEMENT_CLASS(TerrainNode, ShapeNode);

//-----------------------------------------------------------------------------
TerrainNode::TerrainNode()
{
    // empty
}


//-----------------------------------------------------------------------------
TerrainNode::~TerrainNode()
{
    // empty
}


//-----------------------------------------------------------------------------
void TerrainNode::applyGeometry(SceneServer* scene_server)
{
    // empty
}



//-----------------------------------------------------------------------------
void TerrainNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{
    ts_.render();
}


//-----------------------------------------------------------------------------
bool TerrainNode::loadResource()
{
    super::loadResource();

    if (vbUri_.size() && heightMapUri_.size())
    {
    }
    
    return true;
}


//-----------------------------------------------------------------------------
void TerrainNode::unloadResource()
{
    super::unloadResource();
}


//-----------------------------------------------------------------------------
bool TerrainNode::hasGeometry() const
{
    return true;
}


//-----------------------------------------------------------------------------
void TerrainNode::setVBUri(const Uri& uri)
{
    vbUri_ = uri;
    unloadResource();
}


//-----------------------------------------------------------------------------
const Uri& TerrainNode::getVBUri() const
{
    return vbUri_;
}


//-----------------------------------------------------------------------------
void TerrainNode::setHeightMapUri(const Uri& uri)
{
    heightMapUri_ = uri;
    unloadResource();
}


//-----------------------------------------------------------------------------
const Uri& TerrainNode::getHeightMapUri() const
{
    return heightMapUri_;
}


//-----------------------------------------------------------------------------
void TerrainNode::bindProperty()
{
    BIND_PROPERTY(const Uri&, vb_uri, &setVBUri, &getVBUri);
    BIND_PROPERTY(const Uri&, heightmap_uri, &setHeightMapUri, &getHeightMapUri);
    BIND_PROPERTY(int, lod, &setLOD, &getLOD);
}
