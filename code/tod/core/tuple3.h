#ifndef TOD_CORE_TYPE_TUPLE3_H
#define TOD_CORE_TYPE_TUPLE3_H
/**
    @ingroup TodCoreType
    @class tod::core::Tuple3
    @brief
*/

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

        Tuple3 operator - ()
        {
            return Tuple3(-x_, -y_, -z_);
        }
        const Tuple3& operator += (const Tuple3& rhs)
        {
            x_ += rhs.x_;
            y_ += rhs.y_;
            z_ += rhs.z_;
            return *this;
        }
        const Tuple3& operator -= (const Tuple3& rhs)
        {
            x_ -= rhs.x_;
            y_ -= rhs.y_;
            z_ -= rhs.z_;
            return *this;
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
