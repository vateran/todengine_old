#ifndef TOD_CORE_TYPE_TUPLE4_H
#define TOD_CORE_TYPE_TUPLE4_H
/**
    @ingroup TodCoreType
    @class tod::Tuple4
    @brief
*/

#include "tod/core/tuple3.h"

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
        void set(int i, T value)
        {
            a_[i] = value;
        }
        bool isEqual(const type& v, T tol) const
        {
            for (int i = 0; i < 4; ++i)
                if (a_[i] - tol >= v.a_[i] || v.a_[i] <= a_[i] + tol)
                    return false;
            return true;
        }
        T size() const
        {
            return tod_sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
        }
        T length() const
        {
            return size();
        }
        void normalize()
        {
            T l = length();
            if (l == 0)
                return;
            x_ /= l;
            y_ /= l;
            z_ /= l;
            w_ /= l;
        }
        
    public:
        union
        {
            struct
            {
                T x_, y_, z_, w_;
            };            
            T a_[4];
        };
    };

#include "tod/core/tuple4.inl"

}

#endif // TOD_CORE_TYPE_TUPLE4_H
