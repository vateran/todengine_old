#include "tod/engine/terrainsection.h"

#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
TerrainSection::TerrainSection():
col_(0), row_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
TerrainSection::~TerrainSection()
{
    vb_.release();
}


//-----------------------------------------------------------------------------
bool TerrainSection::build(int col, int row, const Vector3& scale)
{
    if (vb_.invalid())
        vb_ = Renderer::instance()->newVertexBuffer();

    col_ = col;
    row_ = row;

    vb_->destroy();
    vb_->create(col_ * row_,
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

    float width = static_cast<float>(col_);
    float height = static_cast<float>(row_);
    for (int h = 0; h < col_; ++h)
    {
        for (int w = 0; w < row_; ++w)
        {
            vbptr->coord_.x_ = (w - width / 2) * scale.x_;
            vbptr->coord_.z_ = -(h - height / 2) * scale.z_;

            if (w == 4 && h == 2)
                vbptr->coord_.y_ = 2;

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
