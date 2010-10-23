#ifndef TOD_CORE_TYPE_QUATERNION_H
#define TOD_CORE_TYPE_QUATERNION_H
/**
    @ingroup TodCoreType
    @class tod::Quaternion
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/tuple4.h"

namespace tod
{
    class Quaternion : public Tuple4<float32_t>
    {
    public:
        Quaternion();

    };
}

#endif // TOD_CORE_TYPE_QUATERNION_H
