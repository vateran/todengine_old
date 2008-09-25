#ifndef TOD_CORE_MATH_MATH_H
#define TOD_CORE_MATH_MATH_H

#include <math.h>
#include "tod/core/vector3.h"

#define tod_min(a,b)    (((a) < (b)) ? (a) : (b))
#define tod_max(a,b)    (((a) > (b)) ? (a) : (b))
#define tod_abs(a)      (((a) < 0.0f) ? (-(a)) : (a))
#define tod_tiny        (0.00001f)

namespace tod
{

//-----------------------------------------------------------------------------
template <typename T>
inline T tod_sqrt(T x)
{
    if (x < 0.0f)
        x = 0.0f;
    return static_cast<T>(sqrt(x));
};

//-----------------------------------------------------------------------------
/**
    given a ray origin and direction, and three vertices of a triangle, 
    this function returns 'true' and the interpolated texture coordinates if
    the ray intersects the triangle
*/
inline bool tod_intersect_triangle
(const Vector3& origin, const Vector3& dir,
 const Vector3& v0, const Vector3& v1, const Vector3& v2,
 float* t, float* u, float* v)
{
    // find vectors for two edges sharing vert0
    Vector3 edge0 = v1 - v0;
    Vector3 edge1 = v2 - v0;

    // begin calculating determinant - also used to calculate U parameter
    Vector3 pvec(dir);
    pvec.cross(edge1);

    // if determinant is near zero, ray lies in plane of triangle
    float det = edge0.dotprod(pvec);
    Vector3 tvec;
    if (det > 0)
    {
        tvec = origin - v0;
    }
    else
    {
        tvec = v0 - origin;
        det = -det;
    }
    if (det < tod_tiny)
        return false;

    // calculate U parameter and test bounds
    *u = tvec.dotprod(pvec);
    if (*u < 0.0f || *u > det)
        return false;

    // prepare to test V parameter
    Vector3 qvec(tvec);
    qvec.cross(edge0);
    *v = dir.dotprod(qvec);
    if (*v < 0.0f || *u + *v > det)
        return false;

    // calculate t, scale parameters, ray intersects triangle
    *t = edge1.dotprod(qvec);
    float inv_det = 1.0f / det;
    *t *= inv_det;
    *u *= inv_det;
    *v *= inv_det;

    return true;
}

}

#endif // TOD_CORE_MATH_MATH_H