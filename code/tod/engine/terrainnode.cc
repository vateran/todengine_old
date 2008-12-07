#include "tod/engine/terrainnode.h"

#include "tod/core/math.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TerrainNode, ShapeNode);

//-----------------------------------------------------------------------------
TerrainNode::TerrainNode():
col_(33), row_(33), uvRepeat_(16)
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
bool TerrainNode::loadResource()
{
    super::loadResource();
    
    if (heightMapUri_.size())
    {
        int tile_size = 32;        
        terrain_.build(col_, row_, tile_size);
        terrainSection_.build(col_, row_, Vector3(1, 1, 1), uvRepeat_);
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
void TerrainNode::pick(int x, int y, int w, int h)
{   
}

struct Vertex
{
    Vector3 coord_;
    Vector3 normal_;
    float u_, v_;
};


//-----------------------------------------------------------------------------
void TerrainNode::pick(int x, int y, int w, int h, PickInfo* info)
{
    int screen_w = w;
    int screen_h = h;
    const Matrix44& proj = Renderer::instance()->getTransform(TRANSFORM_PROJECTION);

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
    float min_dist = 1000000;
    Vertex* picked = 0;

    Vertex* vbptr = 0;    
    terrainSection_.vb_->lock((void*&)vbptr);

    for (int h = 0; h < terrain_.split_; ++h)
    {
        for (int w = 0; w < terrain_.split_; ++w)
        {
            TerrainTile& tile = tiles[h * terrain_.split_ + w];
            IndexBuffer* ib = tile.ibs_[0];

            uint16_t* ibptr = 0;
            ib->lock((void*&)ibptr);

            for (uint32_t i = 0; i < ib->getNumIndices() - 3; ++i)
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
                    info->tile_ = &tile;
                    info->index_ = ibptr[i];
                }
            }

            ib->unlock();

        }
    }

    terrainSection_.vb_->unlock();
}


//-----------------------------------------------------------------------------
void TerrainNode::makeKernel(int radius, float strength, float softness)
{
    kernel_.resize(radius);
    for (int i = 0; i < radius; ++i)
        kernel_[i].resize(radius);

    int half = radius / 2;
    for (int y = -half; y < half + radius % 2; ++y)
    {
        for (int x = -half; x < half + radius % 2; ++x)
        {
            kernel_[y + half][x + half] = strength *
                static_cast<float>(
                    1 / (2 * 3.14 * softness * softness) *
                    tod_exp(-(x * x + y * y) / (2 * softness * softness)));
        }
    } 
}


//-----------------------------------------------------------------------------
void TerrainNode::raise(int x, int y, int w, int h)
{
    PickInfo pi;
    memset(&pi, 0, sizeof(PickInfo));

    pick(x, y, w, h, &pi);

    if (pi.tile_ == 0)
        return;

    Vertex* vbptr = 0;
    terrainSection_.vb_->lock((void*&)vbptr);

    int radius = kernel_.size();
    int half = radius / 2;
    for (int yy = -half; yy < half + radius % 2; ++yy)
    {
        for (int xx = -half; xx < half + radius % 2; ++xx)
        {
            int index = pi.index_ + yy * col_ + xx;
            if (index < 0 || index > col_ * row_)
                continue;
            vbptr[index].coord_.y_ += kernel_[yy + half][xx + half];
        }
    }

    terrainSection_.vb_->unlock();
}


//-----------------------------------------------------------------------------
void TerrainNode::lower(int x, int y, int w, int h)
{
    PickInfo pi;
    memset(&pi, 0, sizeof(PickInfo));

    pick(x, y, w, h, &pi);

    if (pi.tile_ == 0)
        return;

    Vertex* vbptr = 0;
    terrainSection_.vb_->lock((void*&)vbptr);

    int radius = kernel_.size();
    int half = radius / 2;
    for (int yy = -half; yy < half + radius % 2; ++yy)
    {
        for (int xx = -half; xx < half + radius % 2; ++xx)
        {
            int index = pi.index_ + yy * col_ + xx;
            if (index < 0 || index > col_ * row_)
                continue;
            vbptr[index].coord_.y_ -= kernel_[yy + half][xx + half];
        }
    }

    terrainSection_.vb_->unlock();
}


//-----------------------------------------------------------------------------
void TerrainNode::computeNormal()
{
    Vertex* vbptr = 0;
    terrainSection_.vb_->lock((void*&)vbptr);
    
    for (int h = 1; h < col_ - 1; ++h)
    {
        for (int w = 1; w < row_ - 1; ++w)
        {
            Vertex* v = vbptr + h * row_ + w;

            Vector3 v0 = v->coord_ - (v - 1)->coord_;
            Vector3 v1 = (v + row_)->coord_ - v->coord_;

            v->normal_ = v0;
            v->normal_.cross(v1);
            v->normal_.normalize();
        }
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
void TerrainNode::setTerrainSize(int s)
{
    col_ = s;
    row_ = s; 
    unloadResource();
}


//-----------------------------------------------------------------------------
int TerrainNode::getTerrainSize() const
{
    return col_;
}


//-----------------------------------------------------------------------------
void TerrainNode::setTexture(const Uri& uri)
{
    diffuseUri_ = uri;
    ShaderParams::setTexture(STRING("DiffuseMap"), uri);
}


//-----------------------------------------------------------------------------
const Uri& TerrainNode::getTexture() const
{
    return diffuseUri_;
}


//-----------------------------------------------------------------------------
void TerrainNode::bindProperty()
{
    BIND_PROPERTY(const Uri&, heightmap_uri, &setHeightMapUri, &getHeightMapUri);
    BIND_PROPERTY(const Uri&, diffuse_texture_uri, &setTexture, &getTexture);
    BIND_PROPERTY(int, uv_repeat, &setUVRepeat, &getUVRepeat);
    BIND_PROPERTY(int, terrain_size, &setTerrainSize, &getTerrainSize);
}
