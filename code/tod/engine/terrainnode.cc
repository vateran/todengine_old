#include "tod/engine/terrainnode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

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
    ts_.use();
    tts_.draw();
}


//-----------------------------------------------------------------------------
bool TerrainNode::loadResource()
{
    super::loadResource();
    
    if (heightMapUri_.size())
    {
        int split = 8;
        ts_.build(heightMapUri_, Vector3(1, 1, 1), split);
        tts_.build(ts_.getWidth(), ts_.getHeight(), split);
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
