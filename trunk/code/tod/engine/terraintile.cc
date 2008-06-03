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

}

//-----------------------------------------------------------------------------
bool TerrainTile::build(const Vector3& scale)
{
    if (vb_.invalid())
    {
        vb_ = Renderer::instance()->newVertexBuffer();
        if (vb_.invalid())
            return false;
    }

    vb_->destroy();
    vb_->create(16,
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
        goto ERROR;

    int width = 4;
    int height = 4;
    float fwidth = static_cast<float>(width);
    float fheight = static_cast<float>(height);
    for (int h = 0; h < width; ++h)
    {
        for (int w = 0; w < height; ++w)
        {
            Color c;

            vbptr->coord_.x_ = (w - fwidth / 2.0f) * scale.x_;
            vbptr->coord_.z_ = -(h - fheight / 2.0f) * scale.z_;
            vbptr->coord_.y_ = c.r_ * scale.y_;

            vbptr->normal_ = vbptr->coord_;
            vbptr->normal_.normalize();

            vbptr->u_ = w / fwidth;
            vbptr->v_ = h / fheight;

            ++vbptr;
        }
    }

    if (!vb_->unlock())
        goto ERROR;
    return true;

ERROR:
    vb_->destroy();
    return false;
}


//-----------------------------------------------------------------------------
void TerrainTile::render()
{
    vb_->use();
    //vb_->draw(PRIMITIVETYPE_TRIANGLESTRIP);
}


//-----------------------------------------------------------------------------
void TerrainTile::computeLOD(const Vector3& camera_pos)
{
    Vector3 to_camera = center_ - camera_pos;
    float dist_to_camera = to_camera.length();    
}
