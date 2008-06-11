#include "tod/engine/terraintile.h"

#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
TerrainTile::TerrainTile():
detailLevel_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
TerrainTile::~TerrainTile()
{
    // empty
}


//-----------------------------------------------------------------------------
void TerrainTile::draw()
{

}


//-----------------------------------------------------------------------------
bool TerrainTile::build
(int max_lod, int split, const Vector3& center, int col, int row, int x, int y)
{
    center_ = center;

    ibs_.resize(max_lod);
    for (int side = 0; side < SIDE_MAX; ++side)
        cibs_[side].resize(max_lod);

    // choose index buffer format 
    Format format = Format::INDEX16;
    if (col * row > 65535)
        format = Format::INDEX32;

    int step = 1;
    for (int lod = 0; lod < max_lod; ++lod, step <<= 1)
    {
        float tw = static_cast<float>(col) / step / split;
        if (tw - static_cast<int>(tw) > 0)
            tw += 1;
        float th = static_cast<float>(row) / step / split;
        if (th - static_cast<int>(th) > 0)
            th += 1;
        int tile_width = static_cast<int>(tw);
        int tile_height = static_cast<int>(th);

        // compute number of index for tile
        int index_num = (tile_width * 2) * tile_height - tile_height - 2;
        if (index_num < 0)
            return 0;

        ResourceRef<IndexBuffer>& ib = ibs_[lod];
        if (ib.invalid())
            ib = Renderer::instance()->newIndexBuffer();
        if (ib->valid())
            ib->destroy();
        if (!ib->create(index_num, 0, format))
            continue;

        switch (format)
        {
        case Format::INDEX16:
            {
                uint16_t* ibptr = 0;
                if (!ib->lock((void*&)ibptr))
                    return false;
                build_index(ibptr, col, row, step,
                    x, y, tile_width, tile_height);
                ib->unlock();
                break;
            }
        case Format::INDEX32:
            {
                uint32_t* ibptr = 0;
                if (!ib->lock((void*&)ibptr))
                    return false;
                build_index(ibptr, col, row, step,
                    x, y, tile_width, tile_height);
                ib->unlock();
                break;
            }
        }

        if (step < 2)
            continue;
        
        // compute number of index for connector tile
        int index_nums[SIDE_MAX];
        index_nums[SIDE_LEFT] = index_nums[SIDE_RIGHT] = 
            (((tile_width - 1) * 2) + 5) * (tile_height - 1);
        index_nums[SIDE_TOP] = index_nums[SIDE_BOTTOM] =
            index_nums[SIDE_LEFT] - 1;

        index_nums[SIDE_TOPLEFT] =
            (((tile_width - 1) * 4) + 2) +
            ((tile_width - 1) * 2 + 5) * (tile_height - 2) +
            ((tile_height - 2)?1:0);
        index_nums[SIDE_TOPRIGHT] =
            ((tile_width - 1) * 4 + 5) +
            ((tile_width - 1) * 2 + 5) * (tile_height - 2);
        index_nums[SIDE_BOTTOMLEFT] =
            (((tile_width - 1) * 2 + 4) * (tile_height - 1)) +
            (((tile_width - 1) * 2)) + (tile_height - 2) -
            ((tile_height - 2)?2:0);
        index_nums[SIDE_BOTTOMRIGHT] =
            (((tile_width - 1) * 2 + 5) + ((tile_width - 1) * 2 + 3)) *
            ((tile_height - 1) / 2) + (tile_width - 2) * 2 +
            (tile_height - 2) + 2 + ((tile_height - 2)?0:4);

        for (int side = 0; side < SIDE_MAX; ++side)
        {
            ResourceRef<IndexBuffer>& cib = cibs_[side][lod];
            cib = Renderer::instance()->newIndexBuffer();
            if (cib.invalid())
                return false;
            cib->destroy();
            if (!cib->create(index_nums[side], 0, format))
                return false;

            switch (format)
            {
            case Format::INDEX16:
                {
                    uint16_t* ibptr = 0;
                    if (!cib->lock((void*&)ibptr))
                        return false;
                    int usage_index_num = build_connector(ibptr, col, row, step,
                        x, y, tile_width, tile_height, side);
                    tod_assert(usage_index_num == index_nums[side]);
                    cib->unlock();
                    break;
                }
            case Format::INDEX32:
                {
                    uint32_t* ibptr = 0;
                    if (!cib->lock((void*&)ibptr))
                        return false;
                    int usage_index_num = build_connector(ibptr, col, row, step,
                        x, y, tile_width, tile_height, side);
                    tod_assert(usage_index_num == index_nums[side]);
                    cib->unlock();
                    break;
                }
            }
        }
    }    

    return true;
}

    
//-----------------------------------------------------------------------------
void TerrainTile::computeLOD(const Vector3& camera_pos, int lod, float step)
{
    Vector3 to_camera = center_ - camera_pos;
    float dist_to_camera = to_camera.length();

    for (int i = 0; i < lod; ++i)
    {
        if (dist_to_camera < i * step)
        {
            detailLevel_ = i ;
            return;
        }
    }

    detailLevel_ = lod - 1;
}
