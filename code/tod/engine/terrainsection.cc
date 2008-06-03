#include "tod/engine/terrainsection.h"

#include "tod/engine/renderer.h"
#include "tod/engine/image.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
TerrainSection::TerrainSection()
{
    tiles_.resize(1);
    tiles_[0].build(Vector3(1, 1, 1));
}


//-----------------------------------------------------------------------------
TerrainSection::~TerrainSection()
{
    // empty
}

//-----------------------------------------------------------------------------
int build_index
(void* ptr, int col, int row, int step,
 int left, int right, int top, int bottom)
{
    unsigned short* p = static_cast<unsigned short*>(ptr);

    bool winding = false; 
    int index = 0;

    for (int h = 0; h < row - step; h += step)
    {
        if (winding)
        {
            for (int w = 0; w < col; w += step)
            {
                p[index++] = h * col + w;
                p[index++] = (h + step) * col + w;
            }
        }
        else
        {
            for (int w = col - 1; w >= 0; w -= step)
            {
                p[index++] = h * col + w;
                p[index++] = (h + step) * col + w;
            }
        }

        p[index++] = p[index - 1];

        winding = !winding;
    }

    return index - 1;
}

//-----------------------------------------------------------------------------
VertexBuffer* vb = 0;
IndexBuffer* ib = 0;
Texture* height_map = 0;
#include <windows.h>
#include "tod/engine/texture.h"
#include "tod/engine/vertexbuffer.h"
#include "tod/engine/indexbuffer.h"
Vector3 scale_(1, 1, 1);
int index_ = 0;
int col = 0;
int row = 0;
void TerrainSection::render()
{
    /*if (vb == 0)
    {   
        Image hmap(STRING("managed://texture#hmap.png"));
        hmap.preload();

        vb = Renderer::instance()->newVertexBuffer(STRING("test"));
        vb->create(hmap.width() * hmap.height(),
            VERTEXCOMPONENT_COORD  |
            VERTEXCOMPONENT_NORMAL |
            VERTEXCOMPONENT_COLOR  |
            VERTEXCOMPONENT_UV0, 0);

        struct Vertex
        {
            Vector3 coord_;
            Vector3 normal_;
            Color diffuse_;
            float u_, v_;
        };

        Vertex* vbptr = 0;
        vb->lock((void*&)vbptr);

        float width = static_cast<float>(hmap.width());
        float height = static_cast<float>(hmap.height());
        for (int h = 0; h < hmap.height(); ++h)
        {
            for (int w = 0; w < hmap.width(); ++w)
            {
                Color c = hmap.getPixel(w, h);

                vbptr->coord_.x_ = (w - width / 2) * scale_.x_;
                vbptr->coord_.z_ = -(h - height / 2) * scale_.z_;
                vbptr->coord_.y_ = c.r_ * scale_.y_;
                
                vbptr->normal_ = vbptr->coord_;
                vbptr->normal_.normalize();

                vbptr->diffuse_ = Color(255, 255, 255, 255);

                vbptr->u_ = w / width;
                vbptr->v_ = h / height;

                ++vbptr;                
            }
        }

        vb->unlock();

        col = hmap.width();
        row = hmap.height();

        ib = Renderer::instance()->newIndexBuffer(STRING("test"));
        ib->create((col * 2) * row - row - 2, 0, Format::INDEX16);

        rebuild(1);
    }

    vb->use();
    ib->use();
    ib->draw(PRIMITIVETYPE_TRIANGLESTRIP, index_ - 2);*/

    if (0 == ib)
    {
        col = 4;
        row = 4;
        ib = Renderer::instance()->newIndexBuffer(STRING("test"));
        ib->create((col * 2) * row - row - 2, 0, Format::INDEX16);

        rebuild(1);
    }

    Matrix44 v = Renderer::instance()->getTransform(TRANSFORM_VIEW);
    v.inverse();
    Vector3 camera_pos = v.getTranslation();

    // compute Level of Details for each tiles in TerrainSection
    for (TerrainTiles::iterator tile = tiles_.begin();
         tile != tiles_.end(); ++tile)
    {
        tile->computeLOD(camera_pos);
        tile->render();

        ib->use();
        ib->draw(PRIMITIVETYPE_TRIANGLESTRIP, index_ - 2);
    }
}

//-----------------------------------------------------------------------------
void TerrainSection::rebuild(int lod)
{
    unsigned short* ibptr = 0;
    ib->lock((void*&)ibptr);

    index_ = build_index(ibptr, col, row, lod, 0, 0, 0, 0);        

    ib->unlock();
}