#ifndef TOD_CORE_TYPE_TUPLE3_IMPL_H
#define TOD_CORE_TYPE_TUPLE3_IMPL_H
/**
    @ingroup TodCoreType
    @class tod::Tuple3
    @brief
*/

namespace tod
{
    class Matrix44;
    class Tuple3_Impl
    {
    public:
        static void transformCoord(void* tuple3, const Matrix44& m);
    };
}

#endif // TOD_CORE_TYPE_TUPLE3_IMPL_H
