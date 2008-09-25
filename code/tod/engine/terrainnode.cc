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

    vb_->use();
    vb_->draw(PRIMITIVETYPE_TRIANGLELIST);
}


//-----------------------------------------------------------------------------
int tile_col = 33;
int tile_row = 33;
bool TerrainNode::loadResource()
{
    super::loadResource();
    
    if (heightMapUri_.size())
    {
        int tile_size = 32;        
        terrain_.build(tile_col, tile_row, tile_size);
        terrainSection_.build(tile_col, tile_row, Vector3(1, 1, 1));

        if (vb_.invalid())
            vb_ = Renderer::instance()->newVertexBuffer();
        vb_->destroy();
        vb_->create(3,
            VERTEXCOMPONENT_COORD  |
            VERTEXCOMPONENT_NORMAL |
            VERTEXCOMPONENT_COLOR, USAGE_DYNAMIC);
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
#include <windows.h>
void TerrainNode::pick(int x, int y)
{
    int screen_w = 531;
    int screen_h = 394;
    Matrix44 proj = Renderer::instance()->getTransform(TRANSFORM_PROJECTION);

    // compute the vector of the pick ray in screen space
    Vector3 v;
    v.x_ =  (((2.0f * x) / screen_w) - 1) / proj.m11_;
    v.y_ = -(((2.0f * y) / screen_h) - 1) / proj.m22_;
    v.z_ = 1.0f;

    
    // get the inverse view matrix
    const Matrix44 view = Renderer::instance()->getTransform(TRANSFORM_VIEW);
    const Matrix44 world = Renderer::instance()->getTransform(TRANSFORM_WORLD);
    Matrix44 wv = world * view;
    wv.inverse();
    
    Vector3 pick_ray_dir;
    pick_ray_dir.x_ = v.x_ * wv.m11_ + v.y_ * wv.m21_ + v.z_ * wv.m31_;
    pick_ray_dir.y_ = v.x_ * wv.m12_ + v.y_ * wv.m22_ + v.z_ * wv.m32_;
    pick_ray_dir.z_ = v.x_ * wv.m13_ + v.y_ * wv.m23_ + v.z_ * wv.m33_;

    Vector3 pick_ray_orig;
    pick_ray_orig.x_ = wv.m41_;
    pick_ray_orig.y_ = wv.m42_;
    pick_ray_orig.z_ = wv.m43_;

    TerrainTileSet::Tiles& tiles = terrain_.tiles_;

    struct Vertex
    {
        Vector3 coord_;
        Vector3 normal_;
        float u_, v_;
    };

    Vertex* vbptr = 0;
    terrainSection_.vb_->lock((void*&)vbptr);
    float min_dist = 1000000;

    Vertex* picked = 0;

    for (int h = 0; h < terrain_.split_; ++h)
    {
        for (int w = 0; w < terrain_.split_; ++w)
        {
            TerrainTile& tile = tiles[h * terrain_.split_ + w];
            IndexBuffer* ib = tile.ibs_[0];

            uint16_t* ibptr = 0;
            ib->lock((void*&)ibptr);

            for (uint32_t i = 0; i < ib->getNumIndices() - 2; ++i)
            {
                Vector3 v0 = vbptr[ibptr[i]].coord_;
                Vector3 v1 = vbptr[ibptr[i + 1]].coord_;
                Vector3 v2 = vbptr[ibptr[i + 2]].coord_;

                float dist, bary0, bary1;

                if (tod_intersect_triangle(
                        pick_ray_orig, pick_ray_dir,
                        v0, v1, v2, &dist, &bary0, &bary1) &&
                    min_dist > dist)
                {
                    min_dist = dist;
                    picked = &vbptr[ibptr[i]];
                }
            }

            ib->unlock();

        }
    }

    if (picked)
    {
        picked[0].coord_.y_ += 0.1f;
        //picked[0].coord_.y_ += 0.1f;
        //picked[2].coord_.y_ += 0.1f;

        /*struct Vertex2
        {
            Vector3 coord_;                        
            Vector3 normal_;
            Color diffuse_;
        };

        Vertex2* vbptr2 = 0;
        vb_->lock((void*&)vbptr2);
        vbptr2[0].coord_ = picked[0].coord_;
        vbptr2[0].normal_ = picked[0].normal_;
        vbptr2[0].diffuse_.set(255, 255, 255, 255);

        vbptr2[1].coord_ = picked[1].coord_;
        vbptr2[1].normal_ = picked[1].normal_;
        vbptr2[1].diffuse_.set(255, 255, 255, 255);

        vbptr2[2].coord_ = picked[2].coord_;
        vbptr2[2].normal_ = picked[2].normal_;
        vbptr2[2].diffuse_.set(255, 255, 255, 255);
        vb_->unlock();*/
    }

    terrainSection_.vb_->unlock();
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
