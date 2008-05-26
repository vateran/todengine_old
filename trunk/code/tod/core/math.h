#ifndef TOD_CORE_MATH_MATH_H
#define TOD_CORE_MATH_MATH_H

#include <math.h>

#define tod_max(a,b)    (((a) > (b)) ? (a) : (b))
#define tod_abs(a)      (((a) < 0.0f) ? (-(a)) : (a))
#define tod_tiny        (0.0000001f)

//-----------------------------------------------------------------------------
template <typename T>
inline T tod_sqrt(T x)
{
    if (x < 0.0f)
        x = 0.0f;
    return static_cast<T>(sqrt(x));
};

#endif // TOD_CORE_MATH_MATH_H