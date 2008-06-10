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
        index_num = (((tile_width - 1) * 2) + 5) * (tile_height - 1);
        if (index_num < 0)
            return 0;

        static int connector_flags[] =
        {
            SIDE_TOP, SIDE_LEFT, SIDE_RIGHT, SIDE_BOTTOM,
            SIDE_TOP | SIDE_LEFT, SIDE_TOP | SIDE_RIGHT,
            SIDE_BOTTOM | SIDE_LEFT, SIDE_BOTTOM | SIDE_RIGHT,
        };
        int index_nums[SIDE_MAX];
        index_nums[SIDE_LEFT] = index_nums[SIDE_RIGHT] = 
            (((tile_width - 1) * 2) + 5) * (tile_height - 1);
        index_nums[SIDE_TOP] = index_nums[SIDE_BOTTOM] =
            index_nums[SIDE_LEFT] - 1;

        for (int side = 0; side < SIDE_MAX; ++side)
        {   
            int connector_flag = connector_flags[side];
            ResourceRef<IndexBuffer>& cib = cibs_[side][lod];
            cib = Renderer::instance()->newIndexBuffer();
            if (cib.invalid())
                return false;
            if (!cib->create(index_nums[side], 0, format))
                return false;

            uint16_t* ibptr = 0;
            if (!cib->lock((void*&)ibptr))
                return false;
            int usage_index_num = build_connector(ibptr, col, row, step,
                x, y, tile_width, tile_height, connector_flag);
            tod_assert(usage_index_num == _index_num);
            cib->unlock();
        }
    }    

    return true;
}


//-----------------------------------------------------------------------------
int TerrainTile::build_connector
(uint16_t* ptr, int col, int row, int step,
 int x, int y, int width, int height, int side)
{
    bool winding = true; 
    int index = 0;

    if (step < 2)
        return 0;

    if (side == SIDE_RIGHT)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;
                for (; w < width - 1; w += 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }
            else
            {
                int w = width - 1;
                
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + (w - 1) * step;
                ptr[index++] = ptr[index - 2];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                for (w = width - 2; w >= 0; w -= 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = ptr[index - 1];
            }

            h += 1;
            if (h >= height - 1)
                break;
            winding = !winding;
        }
    }
    else if (side == SIDE_LEFT)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                int w = 0;

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = (h * step + y) * col + x + ((w + 1)* step);
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                
                for (w = 1; w < width; w += 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
                ptr[index++] = ptr[index - 1];
            }
            else
            {
                int w = width - 1;
                for (; w >= 1; w -= 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }

                ptr[index++] = (h * step + y) * col + x + (w * step);
                ptr[index++] = ((h * step + step / 2) + y) * col + x + (w * step);
                ptr[index++] = ptr[index - 1];
                ptr[index++] = ptr[index - 4];
                ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
            }

            h += 1;
            if (h >= height - 1)
                break;            
            winding = !winding;
        }
    }
    else if (side == SIDE_TOP)
    {
        int h = 0;
        while (true)
        {
            if (winding)
            {
                for (int w = 0; w < width; w += 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (h >= height - 2 && w < width - 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + ((w + 1) * step);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step + step / 2);
                    }
                }
            }
            else
            {
                for (int w = width - 1; w >= 0; w -= 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (h >= height - 2 && w > 0)
                    {
                        ptr[index++] = (h * step + y) * col + x + ((w - 1) * step);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step - step / 2);
                    }
                }
            }

            h += 1;
            if (h >= height - 1)
                break;
            ptr[index++] = ptr[index - 1];
            winding = !winding;
        }
    }
    else if (side == SIDE_BOTTOM)
    {
        bool head = false;
        int h = 0;
        while (true)
        {
            if (winding)
            {
                for (int w = 0; w < width; w += 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);

                    if (!head && w < width - 1)
                    {
                        ptr[index++] = (h * step + y) * col + x + (w * step + step / 2);
                        ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                    }
                }

                head = true;
            }
            else
            {
                for (int w = width - 1; w >= 0; w -= 1)
                {
                    ptr[index++] = (h * step + y) * col + x + (w * step);
                    ptr[index++] = ((h + 1) * step + y) * col + x + (w * step);
                }
            }

            h += 1;
            if (h >= height - 1)
                break;
            ptr[index++] = ptr[index - 1];
            winding = !winding;
        }
    }

    return index;
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
