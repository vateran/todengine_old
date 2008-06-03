#ifndef TOD_CORE_TYPE_TUPLE4_H
#define TOD_CORE_TYPE_TUPLE4_H
/**
    @ingroup TodCoreType
    @class tod::Tuple4
    @brief
*/

namespace tod
{
    template <typename T>
    class Tuple4
    {
    public:
        typedef Tuple4<T> type;

    public:
        Tuple4();
        Tuple4(T x, T y, T z, T w);

        void clear();
        void set(T x, T y, T z, T w);
        
    public:
        T x_, y_, z_, w_;
    };

#include "tod/core/tuple4.inl"

}

#endif // TOD_CORE_TYPE_TUPLE4_H
