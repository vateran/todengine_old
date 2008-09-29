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
bool TerrainSection::build(int col, int row, const Vector3& scale, int uv_repeat)
{
    if (vb_.invalid())
        vb_ = Renderer::instance()->newVertexBuffer();

    col_ = col;
    row_ = row;

    vb_->destroy();
    vb_->create(col_ * row_,
        VERTEXCOMPONENT_COORD  |
        VERTEXCOMPONENT_NORMAL |
        VERTEXCOMPONENT_UV0,
        USAGE_DYNAMIC);

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

            vbptr->normal_ = Vector3(0, 0, 1);
            vbptr->normal_.normalize();

            vbptr->u_ = w / width * uv_repeat;
            vbptr->v_ = h / height * uv_repeat;

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
