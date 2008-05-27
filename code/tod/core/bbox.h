#ifndef TOD_CORE_TYPE_BBOX_H
#define TOD_CORE_TYPE_BBOX_H
/**
    @ingroup TodCoreType
    @class tod::core::BBox
    @brief 
*/

#include <vector>
#include "tod/core/primitivetype.h"
#include "tod/core/vector3.h"
#include "tod/core/line3.h"
#include "tod/core/matrix44.h"

namespace tod
{
namespace core
{
    class BBox
    {
    public:
        /// clip code
        enum Clip
        {
            CLIP_LEFT   = (1<<0),
            CLIP_RIGHT  = (1<<1),
            CLIP_BOTTOM = (1<<2),
            CLIP_TOP    = (1<<3),
            CLIP_NEAR   = (1<<4),
            CLIP_FAR    = (1<<5),
        };
        /// clip status
        enum ClipStatus
        {
            CLIPSTATUS_OUTSIDE,
            CLIPSTATUS_INSIDE,
            CLIPSTATUS_CLIPPED,
        };

        enum
        {
            OUTSIDE     = 0,
            ISEQUAL     = (1<<0),
            ISCONTAINED = (1<<1),
            CONTAINS    = (1<<2),
            CLIPS       = (1<<3),
        };

    public:
        BBox();
        BBox(const Vector3& center, const Vector3& extends);
        BBox(const Matrix44& m);

        Vector3 center() const;
        Vector3 extends() const;
        Vector3 size() const;
        float diagonalSize() const;
        void set(const Matrix44& m);
        void set(const Vector3& center, const Vector3& extends);

        void beginExtends();
        void extend(const Vector3& v);
        void extend(float x, float y, float z);
        void extend(const BBox& box);
        void endExtends();

        void transform(const Matrix44& m);
        void transformDivW(const Matrix44& m);
        bool intersects(const BBox& box) const;
        bool contains(const BBox& box) const;
        bool contains(const Vector3& v) const;
        /// check for intersection with other bounding box
        ClipStatus clipStatus(const BBox& box) const;
        /// check for intersection with projection volume
        ClipStatus clipStatus(const Matrix44& view_proj) const;
        /// create a matrix which transforms an unit cube to this bounding box
        Matrix44 toMatrix44() const;
        /// return one of the 8 corner points
        Vector3 cornersPoint(int index) const;
        void getClipPlanes(const Matrix44& view_proj, std::vector<Plane>& out_planes) const;
        
        int lineTest(float v0, float v1, float w0, float w1);
        int intersect(const BBox& box);
        bool intersect(const Line3& line, Vector3* out_intersect_pos) const;
        
        bool intersect_const_x(const float x, const Line3& line, Vector3* out) const;
        bool intersect_const_y(const float y, const Line3& line, Vector3* out) const;
        bool intersect_const_z(const float z, const Line3& line, Vector3* out) const;
        
        bool point_in_polygon_const_x(const Vector3& p) const;
        bool point_in_polygon_const_y(const Vector3& p) const;
        bool point_in_polygon_const_z(const Vector3& p) const;

    public:
        Vector3 min_;
        Vector3 max_;

    };
}
}

#endif // TOD_CORE_TYPE_BBOX_H
