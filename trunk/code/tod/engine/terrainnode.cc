#include "tod/engine/terrainnode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TerrainNode, ShapeNode);

//-----------------------------------------------------------------------------
TerrainNode::TerrainNode():
col_(1), row_(1)
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
    terrainSection_.use();
    terrain_.draw(Vector3(0, 0, 0));
}


//-----------------------------------------------------------------------------
int tile_col = 65;
int tile_row = 65;
bool TerrainNode::loadResource()
{
    super::loadResource();
    
    if (heightMapUri_.size())
    {
        int tile_size = 32;        
        terrain_.build(tile_col, tile_row, tile_size);
        terrainSection_.build(tile_col, tile_row, Vector3(1, 1, 1));
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
    BIND_PROPERTY(const Uri&, heightmap_uri, &setHeightMapUri, &getHeightMapUri);
}
