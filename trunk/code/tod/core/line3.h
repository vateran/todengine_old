#ifndef TOD_CORE_TYPE_LINE3_H
#define TOD_CORE_TYPE_LINE3_H
/**
    @ingroup TodCoreType
    @class tod::Line3
    @brief 
*/

#include <vector>
#include "tod/core/primitivetype.h"
#include "tod/core/vector3.h"

namespace tod
{
    class Line3
    {
    public:
        Vector3 interpolation(float t) const
        {
            return Vector3(b_ + m_ * t);
        }

    public:
        /// point of origin
        Vector3 b_;
        /// direction
        Vector3 m_;

    };
}

#endif // TOD_CORE_TYPE_LINE3_H
