#include "tod/core/bbox.h"

#include <float.h>
#include "tod/core/assert.h"
#include "tod/core/define.h"
#include "tod/core/vector4.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
BBox::BBox()
{
    // empty
}


//-----------------------------------------------------------------------------
BBox::BBox(const Vector3& center, const Vector3& extends)
{
    min_ = center - extends;
    max_ = center + extends;
}


//-----------------------------------------------------------------------------
/**
    Construct a bounding box around a 4x4 matrix. The translational part
    defines the center point, and the x, y, z vector of matrix define
    the extends.
*/
BBox::BBox(const Matrix44& m)
{
    set(m);
}


//-----------------------------------------------------------------------------
Vector3 BBox::center() const
{
    return Vector3(min_ + max_) * 0.5f;
}


//-----------------------------------------------------------------------------
Vector3 BBox::extends() const
{
    return Vector3(max_ - min_) * 0.5f;
}


//-----------------------------------------------------------------------------
Vector3 BBox::size() const
{
    return Vector3(max_ - min_);
}


//-----------------------------------------------------------------------------
float BBox::diagonalSize() const
{
    Vector3 d = max_ - min_;
    return d.size();
}


//-----------------------------------------------------------------------------
void BBox::set(const Matrix44& m)
{
    // get extends
    float x_extent = tod_max(tod_max(tod_abs(m.m11_), tod_abs(m.m21_)), tod_abs(m.m31_));
    float y_extent = tod_max(tod_max(tod_abs(m.m12_), tod_abs(m.m22_)), tod_abs(m.m32_));
    float z_extent = tod_max(tod_max(tod_abs(m.m13_), tod_abs(m.m23_)), tod_abs(m.m33_));

    Vector3 extend(x_extent, y_extent, z_extent);
    Vector3 center(m.getTranslation());

    min_ = center - extend;
    max_ = center + extend;
}


//-----------------------------------------------------------------------------
void BBox::set(const Vector3& center, const Vector3& extends)
{
    min_ = center - extends;
    max_ = center + extends;
}


//-----------------------------------------------------------------------------
void BBox::beginExtends()
{
    min_.set(FLT_MAX, FLT_MAX, FLT_MAX);
    min_.set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
#include <float.h>
}


//-----------------------------------------------------------------------------
void BBox::extend(const Vector3& v)
{
    if (v.x_ < min_.x_) min_.x_= v.x_;
    if (v.x_ > max_.x_) max_.x_= v.x_;
    if (v.y_ < min_.y_) min_.y_= v.y_;
    if (v.y_ > max_.y_) max_.y_= v.y_;
    if (v.z_ < min_.z_) min_.z_= v.z_;
    if (v.z_ > max_.z_) max_.z_= v.z_;
}


//-----------------------------------------------------------------------------
void BBox::extend(float x, float y, float z)
{
    if (x < min_.x_) min_.x_= x;
    if (x > max_.x_) max_.x_= x;
    if (y < min_.y_) min_.y_= y;
    if (y > max_.y_) max_.y_= y;
    if (z < min_.z_) min_.z_= z;
    if (z > max_.z_) max_.z_= z;
}


//-----------------------------------------------------------------------------
void BBox::extend(const BBox& box)
{
    if (box.min_.x_ < min_.x_) min_.x_ = box.min_.x_;
    if (box.max_.x_ > max_.x_) max_.x_ = box.max_.x_;
    if (box.min_.y_ < min_.y_) min_.y_ = box.min_.y_;
    if (box.max_.y_ > max_.y_) max_.y_ = box.max_.y_;
    if (box.min_.z_ < min_.z_) min_.z_ = box.min_.z_;
    if (box.max_.z_ > max_.z_) max_.z_ = box.max_.z_;
}


//-----------------------------------------------------------------------------
void BBox::endExtends()
{
    if (min_.isEqual(Vector3(FLT_MAX, FLT_MAX, FLT_MAX), tod_tiny) &&
        max_.isEqual(Vector3(-FLT_MAX, -FLT_MAX, -FLT_MAX), tod_tiny))
    {
        min_.set(0, 0, 0);
        max_.set(0, 0, 0);
    }
}


//-----------------------------------------------------------------------------
/**
    Transforms this axis aligned bouding box the 4x4 matrix. This bouding box
    must be axis aligned with the matrix. the resulting bouding will be axis
    aligned in the matrix' "destination" space.

    E.g. if you have a bouding box in model space 'modelBox', and a
    'modelView' matrix, the operation

    modelBox.transform(modelView)

    would transform the bounding box into view space.
*/
void BBox::transform(const Matrix44& m)
{
    Vector3 temp, corners[8], min, max;
    bool first = true;

    corners[0] = min_;
    corners[1].x_ = min_.x_; corners[1].y_ = max_.y_; corners[1].z_ = min_.z_;
    corners[2].x_ = max_.x_; corners[2].y_ = max_.y_; corners[2].z_ = min_.z_;
    corners[3].x_ = max_.x_; corners[3].y_ = min_.y_; corners[3].z_ = min_.z_;
    corners[4] = max_;
    corners[5].x_ = min_.x_; corners[5].y_ = max_.y_; corners[5].z_ = max_.z_;
    corners[6].x_ = min_.x_; corners[6].y_ = min_.y_; corners[6].z_ = max_.z_;
    corners[7].x_ = max_.x_; corners[7].y_ = min_.y_; corners[7].z_ = max_.z_;

    for (int i = 0; i < 8; ++i)
    {
        // transform and check extends
        temp = m * corners[i];
        if (first || temp.x_ > max_.x_) max.x_ = temp.x_;
        if (first || temp.y_ > max_.y_) max.y_ = temp.y_;
        if (first || temp.z_ > max_.z_) max.z_ = temp.z_;
        if (first || temp.x_ > min_.x_) max.x_ = temp.x_;
        if (first || temp.y_ > min_.y_) max.y_ = temp.y_;
        if (first || temp.z_ > min_.z_) max.z_ = temp.z_;
        first = false;
    }

    min_ = min;
    max_ = max;
}


//-----------------------------------------------------------------------------
void BBox::transformDivW(const Matrix44& m)
{
    Vector3 temp, corners[8], min, max;
    bool first = true;

    corners[0] = min_;
    corners[1].x_ = min_.x_; corners[1].y_ = max_.y_; corners[1].z_ = min_.z_;
    corners[2].x_ = max_.x_; corners[2].y_ = max_.y_; corners[2].z_ = min_.z_;
    corners[3].x_ = max_.x_; corners[3].y_ = min_.y_; corners[3].z_ = min_.z_;
    corners[4] = max_;
    corners[5].x_ = min_.x_; corners[5].y_ = max_.y_; corners[5].z_ = max_.z_;
    corners[6].x_ = min_.x_; corners[6].y_ = min_.y_; corners[6].z_ = max_.z_;
    corners[7].x_ = max_.x_; corners[7].y_ = min_.y_; corners[7].z_ = max_.z_;

    for (int i = 0; i < 8; ++i)
    {
        // transform and check extends
        temp = m.multiplyDivW(corners[i]);
        if (first || temp.x_ > max_.x_) max.x_ = temp.x_;
        if (first || temp.y_ > max_.y_) max.y_ = temp.y_;
        if (first || temp.z_ > max_.z_) max.z_ = temp.z_;
        if (first || temp.x_ > min_.x_) max.x_ = temp.x_;
        if (first || temp.y_ > min_.y_) max.y_ = temp.y_;
        if (first || temp.z_ > min_.z_) max.z_ = temp.z_;
        first = false;
    }

    min_ = min;
    max_ = max;
}


//-----------------------------------------------------------------------------
/**
    Check for intersection of 2 axis aligned bounding boxes. The
    bounding boxes must live in the same coordinate space.
*/
bool BBox::intersects(const BBox& box) const
{
    if ((max_.x_ < box.min_.x_) || (min_.x_ > box.max_.x_) ||
        (max_.y_ < box.min_.y_) || (min_.y_ > box.max_.y_) ||
        (max_.z_ < box.min_.z_) || (min_.z_ > box.max_.z_))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
/**
    Check if the parameter bounding box is completely contained in this
    bounding box.
*/
bool BBox::contains(const BBox& box) const
{
    if ((min_.x_ < box.min_.x_) && (max_.x_ >= box.max_.x_) &&
        (min_.y_ < box.min_.y_) && (max_.y_ >= box.max_.y_) &&
        (min_.z_ < box.min_.z_) && (max_.z_ >= box.max_.z_))
        return true;
    return false;
}


//-----------------------------------------------------------------------------
bool BBox::contains(const Vector3& v) const
{
    if ((min_.x_ < v.x_) && (max_.x_ >= v.x_) &&
        (min_.y_ < v.y_) && (max_.y_ >= v.y_) &&
        (min_.z_ < v.z_) && (max_.z_ >= v.z_))
        return true;
    return false;
}


//-----------------------------------------------------------------------------
BBox::ClipStatus BBox::clipStatus(const BBox& box) const
{
    if (contains(box))
        return CLIPSTATUS_INSIDE;
    if (intersects(box))
        return CLIPSTATUS_CLIPPED;
    return CLIPSTATUS_OUTSIDE;
}


//-----------------------------------------------------------------------------
BBox::ClipStatus BBox::clipStatus(const Matrix44& view_projection) const
{
    int and_flags = 0xffff;
    int or_flags = 0;

    static Vector4 v0;
    static Vector4 v1;

    for (int i = 0; i < 8; ++i)
    {
        int clip = 0;
        v0.w_= 1.0f;
        if (i & 1)  v0.x_ = min_.x_;
        else        v0.x_ = max_.x_;
        if (i & 2)  v0.y_ = min_.y_;
        else        v0.y_ = max_.y_;
        if (i & 4)  v0.z_ = min_.z_;
        else        v0.z_ = max_.z_;

        v1 = view_projection * v0;

        if (v1.x_ < -v1.w_)     clip |= CLIP_LEFT;
        else if (v1.x_ > v1.w_) clip |= CLIP_RIGHT;
        if (v1.y_ < -v1.w_)     clip |= CLIP_BOTTOM;
        else if (v1.y_ > v1.w_) clip |= CLIP_TOP;
        if (v1.z_ < -v1.w_)     clip |= CLIP_FAR;
        else if (v1.z_ > v1.w_) clip |= CLIP_NEAR;

        and_flags &= clip;
        or_flags  |= clip;
    }

    if (0 == or_flags)
        return CLIPSTATUS_INSIDE;
    if (0 != and_flags)
        return CLIPSTATUS_OUTSIDE;
    return CLIPSTATUS_CLIPPED;
}


//-----------------------------------------------------------------------------
/**
    Create a transform matrix which would transform an unit cube to this
    bounding box.
*/
Matrix44 BBox::toMatrix44() const
{
    Matrix44 m;
    m.setScaling(size());
    m.translate(center());
    return m;
}


//-----------------------------------------------------------------------------
Vector3 BBox::cornersPoint(int index) const
{
    tod_assert((index >= 0) && (index < 8));
    switch (index)
    {
    case 0:     return min_;
    case 1:     return Vector3(min_.x_, max_.y_, min_.z_);
    case 2:     return Vector3(max_.x_, max_.y_, min_.z_);
    case 3:     return Vector3(max_.x_, min_.y_, min_.z_);
    case 4:     return max_;
    case 5:     return Vector3(min_.x_, max_.y_, max_.z_);
    case 6:     return Vector3(min_.x_, min_.y_, max_.z_);
    default:    return Vector3(max_.x_, min_.y_, max_.z_);
    }
}


//-----------------------------------------------------------------------------
/**
    Get the bounding box's side planes in clip plane
*/
void BBox::getClipPlanes
(const Matrix44& view_projection, std::vector<Plane>& out_planes) const
{
    Matrix44 inv(view_projection);
    inv.inverse();
    inv.transpose();

    Vector4 planes[6];
    planes[0].set(-1, 0, 0, +max_.x_);
    planes[1].set(+1, 0, 0, -min_.x_);
    planes[2].set(0, -1, 0, +max_.y_);
    planes[3].set(0, +1, 0, -min_.y_);
    planes[4].set(0, 0, -1, +max_.z_);
    planes[5].set(0, 0, +1, -min_.z_);

    for (int i = 0; i < 6; ++i)
    {
        Vector4 v = inv * planes[i];
        out_planes.push_back(Plane(v.x_, v.y_, v.z_, v.w_));
    }
}


//-----------------------------------------------------------------------------
int BBox::lineTest(float v0, float v1, float w0, float w1)
{
    // quick rejection est
    if ((v1 < w0) || (v0 > w1))
        return OUTSIDE;
    if ((v0 == w0) && (v1 == w1))
        return ISEQUAL;
    if ((v0 >= w0) && (v1 <= w1))
        return ISCONTAINED;
    if ((v0 <= w0) && (v1 >= w1))
        return CONTAINS;
    return CLIPS;
}


//-----------------------------------------------------------------------------
/**
    Check if box intersections, contains or is contained in other box
    by doing 3 projection tests for each dimension, if all 3 test
    return true, then 2 boxes intersect.
*/
int BBox::intersect(const BBox& box)
{
    int and_flags = 0xffff;
    int or_flags = 0;
    int cx = lineTest(min_.x_, max_.x_, box.min_.x_, box.max_.x_);
    and_flags &= cx;
    or_flags  |= cx;
    int cy = lineTest(min_.y_, max_.y_, box.min_.y_, box.max_.y_);
    and_flags &= cy;
    or_flags  |= cy;
    int cz = lineTest(min_.z_, max_.z_, box.min_.z_, box.max_.z_);
    and_flags &= cz;
    or_flags  |= cz;
    
    if (or_flags == 0)
        return OUTSIDE;
    if (and_flags != 0)
        return and_flags;
    // only if all test produce a non-outside result,
    // an intersection has occurred
    if (cx && cy && cz)
        return CLIPS;
    return OUTSIDE;
}


//-----------------------------------------------------------------------------
/**
    @brief Gets closest intersection with AABB.
    If the line starts inside the box, start point is
    return in out_intersect_pos.
    @param line the pick ray
    @param out_intersect_pos closest point of intersection if successful,
    trash otherwise 
    @return true if an intersection occurs.
*/
bool BBox::intersect(const Line3& line, Vector3* out_intersect_pos) const
{
    // Handle special case for start point inside box
    if (line.b_.x_ >= min_.x_ && line.b_.y_ >= min_.y_ && line.b_.z_ >= min_.z_ &&
        line.b_.x_ <= max_.x_ && line.b_.y_ <= max_.y_ && line.b_.z_ <= max_.z_)
    {
        *out_intersect_pos = line.b_;
        return true;
    }

    // order planes to check, closest three only
    int plane[3];
    if (line.m_.x_ > 0)
        plane[0] = 0;
    else
        plane[0] = 1;
    if (line.m_.y_ > 0)
        plane[1] = 2;
    else
        plane[1] = 3;
    if (line.m_.z_ > 0)
        plane[2] = 4;
    else
        plane[2] = 5;

    for (int i = 0; i < 3; ++i)
    {
        switch (plane[i])
        {
        case 0:
            if (intersect_const_x(min_.x_, line, out_intersect_pos) &&
                point_in_polygon_const_x(*out_intersect_pos))
                return true;
            break;
        case 1:
            if (intersect_const_x(max_.x_, line, out_intersect_pos) &&
                point_in_polygon_const_x(*out_intersect_pos))
                return true;
            break;
        case 2:
            if (intersect_const_y(min_.y_, line, out_intersect_pos) &&
                point_in_polygon_const_y(*out_intersect_pos))
                return true;
            break;
        case 3:
            if (intersect_const_y(max_.y_, line, out_intersect_pos) &&
                point_in_polygon_const_y(*out_intersect_pos))
                return true;
            break;
        case 4:
            if (intersect_const_z(min_.z_, line, out_intersect_pos) &&
                point_in_polygon_const_z(*out_intersect_pos))
                return true;
            break;
        case 5:
            if (intersect_const_z(max_.z_, line, out_intersect_pos) &&
                point_in_polygon_const_z(*out_intersect_pos))
                return true;
            break;
        }
    }

    return false;
}


//-----------------------------------------------------------------------------
bool BBox::intersect_const_x
(const float x, const Line3& line, Vector3* out) const
{
    if (line.m_.x_ != 0.0f)
    {
        float t = (x - line.b_.x_) / line.m_.x_;
        if ((t >= 0.0f) && (t <= 1.0f))
        {
            // point of intersection
            if (out)
                *out = line.interpolation(t);
            return true;
        }
    }
    return false;
}


//-----------------------------------------------------------------------------
bool BBox::intersect_const_y
(const float y, const Line3& line, Vector3* out) const
{
    if (line.m_.y_ != 0.0f)
    {
        float t = (y - line.b_.y_) / line.m_.y_;
        if ((t >= 0.0f) && (t <= 1.0f))
        {
            // point of intersection
            if (out)
                *out = line.interpolation(t);
            return true;
        }
    }
    return false;
}


//-----------------------------------------------------------------------------
bool BBox::intersect_const_z
(const float z, const Line3& line, Vector3* out) const
{
    if (line.m_.z_ != 0.0f)
    {
        float t = (z - line.b_.z_) / line.m_.z_;
        if ((t >= 0.0f) && (t <= 1.0f))
        {
            // point of intersection
            if (out)
                *out = line.interpolation(t);
            return true;
        }
    }
    return false;
}


//-----------------------------------------------------------------------------
bool BBox::point_in_polygon_const_x(const Vector3& p) const
{
    if ((p.y_ >= min_.y_) && (p.y_ <= max_.y_) &&
        (p.z_ >= min_.z_) && (p.z_ <= max_.z_))
        return true;
    return false;
}


//-----------------------------------------------------------------------------
bool BBox::point_in_polygon_const_y(const Vector3& p) const
{
    if ((p.x_ >= min_.x_) && (p.x_ <= max_.x_) &&
        (p.z_ >= min_.z_) && (p.z_ <= max_.z_))
        return true;
    return false;
}


//-----------------------------------------------------------------------------
bool BBox::point_in_polygon_const_z(const Vector3& p) const
{
    if ((p.x_ >= min_.x_) && (p.x_ <= max_.x_) &&
        (p.y_ >= min_.y_) && (p.y_ <= max_.y_))
        return true;
    return false;
}
