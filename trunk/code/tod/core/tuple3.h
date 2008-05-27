#ifndef TOD_CORE_TYPE_TUPLE3_H
#define TOD_CORE_TYPE_TUPLE3_H
/**
    @ingroup TodCoreType
    @class tod::core::Tuple3
    @brief
*/

#include "tod/core/math.h"

namespace tod
{
namespace core
{
    template <typename T>
    class Tuple3
    {
    public:
        typedef Tuple3<T> type;

    public:
        Tuple3();
        Tuple3(T x, T y, T z);

        void clear();
        void set(T x, T y, T z);
        void set(int i, T value)
        {
            a_[i] = value;
        }
        bool isEqual(const type& v, T tol) const
        {
            for (int i = 0; i < 3; ++i)
                if (a_[i] - tol >= v.a_[i] || v.a_[i] <= a_[i] + tol)
                    return false;
            return true;
        }
        T size() const
        {
            return tod_sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        }

        Tuple3 operator - ()
        {
            return Tuple3(-x_, -y_, -z_);
        }
        const type& operator += (const type& rhs)
        {
            x_ += rhs.x_;
            y_ += rhs.y_;
            z_ += rhs.z_;
            return *this;
        }
        const type& operator -= (const type& rhs)
        {
            x_ -= rhs.x_;
            y_ -= rhs.y_;
            z_ -= rhs.z_;
            return *this;
        }

        type operator + (const type& v) const
        {   
            return type(x_ + v.x_, y_ + v.y_, z_ + v.z_);
        }

        type operator - (const type& v) const
        {
            return type(x_ - v.x_, y_ - v.y_, z_ - v.z_);
        }

        type operator * (float value) const
        {
            return type(x_ * value, y_ * value, z_ * value);
        }

        const T& operator [] (int i) const
        {
            return a_[i];
        }
        T& operator [] (int i)
        {
            return a_[i];
        }
        
    public:
        union
        {
            struct
            {
                T x_, y_, z_;
            };
            T a_[3];
        };
        
    };

#include "tod/core/tuple3.inl"

}
}

#endif // TOD_CORE_TYPE_TUPLE3_H
