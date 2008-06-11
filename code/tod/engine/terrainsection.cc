#include "tod/engine/terrainsection.h"

#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

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
bool TerrainSection::build(const Uri& uri, const Vector3& scale, int split)
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
void TerrainSection::use()
{
    if (vb_.invalid() || vb_->invalid())
        return;
    vb_->use();
}
