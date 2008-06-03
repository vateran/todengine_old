#ifndef TOD_CORE_TYPE_PLANE_H
#define TOD_CORE_TYPE_PLANE_H
/**
    @ingroup TodCoreType
    @class tod::Plane
    @brief 
*/

#include "tod/core/primitivetype.h"

namespace tod
{
    class Plane
    {
    public:
        Plane();
        Plane(real_t a, real_t b, real_t c, real_t d);

    public:
        real_t a_, b_, c_, d_;
    };
}

#endif // TOD_CORE_TYPE_PLANE_H
