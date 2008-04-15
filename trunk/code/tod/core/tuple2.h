#ifndef TOD_CORE_TYPE_TUPLE2_H
#define TOD_CORE_TYPE_TUPLE2_H
/**
    @ingroup TodCoreType
    @class tod::core::Tuple2
    @brief
*/

namespace tod
{
namespace core
{
    template <typename T>
    class Tuple2
    {
    public:
        typedef Tuple2<T> type;

    public:
        Tuple2();
        Tuple2(T x, T y);

        void clear();
        void set(T x, T y);

        Tuple2 operator - ()
        {
            return Tuple2(-x_, -y_);
        }
        const Tuple2& operator += (const Tuple2& rhs)
        {
            x_ += rhs.x_;
            y_ += rhs.y_;
            return *this;
        }
        const Tuple2& operator -= (const Tuple2& rhs)
        {
            x_ -= rhs.x_;
            y_ -= rhs.y_;
            return *this;
        }
        
    public:
        T x_, y_;
    };

#include "tod/core/tuple2.inl"

}
}

#endif // TOD_CORE_TYPE_TUPLE2_H
