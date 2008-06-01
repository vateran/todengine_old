#include "tod/engine/terrainsection.h"

#include "tod/engine/renderer.h"
#include "tod/engine/image.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
TerrainSection::TerrainSection()
{
    // empty
}


//-----------------------------------------------------------------------------
TerrainSection::~TerrainSection()
{
    // empty
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
void TerrainSection::render()
{
    if (vb == 0)
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

        int col = hmap.width();
        int row = hmap.height();

        ib = Renderer::instance()->newIndexBuffer(STRING("test"));
        ib->create((col * 2) * row - row - 2, 0, Format::INDEX16);

        unsigned short* ibptr = 0;
        ib->lock((void*&)ibptr);

        bool winding = true;
        int step = 1;        

        int index = 0;
        for (int h = 0; h < row - 1; ++h)
        {
            if (winding)
            {
                for (int w = 0; w < col; ++w)
                {
                    ibptr[index++] = h * col + w;
                    ibptr[index++] = (h + 1) * col + w;
                }
            }
            else
            {
                for (int w = col - 1; w >= 0; --w)
                {
                    ibptr[index++] = h * col + w;
                    ibptr[index++] = (h + 1) * col + w;
                }
            }

            ibptr[index++] = ibptr[index - 1];

            winding = !winding;
        }

        ib->unlock();
    }

    vb->use();
    ib->use();
    ib->draw(PRIMITIVETYPE_TRIANGLESTRIP);
}
