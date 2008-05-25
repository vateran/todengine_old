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
    if (vb_.invalid() || vb_->invalid())
        return;

    vb_->use();
    vb_->draw(PRIMITIVETYPE_TRIANGLESTRIP);
}


//-----------------------------------------------------------------------------
#include "tod/engine/texture.h"
bool TerrainNode::loadResource()
{
    super::loadResource();

    if (vbUri_.size() && heightMapUri_.size())
    {   
        // load height map texture
        ResourceRef<Texture> t =
            Renderer::instance()->
                newTexture(getHeightMapUri());
        if (t.invalid())
            return false;
        t->preload();

        // create new mesh
        vb_ = Renderer::instance()->newVertexBuffer(getVBUri());
        //vb_->create();
    }
    
    return true;
}


//-----------------------------------------------------------------------------
void TerrainNode::unloadResource()
{
    vb_.release();

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
}
