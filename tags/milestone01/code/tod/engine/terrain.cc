#include "tod/engine/terrain.h"

#include <bitset>
#include "tod/core/math.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
Terrain::Terrain():
col_(0), row_(0), split_(0), maxLOD_(0)
{
    // empty    
}


//-----------------------------------------------------------------------------
Terrain::~Terrain()
{
    // empty
}


//-----------------------------------------------------------------------------
void Terrain::build(int col, int row, int tile_size)
{
    col_ = col;
    row_ = row;

    split_ = col / tile_size;
    if (split_ == 0)
        split_ = 1;

    // compute max level of detail
    maxLOD_ = compute_max_lod_level(tod_min(col, row), split_);

    qtree_.initialize(2,
        BBox(
            Vector3(0, 0, 0),
            Vector3(
                static_cast<float>(col / 2), 10,
                static_cast<float>(row_ / 2))));

    build_index(col, row, maxLOD_, split_);
}


//-----------------------------------------------------------------------------
void Terrain::draw(const Vector3& offset)
{
    // get view transform matrix
    Matrix44 v = Renderer::instance()->getTransform(TRANSFORM_VIEW);
    v.inverse();
    Vector3 look(v.m31_, v.m32_, v.m33_);
    //Vector3 camera_pos = ((look * 10) + v.getTranslation()) - offset;
    Vector3 camera_pos = v.getTranslation() - offset;

    // compute Level of Details for each tiles in Terrain
    for (Tiles::iterator tile = tiles_.begin();
        tile != tiles_.end(); ++tile)
        //tile->computeLOD(Vector3(-64, 0, -64), maxLOD_,
        tile->computeLOD(camera_pos, maxLOD_,
        static_cast<float>(col_ / split_));

    // render the terrain section
    for (int h = 0; h < split_; ++h)
    {
        for (int w = 0; w < split_; ++w)
        {
            TerrainTileElement& tile = tiles_[h * split_ + w];
            int cur_lod = tile.tile_.getLOD();

            TerrainTile::JunctionFlag flag;
            if (w && tiles_[h * split_ + w - 1].tile_.getLOD() < cur_lod)
                flag.set(TerrainTile::JUNCTION_LEFT);
            if (w < (split_ - 1) &&
                tiles_[h * split_ + w + 1].tile_.getLOD() < cur_lod)
                flag.set(TerrainTile::JUNCTION_RIGHT);
            if (h && tiles_[(h - 1) * split_ + w].tile_.getLOD() < cur_lod)
                flag.set(TerrainTile::JUNCTION_TOP);
            if (h < (split_ - 1) &&
                tiles_[(h + 1) * split_ + w].tile_.getLOD() < cur_lod)
                flag.set(TerrainTile::JUNCTION_BOTTOM);

            tile.flag_ = flag;
        }
    }

    qtree_.render(
        v *
        Renderer::instance()->getTransform(TRANSFORM_PROJECTION));
}

//-----------------------------------------------------------------------------
void Terrain::TerrainTileElement::render
(const Matrix44& view_proj, BBox::ClipStatus clip_status)
{
    tile_.draw(flag_);
}

//-----------------------------------------------------------------------------
void Terrain::build_index(int col, int row, int max_lod, int split)
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
            TerrainTileElement& tile = tiles_[i * split + j];

            tile.build(max_lod, split, Vector3(w, 0, h), col, row, x, y);

            qtree_.insert(&tile,
                BBox(Vector3(w, 0, h),
                    Vector3(
                        advance_x1 / 2.0f - tod_tiny, 0,
                        advance_y1 / 2.0f - tod_tiny)));

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
int Terrain::compute_max_lod_level(int size, int split)
{
    if (split == 0)
        return 0;
    int max_lod = 1;
    size /= split;
    for (; size > 1; ++max_lod, size /= 2);
    return max_lod;
}
