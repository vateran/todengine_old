#include "tod/engine/terrainsection.h"

#include "tod/core/math.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
TerrainSection::TerrainSection():
maxLOD_(0), split_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
TerrainSection::~TerrainSection()
{
    // empty
}


//-----------------------------------------------------------------------------
void TerrainSection::build(const Uri& uri, const Vector3& scale, int split)
{
    split_ = split;

    build_tile(uri, scale);

    // compute max lod level
    maxLOD_ = compute_max_lod_level(
        tod_min(hmap_.width(), hmap_.height()), split_);

    build_index(hmap_.width(), hmap_.height(), maxLOD_, split_);
}


//-----------------------------------------------------------------------------
#include <bitset>
void TerrainSection::render()
{
    if (vb_.invalid() || vb_->invalid())
        return;

    vb_->use();

    // get view transform matrix
    Matrix44 v = Renderer::instance()->getTransform(TRANSFORM_VIEW);
    v.inverse();
    Vector3 camera_pos = v.getTranslation();

    // compute Level of Details for each tiles in TerrainSection
    int i = 0;

    for (Tiles::iterator tile = tiles_.begin();
         tile != tiles_.end(); ++tile)
         //tile->computeLOD(Vector3(-32, 0, -32), maxLOD_, hmap_.width() / split_);
         tile->computeLOD(camera_pos, maxLOD_, hmap_.width() / split_);

    for (int h = 0; h < split_; ++h)
    {
        for (int w = 0; w < split_; ++w)
        {
            TerrainTile& tile = tiles_[h * split_ + w];

            std::bitset<4> flag;
            if (w && tiles_[h * split_ + w - 1].detailLevel_ < tile.detailLevel_)
                flag.set(TerrainTile::SIDE_LEFT);
            if (w < (split_ - 1) && tiles_[h * split_ + w + 1].detailLevel_ < tile.detailLevel_)
                flag.set(TerrainTile::SIDE_RIGHT);
            if (h && tiles_[(h - 1) * split_ + w].detailLevel_ < tile.detailLevel_)
                flag.set(TerrainTile::SIDE_TOP);
            if (h < (split_ - 1) && tiles_[(h + 1) * split_ + w].detailLevel_ < tile.detailLevel_)
                flag.set(TerrainTile::SIDE_BOTTOM);

            if (flag.any())
            {
                int side = 0;
                if (flag.test(TerrainTile::SIDE_TOP))
                {
                    if (flag.test(TerrainTile::SIDE_LEFT))
                        side = TerrainTile::SIDE_TOPLEFT;
                    else if (flag.test(TerrainTile::SIDE_RIGHT))
                        side = TerrainTile::SIDE_TOPRIGHT;
                    else
                        side = TerrainTile::SIDE_TOP;
                }
                else if (flag.test(TerrainTile::SIDE_BOTTOM))
                {
                    if (flag.test(TerrainTile::SIDE_LEFT))
                        side = TerrainTile::SIDE_BOTTOMLEFT;
                    else if (flag.test(TerrainTile::SIDE_RIGHT))
                        side = TerrainTile::SIDE_BOTTOMRIGHT;
                    else
                        side = TerrainTile::SIDE_BOTTOM;
                }
                else if (flag.test(TerrainTile::SIDE_LEFT))
                    side = TerrainTile::SIDE_LEFT;
                else if (flag.test(TerrainTile::SIDE_RIGHT))
                    side = TerrainTile::SIDE_RIGHT;
                else
                {
                    tod_assert(0);
                }

                tile.cibs_[side][tile.detailLevel_]->use();
                tile.cibs_[side][tile.detailLevel_]->draw(PRIMITIVETYPE_TRIANGLESTRIP);
            }
            else
            {
                tile.ibs_[tile.detailLevel_]->use();
                tile.ibs_[tile.detailLevel_]->draw(PRIMITIVETYPE_TRIANGLESTRIP);
            }
        }
    }
}

//-----------------------------------------------------------------------------
void TerrainSection::build_index(int col, int row, int max_lod, int split)
{   
    int x = 0;
    int y = 0;
    int advance_x1 = col / split;
    int advance_y1 = row / split;
    float advance_x2 = static_cast<float>(col - 1) / split;
    float advance_y2 = static_cast<float>(row - 1) / split;
    float rx = static_cast<float>(col / 2);
    float ry = static_cast<float>(row / 2);

    tiles_.resize(split * split);
    
    int i = 0;
    for (float h = ry - (advance_y2 / 2); h >= -ry; h -= advance_y2, ++i)
    {
        int j = 0;
        for (float w = -rx + (advance_x2 / 2); w < rx; w += advance_x2, ++j)
        {   
            TerrainTile& tile = tiles_[i * split + j];

            tile.build(max_lod, split, Vector3(w, 0, h), col, row, x, y);

            x += advance_x1;
            if (x >= col - 1)
            {
                x = 0;
                y += advance_y1;
            }
        }
    }
}


//-----------------------------------------------------------------------------
bool TerrainSection::build_tile(const Uri& uri, const Vector3& scale)
{
    if (vb_.invalid())
        vb_ = Renderer::instance()->newVertexBuffer();

    // load height map image
    hmap_.setUri(uri);
    if (!hmap_.preload())
        return false;

    vb_->destroy();
    vb_->create(hmap_.width() * hmap_.height(),
        VERTEXCOMPONENT_COORD  |
        VERTEXCOMPONENT_NORMAL |
        VERTEXCOMPONENT_UV0, 0);

    struct Vertex
    {
        Vector3 coord_;
        Vector3 normal_;
        float u_, v_;
    };

    Vertex* vbptr = 0;
    if (!vb_->lock((void*&)vbptr))
        return false;

    float width = static_cast<float>(hmap_.width());
    float height = static_cast<float>(hmap_.height());
    for (int h = 0; h < hmap_.height(); ++h)
    {
        for (int w = 0; w < hmap_.width(); ++w)
        {
            Color c = hmap_.getPixel(w, h);

            vbptr->coord_.x_ = (w - width / 2) * scale.x_;
            vbptr->coord_.z_ = -(h - height / 2) * scale.z_;
            vbptr->coord_.y_ = c.r_ * scale.y_;

            vbptr->normal_ = vbptr->coord_;
            vbptr->normal_.normalize();

            vbptr->u_ = w / width;
            vbptr->v_ = h / height;

            ++vbptr;
        }
    }

    vb_->unlock();
    return true;
}


//-----------------------------------------------------------------------------
int TerrainSection::compute_max_lod_level(int size, int split)
{
    int max_lod = 1;
    size /= split;
    for (; size > 1; ++max_lod, size /= 2);
    return max_lod;
}
