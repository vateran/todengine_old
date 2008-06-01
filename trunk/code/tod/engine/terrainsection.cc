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
#include "tod/engine/texture.h"
#include "tod/engine/vertexbuffer.h"
#include "tod/engine/indexbuffer.h"
Vector3 scale_(0.01f, 0.01f, 0.01f);
void TerrainSection::render()
{
    if (vb == 0)
    {   
        Image hmap(STRING("managed://texture#map.bmp"));
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
                vbptr->coord_.x_ = (w - width) / 2 * scale_.x_;
                vbptr->coord_.z_ = (h - height) / 2 * scale_.z_;
                vbptr->coord_.y_ = c.r_ * scale_.y_;
                
                vbptr->normal_ = vbptr->coord_;
                vbptr->normal_.normalize();

                vbptr->diffuse_ = Color(255, 255, 255, 255);

                vbptr->u_ = w / (width - 1);
                vbptr->v_ = h / (height - 1);
            }
        }

        /*vbptr[0].coord_.x_ = -1;
        vbptr[0].coord_.y_ = 0;
        vbptr[0].coord_.z_ = 1;
        vbptr[0].diffuse_ = Color(255, 255, 255, 255);
        vbptr[0].u_ = 0;
        vbptr[0].v_ = 0;

        vbptr[1].coord_.x_ = 0;
        vbptr[1].coord_.y_ = 1;
        vbptr[1].coord_.z_ = 1;
        vbptr[1].diffuse_ = Color(255, 255, 255, 255);
        vbptr[1].u_ = 0;
        vbptr[1].v_ = 1;

        vbptr[2].coord_.x_ = 1;
        vbptr[2].coord_.y_ = -1;
        vbptr[2].coord_.z_ = 1;
        vbptr[2].diffuse_ = Color(255, 255, 255, 255);
        vbptr[2].u_ = 1;
        vbptr[2].v_ = 1;*/

        vb->unlock();

        ib = Renderer::instance()->newIndexBuffer(STRING("test"));
        ib->create(hmap.width() * hmap.height() * 2, 0, Format::INDEX16);

        struct TriIndex
        {
            unsigned short i0_, i1_, i2_;
        };

        TriIndex* ibptr = 0;
        ib->lock((void*&)ibptr);
        
        ib->unlock();
    }

    vb->use();
    ib->use();
    ib->draw(PRIMITIVETYPE_TRIANGLELIST);
}
