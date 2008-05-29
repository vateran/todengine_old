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
Texture* height_map = 0;
#include "tod/engine/texture.h"
#include "tod/engine/vertexbuffer.h"
#include "tod/engine/indexbuffer.h"
Vector3 scale_(10, 10, 10);
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

        Vertex* ptr = 0;
        vb->lock((void*&)ptr);

        float width = static_cast<float>(hmap.width());
        float height = static_cast<float>(hmap.height());
        for (int h = 0; h < hmap.height(); ++h)
        {
            for (int w = 0; w < hmap.width(); ++w)
            {
                Color c = hmap.getPixel(w, h);
                ptr->coord_.x_ = (w - width) / 2 * scale_.x_;
                ptr->coord_.z_ = (h - height) / 2 * scale_.z_;
                ptr->coord_.y_ = c.r_ * scale_.y_;
                
                ptr->normal_ = ptr->coord_;
                ptr->normal_.normalize();

                ptr->diffuse_ = Color(255, 255, 255, 255);

                ptr->u_ = w / (width - 1);
                ptr->v_ = h / (height - 1);
            }
        }

        /*ptr[0].coord_.x_ = -1;
        ptr[0].coord_.y_ = 0;
        ptr[0].coord_.z_ = 1;
        ptr[0].diffuse_ = Color(255, 255, 255, 255);
        ptr[0].u_ = 0;
        ptr[0].v_ = 0;

        ptr[1].coord_.x_ = 0;
        ptr[1].coord_.y_ = 1;
        ptr[1].coord_.z_ = 1;
        ptr[1].diffuse_ = Color(255, 255, 255, 255);
        ptr[1].u_ = 0;
        ptr[1].v_ = 1;

        ptr[2].coord_.x_ = 1;
        ptr[2].coord_.y_ = -1;
        ptr[2].coord_.z_ = 1;
        ptr[2].diffuse_ = Color(255, 255, 255, 255);
        ptr[2].u_ = 1;
        ptr[2].v_ = 1;*/

        vb->unlock();
    }

    vb->use();
    vb->draw(PRIMITIVETYPE_TRIANGLESTRIP);
}
